import zappy
import queue
import log
import queue
import random
import time
import subprocess

class Engine:
    def __init__(self, port, name, host):
        self._zappy = zappy.Zappy(port, name, host)

        self._run = False

        self._serverReply = ''
        self._aiReply = ''
        self._key = 'jsxqmadymtm@epitech.eu'
        self._cmds = queue.Queue(0)

        # Utils players
        self._players = []
        self._leaders = [None, None, None, None, None, None, None, None]
        self._deltas = {
            'starving_critical': 2,
            'starving_begin': 15,
            'starving_end': 60
        }

        # States
        self._starving = False
        self._incanting = False
        self._levelUpBroadcast = False

        # Env
        self._malwares = 0
        self._dd = ['Left', 'Right']
        self._minerals = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
        self._targets = [
            ['Forward'],
            ['Forward', 'Left', 'Forward', 'Right'],
            ['Left', 'Forward'],
            ['Left', 'Forward', 'Left', 'Forward'],
            ['Left', 'Left', 'Forward'],
            ['Right', 'Forward', 'Right', 'Forward'],
            ['Right', 'Forward'],            
            ['Forward', 'Right', 'Forward', 'Left']]
        self._levels = [
            [1, 1, 0, 0, 0, 0, 0],
            [2, 1, 1, 1, 0, 0, 0],
            [2, 2, 0, 1, 0, 2, 0],
            [4, 1, 1, 2, 0, 1, 0],
            [4, 1, 2, 1, 3, 0, 0],
            [6, 1, 2, 3, 0, 1, 0],
            [6, 2, 2, 2, 2, 2, 1]]

        # Messages
        self._messages = queue.LifoQueue(0)

    def _getServerReply(self):
        self._serverReply = self._zappy._net.receive()
        cmds = self._serverReply.split('\n')
        for i in cmds:
            if i != '':
                if i == 'dead': self._die()
                self._cmds.put(i)
        return self._serverReply

    def _getAnswer(self, force=True):
        # If the queue is empty, retrieve answer from server
        if self._cmds.qsize() == 0:
            self._getServerReply()
        # Get last command
        reply = self._cmds.get()
        # Random incoming token
        if 'Elevation underway' in reply:
            self._incanting = True
            return self._getAnswer() if force else reply
        if 'Current level:' in reply:
            self._zappy._player._level += 1
            self._incanting = False
            self._levelUpBroadcast = True
            log.Log(reply, color='Green', underline=True, bold=True)
            return self._getAnswer() if force else reply
        if 'message' in reply:
            self._messages.put(reply)
            return self._getAnswer() if force else reply
        if 'eject' in reply:
            return self._getAnswer() if force else reply
        return reply
    
    def _send(self, payload, nl=True):
        log.Log(payload, color='Blue')
        self._zappy._net.send(payload + ('\n' if nl else ''))

    def _init(self):
        self._zappy._net.connect() # Connect to the server

        self._getServerReply() # Welcome message
        log.Head(self._cmds.get()) # ===========

        log.Inform('Retrieving player infos...')
        log.Inform("Player team: " + self._zappy._player._team)

        self._zappy._net.send(self._zappy._player._team + '\n') # Init call
        self._getServerReply() # Get reply
        if self._cmds.qsize() < 2: self._getServerReply()

        reply = self._cmds.get()
        if (reply == "ko" or reply == "ok"):
            log.Fail("Cannot retrieve player infos :(", bold=True)
            exit(84)
        reply = self._cmds.get()
        pos_t = reply.split()

        self._run = True

        # Register player for other member of the team
        id = self._zappy._player._id
        team = self._zappy._player._team
        level = self._zappy._player._level

        log.Inform('Register player ' + str(id) + ' (' + team + ')')
        self._global_broadcast(self._zappy._msgManager._register(id, level, team))

        # Random move at begining in order to dispatch AIs
        self._move_turn()
        self._move_forward()
        ##############################################

    def _start(self):
        while self._run: self._lap()
        log.Log('Exiting...', color='Blue')

    def _stop(self):
        self._run = False
        return False
    
    def _die(self):
        log.Warn('Dayum, this is the end for me... :\'(')
        self._global_broadcast(self._zappy._msgManager._unregister(self._zappy._player._id, self._zappy._player._team))
        self._stop()
        exit(0)

    def _lap(self):
        # Check pool state
        self._pool_entryPoint()
        # If we just level up, broadcast it to the whole population
        self._utils_broadcast_newLevel()
        # Update inventory and vision
        self._global_entryPoint()
        # Prevent user for starving
        self._food_entryPoint()
        if not self._starving:
            self._message_entryPoint()
        # If player is a leader
        # Then check ressource, help and cast
        if self._pool_isPlayerALeader(self._zappy._player._level, self._zappy._player._id) and not self._starving:
            log.Inform('Leader actions....')
            if self._ressource_entryPoint() == True:
                log.Inform('Enough ressource to incant')
                if self._help_entryPoint() == True:
                    log.Inform('Enough help to incant')
                    self._cast_entryPoint()

    ############### POOLS ################
    def _pool_entryPoint(self):
        c_pool = self._pool_getCurrent()
        player = self._zappy._player

        log.Inform('Current pool for ' + str(player._id) + ' (' + str(player._level) + '): ' + ', '.join(list(map(str, c_pool))))

        self._leaders[player._level - 1] = min(c_pool + [player._id])
        return True
    
    def _pool_getCurrent(self):
        pool = []
        player = self._zappy._player
        for x in self._players:
            if x._level == player._level: pool.append(x._id)
        return pool

    def _pool_isPlayerALeader(self, level, playerID):
        return self._leaders[level - 1] == playerID
    
    def _pool_getBelow(self):
        pool = []
        player = self._zappy._player
        for x in self._players:
            if x._level <= player._level: pool.append(x._id)
        return pool
    
    ############### FOOD #################
    def _food_entryPoint(self):
        if self._incanting: return False
        # Check if the player is starving
        if not self._food_isStarving():
            return False
        # Search food around
        target = self._ressource_searchByType('food')
        if target is None:
            self._ressource_take('food')
        else:
            self._move_smooth(target)
        return True
    
    def _food_isStarving(self):
        food_level = self._food_get()
        if food_level < self._deltas['starving_critical']:
            self._die()
        elif food_level < self._deltas['starving_begin']:
            self._starving = True
        elif food_level > self._deltas['starving_end']:
            self._starving = False
        log.Inform('Player ' + str(self._zappy._player._id) + ' is' + ('' if self._starving else ' not') + ' starving (' + str(food_level)+ ')')
        return self._starving
    
    def _food_get(self):
        return self._zappy._player._inventory[0]

    ############### MESSAGES ###################
    def _message_entryPoint(self):
        if self._incanting == True: return False

        t_help = True
        self._malwares = 0
        while self._messages.qsize() > 0:
            if self._message_handle(self._messages.get(), help=t_help) == 'use_help': t_help = False

    def _message_handle(self, payload, help=True):
        t_buff = payload.split(',')
        dir = t_buff[0].split(' ')[1]

        # check if the message is sent by us or not
        # if not => re send message as malware
        if not self._key in t_buff[1]:
            self._malwares += 1
            return self._message_sendMalware(t_buff[1]) if self._malwares <= 10 else False
        # check if the message is based on our protocol
        protocol_based = any([x in t_buff[1] for x in self._zappy._msgManager._commands])
        # if not, delete broadcast of the message
        if not protocol_based: return False
        # else, remove key from the message, then parse and exec it
        buffer = [dir]
        buffer += self._utils_epurTable(t_buff[1].replace(self._key, '').split(':'))
        buffer[1] = buffer[1].replace(' ', '')

        log.Fail(', '.join(buffer))

        #
        # Redirect query
        #
        query = buffer[1]
        if query == 'REGISTER':
            self._message_register(buffer)
        elif query == 'INFORM':
            self._message_inform(buffer)
        elif query == 'UNREGISTER':
            self._message_unregister(buffer)
        elif query == 'SET_LEVEL':
            self._message_setLevel(buffer)
        elif query == 'REQUIRE_HELP' and help:
            return self._message_requireHelp(buffer)

    def _message_sendMalware(self, payload):
        log.Inform('Sending malware as (' + payload + ')')
        self._global_broadcast(payload)
        return True
    
    def _message_register(self, datas):
        newID = int(datas[2])
        newLevel = int(datas[3])
        team = datas[4]

        myId = self._zappy._player._id
        myLevel = self._zappy._player._level
        myTeam = self._zappy._player._team

        if team != myTeam: return False

        self._players.append(zappy.Ally(newID, newLevel, team))
        self._global_broadcast(self._zappy._msgManager._inform(newID, myId, myLevel, myTeam))
        self._utils_logPlayers()
        return True
    
    def _message_unregister(self, datas):
        targetId = int(datas[2])
        targetTeam = datas[3]
        deleted = False

        if targetTeam != self._zappy._player._team: return False

        for i in range(len(self._players)):
            if self._players[i]._id == targetId:
                self._players.pop(i); deleted = True; break

        self._utils_logPlayers()
        return deleted

    def _message_inform(self, datas):
        targetId = int(datas[2])
        srcID = int(datas[3])
        srcLevel = int(datas[4])
        srcTeam = datas[5]

        if srcTeam != self._zappy._player._team or targetId != self._zappy._player._id: return False

        for i in self._players:
            if i._id == srcID: return False

        self._players.append(zappy.Ally(srcID, srcLevel, srcTeam))
        self._utils_logPlayers()
        return True

    def _message_setLevel(self, datas):
        level = int(datas[2])
        team = datas[3]
        playerID = int(datas[4])

        player = self._zappy._player
        if team != player._team: return False

        for pl in range(len(self._players)):
            if self._players[pl]._id == playerID:
                log.Inform('Set level to ' + str(level) + 'for ' + str(self._players[pl]))
                self._players[pl]._level = level
                if level == player._level: self._pool_entryPoint()

    def _message_requireHelp(self, datas):
        if len(datas) != 6: return False
        dir = int(datas[0])
        level = int(datas[2])
        team = datas[3]
        leaderID = int(datas[4])
        playerID = int(datas[5])

        player = self._zappy._player
        if team != player._team or playerID != player._id: return False
        if self._leaders[level - 1] == player._id: return False

        log.Inform('I\'m comming for you!')

        if dir == 0: return 'use_help'

        commands = self._targets[dir - 1]
        log.Head(str(dir) + '   -   ' + ', '.join(commands))
        for i in commands:
            if i == 'Forward':
                self._move_forward()
            else:
                self._move_turn(i)
        return 'use_help'

    ############### RESSOURCES #################
    def _ressource_entryPoint(self):
        if self._starving or self._incanting: return False

        # Get needed ressources for level up
        clevel = self._zappy._player._level
        nr = [0 if t < 0 else t for t in [self._levels[clevel - 1][x] - self._zappy._player._inventory[x] for x in range(1, 7)]]
        if sum(nr) == 0: return True
        log.Inform('Need some ressource (' + ', '.join(list(map(str, nr))) + ')')
        for x in range(len(nr)):
            if nr[x] > 0:
                mineral = self._minerals[x]
                target = self._ressource_searchByType(mineral)
                if target is None:
                    self._ressource_take(mineral)
                else:
                    self._move_smooth(target)
        return False

    def _ressource_searchByType(self, rtype):
        k = 0 # Index for case ahead of the player
        n = 2 # coef
        # Check current position
        if self._zappy._player._cells[0].count(rtype):
            return None

        for i in range(1, self._zappy._player._level + 1):
            k += n # Add the coef to the ref case
            n += 2
            s = 2 * i # Size of the row (-1)
            if self._zappy._player._cells[k].count(rtype):
                log.Inform('Found some ' + rtype + ' ahead of the player')
                return 'Forward'
            for xwing in range(1, s // 2 + 1):
                if self._zappy._player._cells[k - xwing].count(rtype):
                    log.Inform(rtype + ' found to the left of the player | ' + str(k - xwing))
                    return 'Left'
                elif self._zappy._player._cells[k + xwing].count(rtype):
                    log.Inform(rtype + ' found to the right of the player | ' + str(k + xwing))                    
                    return 'Right'
        return 'Random'
    
    def _ressource_take(self, rtype):
        self._send('Take ' + rtype)
        reply = self._getAnswer()
        log.Log(reply, color='Green')
        if rtype == 'food':
            self._global_inventory()
        else:
            idx = self._minerals.index(rtype)
            self._zappy._player._inventory[idx + 1] += 1

    def _ressource_getNextRessourceOnCell(self):
        self._global_scan()
        table = self._minerals + ['food']
        ccell = self._zappy._player._cells[0]
        payload = [ccell.count(mineral) for mineral in table]
        for x in range(len(payload)):
            if payload[x] > 0: return table[x]
        return False

    def _ressource_drop(self, rtype):
        self._send('Set ' + rtype)
        log.Log(self._getAnswer(), color='Green')
        idx = self._minerals.index(rtype)
        self._zappy._player._inventory[idx + 1] -= 1

    ############### HELP #################
    def _help_entryPoint(self):
        if self._incanting or self._starving: return False

        # Get datas
        player      =   self._zappy._player
        pool        =   self._pool_getCurrent()
        nbOnCell    =   self._help_player_oncell()
        nbNeed      =   self._levels[player._level - 1][0]
        belowMe     =   self._pool_getBelow()

        if nbNeed == nbOnCell and len(pool) >= nbNeed - 1: return True
        elif nbOnCell > nbNeed:
            self._help_eject()
            return False

        if len(pool) < nbNeed - 1:
            if len(belowMe) < nbNeed - 1:
                self._global_fork()
            return False
        
        if nbNeed == 0: return False

        for i in pool[:nbNeed - 1]:
            self._global_broadcast(self._zappy._msgManager._require_support(player._level, player._team, player._id, i))

    def _help_player_oncell(self):
        self._global_scan()
        return self._zappy._player._cells[0].count('player')

    def _help_eject(self):
        self._send('Eject')
        log.Log(self._getAnswer(), color='Green')

    ############### CAST #################

    def _cast_entryPoint(self):
        self._cast_emptyCell()
        self._cast_fillCell()
        self._cast_start()
    
    def _cast_emptyCell(self):
        lock = True
        while lock:
            rtype = self._ressource_getNextRessourceOnCell()
            if rtype: self._ressource_take(rtype)
            else: lock = False
    
    def _cast_fillCell(self):
        table = self._levels[self._zappy._player._level - 1][1:]
        for k in range(len(table)):
            for t in range(table[k]):
                self._ressource_drop(self._minerals[k])
    
    def _cast_start(self):
        pool        =   self._pool_getCurrent()
        nbNeed      =   self._levels[self._zappy._player._level - 1][0]

        self._send('Incantation')
        reply = self._getAnswer(force=False)
        log.Log(reply, color='Green')
        if reply == 'Elevation underway':
            self._incanting = True
        reply = self._getAnswer(force=False)
        if 'Current level:' in reply:
            for i in range(nbNeed - 1):
                self._players[i]._level += 1

        self._incanting = False

    ############### MOVE #################
    
    def _move_smooth(self, dir='Random'):
        if dir == 'Random': dir = (self._dd + ['Forward'])[random.randint(0, 2)]
        if dir == 'Forward': return self._move_forward()

        o_dest = self._dd[(self._dd.index(dir) + 1) % 2]
        self._move_turn(dest=dir)
        self._move_forward()
        self._move_turn(dest=o_dest)
        self._move_forward()
        return True
    
    def _move_forward(self):
        self._send('Forward')
        log.Log(self._getAnswer(), color='Green')
    
    def _move_turn(self, dest='Random'):
        if dest == 'Random': dest = self._dd[random.randint(0, 1)]
        self._send(dest)
        log.Log(self._getAnswer(), color='Green')

    ############### GLOBAL #################

    def _global_entryPoint(self):
        self._global_scan()
        self._global_inventory()

    def _global_broadcast(self, payload):
        self._send('Broadcast ' + payload + self._key)
        log.Log(self._getAnswer(), color='Green')
    
    def _global_scan(self):
        # Get player vision
        self._send('Look')
        reply = self._getAnswer()
        # Parse && epur vision
        while not '[' in reply or not ']' in reply or not 'player' in reply:
            reply = self._getAnswer()
        reply = reply.replace(']', '').replace('[', '').split(',')
        for i in range(len(reply)):
            reply[i] = self._utils_epurTable(reply[i].split(' '))
        self._zappy._player._cells = reply
        for i in range(len(reply)): log.Log('Cell ' + str(i) + ': ' + ', '.join(reply[i]), color='Green')
        return True
    
    def _global_inventory(self):
        # Get inventory
        self._send('Inventory')
        reply = self._getAnswer()
        while not '[' in reply or not ']' in reply or reply.count(',') != 6:
            reply = self._getAnswer()
        # Parse inventory
        reply = reply.split('[')[1].split(']')[0].split(',')
        for i in range(len(reply)):
            reply[i] = reply[i].split(' ')
            reply[i] = self._utils_epurTable(reply[i])
            reply[i] = int(reply[i][1])
        # Store inventory
        self._zappy._player._inventory = reply
        log.Log(', '.join(list(map(str, self._zappy._player._inventory))), color='Green')

    def _global_fork(self):
        self._send('Fork')
        log.Log(self._getAnswer(), color='Green')
        subprocess.Popen(["./zappy_ai", "-p", str(self._zappy._net._port), "-h", self._zappy._net._host, "-n", self._zappy._player._team])

    ############### UTILS #################    

    def _utils_epurTable(self, table):
        for x in table:
            if x == '': table.remove(x)
        return table
    
    def _utils_logPlayers(self):
        log.Head('Crew for ' + self._zappy._player._team)
        log.Head('Me:\t' + str(self._zappy._player._id) + ' (' + str(self._zappy._player._level) + ')')
        for i in range(len(self._players)):
            log.Head(('-' * 4) + ' ' + str(self._players[i]._id) + ' (' + str(self._players[i]._level) + ')')
        log.Head('_' * 30)
    
    def _utils_broadcast_newLevel(self):
        if self._levelUpBroadcast == True:
            self._global_broadcast(self._zappy._msgManager._set_level(self._zappy._player._level, self._zappy._player._team, self._zappy._player._id))
            self._levelUpBroadcast = False
