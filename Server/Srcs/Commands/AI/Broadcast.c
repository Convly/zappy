/*
** Broadcast.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Fri Jun 30 15:51:26 2017 Antoine Dury
** Last update Sat Jul 01 16:54:09 2017 Antoine Dury
*/

#include "Zappy.h"

static int	getBroadcastDirection(t_zappyData *zd,
				      const t_clientData receiver,
				      const t_clientData sender)
{
  int		x;
  int		y;

  x = getClosestPath(sender.pos.x, receiver.pos.x, zd->width / 2);
  y = getClosestPath(sender.pos.y, receiver.pos.y, zd->height / 2);
  return (getSoundDirection(zd, receiver, getRelativePos(x, zd->width),
			    getRelativePos(y, zd->height)));
}

int	processBroadcast(t_zappyData *zd, char **cmd, const int actionId)
{
  int	i;
  int	playerId;

  (void)cmd;
  i = -1;
  playerId = zd->actions[actionId].playerId;
  while (++i < SOMAXCONN)
    {
      if (i != playerId && playerExists(zd, i))
        {
          if (playerSamePos(zd->clients[playerId].pos, zd->clients[i].pos) ?
	      addResponse(zd, i, "message 0, %s",
			  zd->actions[actionId].param) :
	      addResponse(zd, i, "message %d, %s",
			  getBroadcastDirection(zd, zd->clients[i],
						zd->clients[playerId]),
			  zd->actions[actionId].param) == FAILURE)
            return (FAILURE);
        }
    }
  return (addGlobalResponse(zd, "pbc %d %s", playerId,
			    zd->actions[actionId].param) == SUCCESS ?
	  addResponse(zd, playerId, "ok") : FAILURE);
}

static int		broadcastAction(t_zappyData *zd, char *msg)
{
  t_clientAction	action;

  msg[strlen(msg) - 1] = '\0';
  action.playerId = zd->currentClient;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (7.0 / zd->freq) * 1000000;
  action.action = BROADCAST;
  if ((action.param = strdup(msg)) == NULL)
    return (printPerror("strdup"));
  free(msg);
  return (addAction(zd, action));
}

int	broadcastCmd(t_zappyData *zd, char **cmd, const int nbParams)
{
  int 	i;
  char	*msg;

  i = 0;
  if (!rightMode(zd, AI))
    return (rightMode(zd, UNDEFINED) ?
	    addResponse(zd, zd->currentClient, "ko") :
	    addResponse(zd, zd->currentClient, "suc"));
  else if (nbParams < 2 || !cmd[1])
    return (addResponse(zd, zd->currentClient, "ko"));
  if ((msg = malloc(sizeof(char) * 1)) == NULL)
    return (printPerror("malloc"));
  bzero(msg, 1);
  while (++i < nbParams && cmd[i])
    {
      if ((msg = reallocat(msg, cmd[i])) == NULL ||
	  (msg = reallocat(msg, " ")) == NULL)
	return (FAILURE);
    }
  return (broadcastAction(zd, msg));
}
