/*
** Commands1.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/GRAPHIC
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 14:00:39 2017 Antoine Dury
** Last update Sun Jul  2 20:39:52 2017 Antoine Dury
*/

#include "Zappy.h"

int	mszCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  (void)cmd;
  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  return (addResponse(zd, zd->currentClient, "msz %d %d", zd->width,
		      zd->height));
}

int	pinCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  int	id;
  t_pos	pos;

  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 2 || !cmd[1] || (id = atoi(cmd[1])) < 0 ||
	   !playerExists(zd, id) || zd->clients[id].teamId == -1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  pos = getPlayerPos(zd, id);
  return (addResponse(zd, zd->currentClient,
		      "pin %d %d %d %d %d %d %d %d %d %d",
		      id, pos.x, pos.y,
		      zd->clients[id].nbFoods,
		      zd->clients[id].resources[LINEMATE],
		      zd->clients[id].resources[DERAUMERE],
		      zd->clients[id].resources[SIBUR],
		      zd->clients[id].resources[MENDIANE],
		      zd->clients[id].resources[PHIRAS],
		      zd->clients[id].resources[THYSTAME]));
}

int	plvCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  int	id;

  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 2 || !cmd[1] || (id = atoi(cmd[1])) < 0 ||
	   !playerExists(zd, id) || zd->clients[id].teamId == -1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  return (addResponse(zd, zd->currentClient, "plv %d %d", id,
		       getPlayerLevel(zd, id)));
}

int	ppoCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  int	id;
  t_pos	pos;

  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 2 || !cmd[1] || (id = atoi(cmd[1])) < 0 ||
	   !playerExists(zd, id) || zd->clients[id].teamId == -1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  pos = getPlayerPos(zd, id);
  return (addResponse(zd, zd->currentClient, "ppo %d %d %d %d",
		      id, pos.x, pos.y, getPlayerOrientation(zd, id)));
}

int	sgtCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  (void)cmd;
  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  return (addResponse(zd, zd->currentClient, "sgt %d", zd->freq));
}
