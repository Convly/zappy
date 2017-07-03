/*
** Fork.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:54:39 2017 Antoine Dury
** Last update Sun Jul  2 20:27:03 2017 Antoine Dury
*/

#include "Zappy.h"

int	getNextEgg(const t_zappyData *zd, const int teamId)
{
  int	i;

  i = -1;
  while (++i < MAX_ACTIONS)
    {
      if (zd->teams[teamId].eggs[i].playerId != 0)
        return (i);
    }
  return (-1);
}

void	removeHatchingAction(t_zappyData *zd, const int playerId)
{
  int	i;

  i = -1;
  while (++i < MAX_ACTIONS)
    {
      if (zd->actions[i].playerId == playerId &&
	  zd->actions[i].action == HATCHING)
        {
          zd->actions[i].playerId = 0;
          return;
        }
    }
}

int	processHatching(t_zappyData *zd, char **cmd, const int actionId)
{
  int	playerId;
  int	teamId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  teamId = zd->clients[playerId].teamId;
  zd->teams[teamId].maxPlayers--;
  if (addGlobalResponse(zd, "edi %d",
			zd->teams[teamId].eggs[getNextEgg(zd, teamId)].eggId)
      == FAILURE)
    return (FAILURE);
  zd->teams[teamId].eggs[getNextEgg(zd, teamId)].playerId = 0;
  zd->teams[teamId].nbEggs--;
  return (SUCCESS);
}

int			processFork(t_zappyData *zd, char **cmd,
				    const int actionId)
{
  t_clientAction	action;
  int			playerId;
  int			teamId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  teamId = zd->clients[playerId].teamId;
  zd->teams[teamId].maxPlayers++;
  zd->teams[teamId].eggs[zd->teams[teamId].nbEggs].playerId = playerId;
  zd->teams[teamId].eggs[zd->teams[teamId].nbEggs].eggId = zd->nbEggs;
  zd->teams[teamId].eggs[zd->teams[teamId].nbEggs].pos =
    getPlayerPos(zd, playerId);
  zd->nbEggs++;
  zd->teams[teamId].nbEggs++;
  action.playerId = playerId;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (600.0 / zd->freq) * 1000000;
  action.action = HATCHING;
  action.param = NULL;
  return (addAction(zd, action) == SUCCESS ?
	  addGlobalResponse(zd, "enw %d %d %d %d", zd->nbEggs - 1, playerId,
			    zd->clients[playerId].pos.x,
			    zd->clients[playerId].pos.y)
	  == SUCCESS ? addResponse(zd, playerId, "ok") : FAILURE : FAILURE);
}

int			forkCmd(t_zappyData *zd, char **cmd,
				const int nbParams)
{
  t_clientAction	 action;

  (void)cmd;
  if (!rightMode(zd, AI))
    return (rightMode(zd, UNDEFINED) ?
	    addResponse(zd, zd->currentClient, "ko") :
	    addResponse(zd, zd->currentClient, "suc"));
  else if (nbParams != 1)
    return (addResponse(zd, zd->currentClient, "ko"));
  action.playerId = zd->currentClient;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (42.0 / zd->freq) * 1000000;
  action.action = FORK;
  action.param = NULL;
  return (addGlobalResponse(zd, "pfk %d", zd->currentClient) == SUCCESS ?
	  addAction(zd, action) : FAILURE);
}
