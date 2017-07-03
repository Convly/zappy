/*
** Movement2.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 27 15:13:02 2017 Antoine Dury
** Last update Sun Jul  2 20:34:35 2017 Antoine Dury
*/

#include "Zappy.h"

static int	ppoCmdPropagation(t_zappyData *zd,
				  const int playerId)
{
  t_pos		pos;

  pos = getPlayerPos(zd, playerId);
  return (addGlobalResponse(zd, "ppo %d %d %d %d", playerId, pos.x, pos.y,
			    getPlayerOrientation(zd, playerId)));
}

int	processForward(t_zappyData *zd,
		       char **cmd,
		       const int actionId)
{
  int	playerId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  zd->map[zd->clients[playerId].pos.y][zd->clients[playerId].pos.x].
    nbPlayers--;
  if (zd->clients[playerId].orientation == NORTH)
    zd->clients[playerId].pos.y + 1 >= zd->height ?
      zd->clients[playerId].pos.y = 0 : zd->clients[playerId].pos.y++;
  else if (zd->clients[playerId].orientation == SOUTH)
    zd->clients[playerId].pos.y - 1 < 0 ? zd->clients[playerId].pos.y =
      zd->height - 1 : zd->clients[playerId].pos.y--;
  else if (zd->clients[playerId].orientation == EAST)
    zd->clients[playerId].pos.x + 1 >= zd->width ?
      zd->clients[playerId].pos.x = 0 : zd->clients[playerId].pos.x++;
  else if (zd->clients[playerId].orientation == WEST)
    zd->clients[playerId].pos.x - 1 < 0 ? zd->clients[playerId].pos.x =
      zd->width - 1 : zd->clients[playerId].pos.x--;
  zd->map[zd->clients[playerId].pos.y][zd->clients[playerId].pos.x].
    nbPlayers++;
  return (addResponse(zd, playerId, "ok") == SUCCESS ?
	  ppoCmdPropagation(zd, playerId) == SUCCESS ?
	  debugLog("Player n°%d move forward", playerId) : FAILURE : FAILURE);
}

int	processLeft(t_zappyData *zd,
		    char **cmd,
		    const int actionId)
{
  int	playerId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  if (zd->clients[playerId].orientation == NORTH)
    zd->clients[playerId].orientation = WEST;
  else
    zd->clients[playerId].orientation -= 1;
  return (addResponse(zd, playerId, "ok") == SUCCESS ?
	  ppoCmdPropagation(zd, playerId) == SUCCESS ?
	  debugLog("Player n°%d move left", playerId) : FAILURE : FAILURE);
}

int	processRight(t_zappyData *zd,
		     char **cmd,
		     const int actionId)
{
  int	playerId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  if (zd->clients[playerId].orientation == WEST)
    zd->clients[playerId].orientation = NORTH;
  else
    zd->clients[playerId].orientation += 1;
  return (addResponse(zd, playerId, "ok") == SUCCESS ?
	  ppoCmdPropagation(zd, playerId) == SUCCESS ?
	  debugLog("Player n°%d move right", playerId) : FAILURE : FAILURE);
}
