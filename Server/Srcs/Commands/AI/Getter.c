/*
** Getter.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:54:47 2017 Antoine Dury
** Last update Sun Jul  2 20:27:43 2017 Antoine Dury
*/

#include "Zappy.h"

int	processInventory(t_zappyData *zd,
			 char **cmd,
			 const int actionId)
{
  int	playerId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  return (addResponse(zd, playerId, "[ food %d, linemate %d, \
deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d ]",
		      zd->clients[playerId].nbFoods,
		      zd->clients[playerId].resources[LINEMATE],
		      zd->clients[playerId].resources[DERAUMERE],
		      zd->clients[playerId].resources[SIBUR],
		      zd->clients[playerId].resources[MENDIANE],
		      zd->clients[playerId].resources[PHIRAS],
		      zd->clients[playerId].resources[THYSTAME]));
}

int			inventoryCmd(t_zappyData *zd, char **cmd,
				     const int nbParams)
{
  t_clientAction	action;

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
  action.duration = (1.0 / zd->freq) * 1000000;
  action.action = INVENTORY;
  action.param = NULL;
  return (addAction(zd, action));
}

int	connectNbrCmd(t_zappyData *zd, char **cmd, const int nbParams)
{
  (void)cmd;
  if (!rightMode(zd, AI))
    return (rightMode(zd, UNDEFINED) ?
	    addResponse(zd, zd->currentClient, "ko") :
	    addResponse(zd, zd->currentClient, "suc"));
  else if (nbParams != 1)
    return (addResponse(zd, zd->currentClient, "ko"));
  return (addResponse(zd, zd->currentClient, "%d",
		      zd->teams[zd->clients[zd->currentClient].teamId].
		      maxPlayers -
		      zd->teams[zd->clients[zd->currentClient].teamId].
		      nbPlayers));
}
