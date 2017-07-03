/*
** Team.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 14:35:40 2017 Antoine Dury
** Last update Sun Jul  2 20:38:39 2017 Antoine Dury
*/

#include "Zappy.h"

static int	teamCmdPropagation(t_zappyData *zd,
				   const int id)
{
  t_pos		pos;

  pos = getPlayerPos(zd, id);
  return (addGlobalResponse(zd, "pnw %d %d %d %d %d %s", id, pos.x, pos.y,
			    getPlayerOrientation(zd, id),
			    getPlayerLevel(zd, id),
			    getPlayerTeam(zd, id)) == SUCCESS ?
	  processGlobalMctCmd(zd) : FAILURE);
}

static int		initPlayer(t_zappyData *zd,
				   const int id)
{
  t_clientAction	action;

  zd->clients[id].mode = AI;
  zd->clients[id].connected = true;
  zd->clients[id].dead = false;
  zd->clients[id].pos.x = rand() % zd->width;
  zd->clients[id].pos.y = rand() % zd->height;
  zd->map[zd->clients[id].pos.y][zd->clients[id].pos.x].nbPlayers++;
  zd->clients[id].orientation = (rand() % 4) + 1;
  zd->clients[id].level = 1;
  zd->clients[id].resources[LINEMATE] = 0;
  zd->clients[id].resources[DERAUMERE] = 0;
  zd->clients[id].resources[SIBUR] = 0;
  zd->clients[id].resources[MENDIANE] = 0;
  zd->clients[id].resources[PHIRAS] = 0;
  zd->clients[id].resources[THYSTAME] = 0;
  zd->clients[id].nbFoods = 10;
  action.playerId = id;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (126.0 / zd->freq) * 1000000;
  action.action = EAT;
  action.param = NULL;
  return (addAction(zd, action));
}

static int	forkTeamCmd(t_zappyData *zd,
			    char **cmd,
			    const int teamId)
{
  int		playerId;
  int		eggId;

  eggId = getNextEgg(zd, teamId);
  playerId = zd->teams[teamId].eggs[eggId].playerId;
  zd->map[zd->clients[zd->currentClient].pos.y][zd->clients[zd->currentClient]
						.pos.x].nbPlayers--;
  zd->clients[zd->currentClient].pos.x = zd->teams[teamId].eggs[eggId].pos.x;
  zd->clients[zd->currentClient].pos.y = zd->teams[teamId].eggs[eggId].pos.y;
  zd->map[zd->clients[zd->currentClient].pos.y][zd->clients[zd->currentClient]
						.pos.x].nbPlayers++;
  zd->teams[teamId].eggs[eggId].playerId = 0;
  removeHatchingAction(zd, playerId);
  return (addResponse(zd, zd->currentClient, "%d",
		      zd->teams[teamId].maxPlayers -
		      zd->teams[teamId].nbPlayers) == SUCCESS
	  && addResponse(zd, zd->currentClient, "%d %d",
			 zd->width, zd->height) == SUCCESS &&
	  addGlobalResponse(zd, "eht %d\nebo %d",
			    zd->teams[teamId].eggs[eggId].eggId,
			    zd->teams[teamId].eggs[eggId].eggId) == SUCCESS &&
	  teamCmdPropagation(zd, zd->currentClient) == SUCCESS &&
	  infoLog("Client n°%d selected the team '%s' (connected with an egg)",
		  zd->currentClient,
		  cmd[0]) == SUCCESS ? SUCCESS : FAILURE);
}

int	teamCmd(t_zappyData *zd,
		char **cmd,
		const int nbParams)
{
  int	teamId;

  (void)nbParams;
  if (zd->teams[getTeamId(zd, cmd[0])].nbPlayers + 1 >
      zd->teams[getTeamId(zd, cmd[0])].maxPlayers ||
      zd->clients[zd->currentClient].connected)
    return (addResponse(zd, zd->currentClient, "ko"));
  if (initPlayer(zd, zd->currentClient) == FAILURE)
    return (FAILURE);
  teamId = getTeamId(zd, cmd[0]);
  zd->clients[zd->currentClient].teamId = teamId;
  zd->teams[teamId].players[zd->currentClient] = zd->currentClient;
  zd->teams[teamId].nbPlayers++;
  if (zd->teams[getTeamId(zd, cmd[0])].maxPlayers > zd->nbClients)
    return (forkTeamCmd(zd, cmd, teamId));
  return (addResponse(zd, zd->currentClient, "%d",
		      zd->teams[teamId].maxPlayers -
		      zd->teams[teamId].nbPlayers) == SUCCESS
	  && addResponse(zd, zd->currentClient, "%d %d",
			 zd->width, zd->height) == SUCCESS &&
	  teamCmdPropagation(zd, zd->currentClient) == SUCCESS &&
	  infoLog("Client n°%d selected the team '%s'", zd->currentClient,
		  cmd[0]) == SUCCESS ? SUCCESS : FAILURE);
}
