import time
import sys
import net
import random

class Player:
    def __init__(self, team):
        self._team = team
        self._level = 1
        self._inventory = [10, 0, 0, 0, 0, 0, 0]
        self._cells = []
        self._id = int(str("%.5f" % time.time()).replace('.', ''))

class Ally:
    def __init__(self, id, level, team):
        self._team = team
        self._level = level
        self._id = id

class msgManager:
    def __init__(self):
        self._commands = ['REGISTER', 'INFORM', 'UNREGISTER', 'SET_LEADER', 'SET_LEVEL', 'REQUIRE_HELP']

    def _register(self, id, level, team):
        return ':'.join(['REGISTER', str(id), str(level), team])
    
    def _inform(self, targetId, id, level, team):
        return ':'.join(['INFORM', str(targetId), str(id), str(level), team])
    
    def _unregister(self, id, team):
        return ':'.join(['UNREGISTER', str(id), team])
    
    def _set_leader(self, lvl, team, leaderID):
        return ':'.join(['SET_LEADER', str(lvl), team, str(leaderID)])
    
    def _set_level(self, lvl, team, playerID):
        return ':'.join(['SET_LEVEL', str(lvl), team, str(playerID)])
    
    def _require_support(self, lvl, team, leaderID, playerID):
        return ':'.join(['REQUIRE_HELP', str(lvl), team, str(leaderID), str(playerID)])
    
class Zappy:
    def __init__(self, port, name, host):
        # Initialisation for parameters
        self._net = net.Net(host, port)
        self._player = Player(name)
        self._msgManager = msgManager()