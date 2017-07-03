import log
import zappy
import random
import subprocess
import queue

class Manager:
    def __init__(self, engine):
        self.dd = ['Right', 'Left']
        self._run = True
        self._sleep = False
        self._incant = False
        self._needHelp = False
        self._answer = True
        self._freeze = False
        self._lWa = 0
        self._msg = queue.LifoQueue(0)
        self._engine = engine

    
    def _getAnswer(self, ignoreCalls=False, recurse=0):
        self._engine._getServerReply()
        reply = self._engine._cmds.get()
        if 'message' in reply:
            if not ignoreCalls:
                self._msg.put(reply)
            itt = recurse + 1
            if itt > 10:
                return 'ok'
            return self._getAnswer(recurse=itt)
        if reply == 'dead': self._action_dead(); exit(0)
        return reply
    

    def _action_handleMessage(self, payload):
        table = payload.split(',')
        dir = int(table[0].split(' ')[1])
        message = table[1]

        log.Fail(payload)

        if 'I HEARD YOU BOBBY' in message:
            self._answer = True

        if 'You\'re a free elfe Bobby!' in message:
            self._freeze = False
            return False

        if 'lem_help_plz:' in message:
            lvl = int(message.split(':')[1])
            if lvl == self._engine._zappy._player._level:
                if dir == 0:
                    self._freeze = True
                    return False
                else:
                    self._action_goToTarget(dir, ignoreCalls=True)
                self._action_broadcast('I HEARD YOU BOBBY', ignoreCalls=True)

    ###################### NEED ############################

    def _clearMsg(self):
        while self._msg.qsize() > 0:
            self._action_handleMessage(self._msg.get())

    def _need_food(self):
        if not self._run: return False
        self._updateInventory()
        if self._sleep and self._engine._zappy._player._inventory[0] < 10:
            self._sleep = False
        elif self._engine._zappy._player._inventory[0] > 30:
            self._sleep = True
        
        if not self._sleep:
            log.Inform('Food level is below normal, searching some meat...')
            if self._question_foodOnCell():
                self._action_takeFood()
            else:
                dest = self._question_foodAround()
                print(dest)
                if dest:
                    self._action_goToDestination(dest)
                else:
                    log.Inform('Can\'t find food here, going to a random position')
                    if self._question_randomChoice() == True:
                        self._action_goForward()
                    else:
                        self._action_turn()
            return True
        return False
    
    def _need_ressource(self):
        if not self._run: return False
        if self._freeze: return True
        clevel = self._engine._zappy._player._level
        nr = [0 if t < 0 else t for t in [self._levels[clevel - 1][x] - self._engine._zappy._player._inventory[x] for x in range(1, 7)]]
        if not self._question_enoughRessourceForCast(nr):
            log.Inform('Need some ressource (' + ', '.join(list(map(str, nr))) + ')')
            for x in range(len(nr)):
                if nr[x] > 0 and self._search_and_find(x):
                    return True
            log.Inform('Can\'t find appropriate ressource here, going to a random position')
            if self._question_randomChoice() == True:
                self._action_goForward()
            else:
                self._action_turn()
        else:
            log.Inform('It\'s time to level up Bobby!')
            self._actions_cast()
        return True
    
    def _need_help(self):
        if not self._run: return False
        log.Inform("Need help", underline=True)

    def _need_me(self):
        if not self._run: return False
        log.Inform("Need me", underline=True)

    ###################### ACTION ############################

    def _search_and_find(self, idx):
        rtype = self._minerals[idx]
        if self._question_ressourceOnCell(rtype):
            self._action_takeRessource(rtype)
        else:
            dest = self._question_ressourcesAround(rtype)
            if dest:
                log.Inform('Going ' + dest + ' to steal some ' + rtype)
                self._action_goToDestination(dest)
            else:
                return False
        return True
    
    def _action_goToTarget(self, target, ignoreCalls=False):
        commands = self._targets[target - 1]
        log.Head(str(dir) + '   -   ' + ', '.join(commands))
        for i in commands:
            if i == 'Forward':
                self._action_goForward(ignoreCalls=ignoreCalls)
            else:
                self._action_turn(dir=i, ignoreCalls=ignoreCalls)

    def _updateInventory(self):
        if not self._run: return False
        self._send('Inventory')
        reply = self._getAnswer()
        while not '[' in reply or not ']' in reply:
            reply = self._getAnswer()
        self._engine._zappy._player._inventory = self.epurTable(reply)
        log.Log(', '.join(list(map(str, self._engine._zappy._player._inventory))), color='Green')

    def _action_takeFood(self):
        if not self._run: return False
        self._action_takeRessource('food')

    def _action_takeRessource(self, rtype):
        if not self._run: return False
        self._send('Take ' + rtype)
        reply = self._getAnswer()
        log.Log(reply, color='Green')
        self._updateInventory()

    def _action_dropRessource(self, rtype):
        if not self._run: return False
        self._send('Set ' + rtype)
        log.Log(self._getAnswer(), color='Green')        
        self._updateInventory()

    def _actions_cast(self):
        if not self._run: return False

        ddataP = self._action_checkPlayerForCast()
        if not ddataP[1]: return False
        if self._freeze: return False

        lock = True
        while lock:
            rtype = self._question_isAnythingOnCell()
            if rtype: self._action_takeRessource(rtype)
            else: lock = False

        table = self._levels[self._engine._zappy._player._level - 1][1:]
        for k in range(len(table)):
            for t in range(table[k]):
                self._action_dropRessource(self._minerals[k])

        ddataP = self._action_checkPlayerForCast()
        if not ddataP[1]: return False
        
        self._send('Incantation')
        reply = self._getAnswer()
        log.Log(reply, color='Green')
        if reply == 'Elevation underway':
            self._incant = True
        reply = self._getAnswer()
        if 'Current level:' in reply:
            self._engine._zappy._player._level += 1
            if ddataP[0] > 1: self._action_broadcast('You\'re a free elfe Bobby!')
            self._freeze = False
            log.Log(reply, color='Green', underline=True, bold=True)
        self._incant == False
        return True
        
    def _action_checkPlayerForCast(self):
        target = self._levels[self._engine._zappy._player._level - 1][0]
        amount = self._question_ressourceOnCell('player', amount=True)
        r = target - amount
        if  r > 0:
            if self._answer:
                log.Inform('Need ' + str(r) + ' more players')
                self._action_broadcast('lem_help_plz:' + str(self._engine._zappy._player._level))
                self._answer = False
            else:
                self._lWa += 1
                if self._lWa > 40:
                    self._lWa = 0
                    self._answer = True
                    self._action_reproduce()
            return [amount, False]
        elif r < 0:
            self._send('Eject')
            log.Log(self._getAnswer(), color='Green')
            return [amount, False]
        return [amount, True]

    def _action_goForward(self, ignoreCalls=False):
        if not self._run: return False
        self._send('Forward')
        log.Log(self._getAnswer(ignoreCalls=ignoreCalls), color='Green')

    def _action_turn(self, dir='Random', ignoreCalls=False):
        if not self._run: return False

        if dir == 'Random': tdest = self.dd[random.randint(0, 1)]
        elif dir in self.dd: tdest = dir
        else: return False

        self._send(tdest)
        log.Log(self._getAnswer(ignoreCalls=ignoreCalls), color='Green')
    
    def _action_dead(self):
        self._run = False
        self._engine._die()
        return False

    def _action_broadcast(self, payload, ignoreCalls=False):
        if not self._run: return False
        self._send('Broadcast ' + payload)
        log.Log(self._getAnswer(ignoreCalls=ignoreCalls), color='Green')

    def _action_goToDestination(self, dest, ignoreCalls=False):
        if not self._run: return False
        if dest == 'Forward':
            self._action_goForward(ignoreCalls=ignoreCalls)
        elif dest in self.dd:
            o = self.dd[(self.dd.index(dest) + 1) % 2]
            self._action_turn(dir=dest, ignoreCalls=ignoreCalls)
            self._action_goForward(ignoreCalls=ignoreCalls)
            self._action_turn(dir=o, ignoreCalls=ignoreCalls)

    def _action_scan(self):
        if not self._run: return False
        self._send('Look')
        reply = self._getAnswer()
        while not '[' in reply or not ']' in reply or not 'player' in reply:
            reply = self._getAnswer()
        reply = reply.replace(']', '').replace('[', '').split(',')
        for i in range(len(reply)):
            reply[i] = self._epurTable(reply[i].split(' '))
        self._engine._zappy._player._cells = reply

        for i in range(len(reply)):
            log.Log('Cell ' + str(i) + ': ' + ', '.join(reply[i]), color='Green')

    def _action_reproduce(self):
        if not self._run: return False
        log.Inform('Lem smash Bobby!')
        self._send('Fork')
        subprocess.Popen(["./zappy_ai", "-p", str(self._engine._zappy._net._port), "-h", "localhost", "-n", self._engine._zappy._team])
        log.Log(self._getAnswer(), color='Green')

    ###################### QUESTION ############################  

    def _question_isAnythingOnCell(self):
        self._action_scan()
        table = self._minerals + ['food']
        ccell = self._engine._zappy._player._cells[0]
        payload = [ccell.count(mineral) for mineral in table]
        for x in range(len(payload)):
            if payload[x] > 0: return table[x]
        return False

    def _question_foodOnCell(self):
        if not self._run: return False
        return self._question_ressourceOnCell('food')

    def _question_foodAround(self):
        if not self._run: return False
        return self._question_ressourcesAround('food')

    def _question_enoughRessourceForCast(self, nr):
        if not self._run: return False
        return sum(nr) == 0

    def _question_ressourcesAround(self, rtype):
        if not self._run: return False
        k = 0
        n = 2
        for i in range(1, self._engine._zappy._player._level + 1):
            k += n
            n += 2
            s = 2 * i
            if self._engine._zappy._player._cells[k].count(rtype):
                log.Inform('Found some food on cell ' + str(k))
                return 'Forward'
            for xwing in range(1, s // 2 + 1):
                if self._engine._zappy._player._cells[k - xwing].count(rtype):
                    log.Inform(rtype + ' on ' + str(k - xwing))
                    return 'Left'
                elif self._engine._zappy._player._cells[k + xwing].count(rtype):
                    log.Inform(rtype + ' on ' + str(k + xwing))
                    return 'Right'
        return None

    def _question_ressourceOnCell(self, rtype, amount=False):
        if not self._run: return False
        self._action_scan()
        ramount = self._engine._zappy._player._cells[0].count(rtype)
        return ramount if amount else ramount > 0


    def _question_doIHaveFriend(self, id, label):
        if not self._run: return False
        log.Inform(label)

    def _question_canFriendHelpMe(self, id, label):
        if not self._run: return False
        log.Inform(label)

    def _question_randomChoice(self):
        if not self._run: return False
        return random.randint(0, 1)

 ################## UTILS ######################

    def epurTable(self, table):

        return table
    
    def _epurTable(self, table):
        for x in table:
            if x == '': table.remove(x)
        return table