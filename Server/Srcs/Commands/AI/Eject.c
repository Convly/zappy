/*
** Eject.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:54:25 2017 Antoine Dury
** Last update Sun Jul 02 19:30:08 2017 Antoine Dury
*/

#include "Zappy.h"

static int	getEjectPos(t_zappyData *zd, const t_clientData player,
			    const t_pos pos)
{
  if ((player.pos.y - 1 < 0 ? zd->height - 1 : player.pos.y - 1) == pos.y &&
      player.pos.x == pos.x)
    return (player.orientation == NORTH ? 5 : player.orientation == SOUTH ? 1 :
	    player.orientation == WEST ? 3 : 7);
  else if ((player.pos.y + 1 >= zd->height ? 0 : player.pos.y + 1) == pos.y &&
	   player.pos.x == pos.x)
    return (player.orientation == NORTH ? 1 : player.orientation == SOUTH ? 5 :
	    player.orientation == WEST ? 7 : 3);
  else if ((player.pos.x - 1 < 0 ? zd->width - 1 : player.pos.x - 1) == pos.x
	   && player.pos.y == pos.y)
    return (player.orientation == NORTH ? 3 : player.orientation == SOUTH ? 7 :
	    player.orientation == WEST ? 1 : 5);
  return (player.orientation == NORTH ? 7 : player.orientation == SOUTH ? 3 :
	  player.orientation == WEST ? 5 : 1);
}

static int	ejectPlayer(t_zappyData *zd, const int senderId,
			    const int receiverId)
{
  zd->map[zd->clients[receiverId].pos.y][zd->clients[receiverId].pos.x].
    nbPlayers--;
  if (zd->clients[senderId].orientation == NORTH)
    zd->clients[receiverId].pos.y + 1 >= zd->height ?
      zd->clients[receiverId].pos.y = 0 : zd->clients[receiverId].pos.y++;
  else if (zd->clients[senderId].orientation == SOUTH)
    zd->clients[receiverId].pos.y - 1 < 0 ? zd->clients[receiverId].pos.y =
      zd->height - 1 : zd->clients[receiverId].pos.y--;
  else if (zd->clients[senderId].orientation == EAST)
    zd->clients[receiverId].pos.x + 1 >= zd->width ?
      zd->clients[receiverId].pos.x = 0 : zd->clients[receiverId].pos.x++;
  else if (zd->clients[senderId].orientation == WEST)
    zd->clients[receiverId].pos.x - 1 < 0 ? zd->clients[receiverId].pos.x =
      zd->width - 1 : zd->clients[receiverId].pos.x--;
  zd->map[zd->clients[receiverId].pos.y][zd->clients[receiverId].pos.x].
    nbPlayers++;
  return (addGlobalResponse(zd, "ppo %d %d %d %d", receiverId,
			    zd->clients[receiverId].pos.x,
			    zd->clients[receiverId].pos.y,
			    zd->clients[receiverId].orientation));
}

int	processEject(t_zappyData *zd, char **cmd, const int actionId)
{
  int	i;
  int	playerId;
  t_pos	playerPos;

  (void)cmd;
  i = -1;
  playerId = zd->actions[actionId].playerId;
  playerPos = zd->clients[playerId].pos;
  if (addGlobalResponse(zd, "pex %d", playerId) == FAILURE)
    return (FAILURE);
  while (++i < SOMAXCONN)
    {
      if (i != playerId && playerExists(zd, i) && zd->clients[i].pos.x ==
	  playerPos.x && zd->clients[i].pos.y == playerPos.y)
        {
          if (ejectPlayer(zd, playerId, i) == FAILURE)
            return (FAILURE);
          if (addResponse(zd, i, "eject: %d",
			  getEjectPos(zd, zd->clients[i], playerPos))
	      == FAILURE)
	    return (FAILURE);
        }
    }
  return (addResponse(zd, playerId, "ok"));
}

int			ejectCmd(t_zappyData *zd, char **cmd,
				 const int nbParams)
{
  t_clientAction	action;

  (void)cmd;
  if (!rightMode(zd, AI))
    return (rightMode(zd, UNDEFINED) ?
	    addResponse(zd, zd->currentClient, "ko") :
	    addResponse(zd, zd->currentClient, "suc"));
  else if (nbParams != 1 ||
	   zd->map[zd->clients[zd->currentClient].pos.y]
	   [zd->clients[zd->currentClient].pos.x].nbPlayers < 2)
    return (addResponse(zd, zd->currentClient, "ko"));
  action.playerId = zd->currentClient;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (7.0 / zd->freq) * 1000000;
  action.action = EJECT;
  action.param = NULL;
  return (addAction(zd, action));
}
