/*
** Incantation.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:55:26 2017 Antoine Dury
** Last update Sun Jul  2 20:30:12 2017 Antoine Dury
*/

#include "Zappy.h"

const t_incantation g_incantation[] =
  {
    {1, {1, 0, 0, 0, 0, 0}},
    {2, {1, 1, 1, 0, 0, 0}},
    {2, {2, 0, 1, 0, 2, 0}},
    {4, {1, 1, 2, 0, 1, 0}},
    {4, {1, 2, 1, 3, 0, 0}},
    {6, {1, 2, 3, 0, 1, 0}},
    {6, {2, 2, 2, 2, 2, 1}}
  };

static int	sendBeginIncantation(t_zappyData *zd)
{
  int		i;
  char		msg[BUFFER_SIZE];
  t_pos		pos;

  i = -1;
  bzero(msg, BUFFER_SIZE);
  pos = getPlayerPos(zd, zd->currentClient);
  if ((sprintf(msg, "%d", zd->currentClient)) < 0)
    return (printPerror("sprintf"));
  while (++i < SOMAXCONN)
    {
      if (zd->clients[i].fdType == FD_CLIENT && zd->clients[i].connected &&
	  zd->clients[i].pos.x == pos.x && zd->clients[i].pos.y == pos.y &&
	  i != zd->currentClient)
        {
          if ((sprintf(msg + strlen(msg), " %d", i)) < 0)
            return (printPerror("sprintf"));
        }
    }
  return (addGlobalResponse(zd, "pic %d %d %d %s", pos.x, pos.y,
			    getPlayerLevel(zd, zd->currentClient), msg));
}

static bool checkIncantation(t_zappyData *zd, const int playerId,
			     const t_incantation incantation)
{
  return (checkPlayers(zd, playerId, incantation.nbPlayers) &&
	  checkMinerals(zd, playerId, incantation));
}

static int	proccessEndIncantation(t_zappyData *zd, const t_pos pos,
				       const int playerId)
{
  int		i;
  int		j;

  i = -1;
  while (++i < NB_RESOURCES)
    {
      j = -1;
      zd->map[pos.y][pos.x].resources[i] -=
	g_incantation[getPlayerLevel(zd, playerId) - 1].resources[i];
      while (++j < g_incantation[getPlayerLevel(zd, playerId) - 1].
	     resources[i])
        zd->map[rand() % zd->height][rand() % zd->width].resources[i]++;
    }
  i = -1;
  while (++i < SOMAXCONN)
    {
      if (zd->clients[i].fdType == FD_CLIENT && zd->clients[i].connected &&
	  zd->clients[i].pos.x == pos.x && zd->clients[i].pos.y == pos.y)
        {
          zd->clients[i].level++;
          if (addIncantationResponse(zd, i) == FAILURE)
            return (FAILURE);
        }
    }
  return (processGlobalMctCmd(zd));
}

int	processIncantation(t_zappyData *zd, char **cmd, const int actionId)
{
  int	playerId;
  t_pos	pos;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  pos = getPlayerPos(zd, playerId);
  if (checkIncantation(zd, playerId,
		       g_incantation[getPlayerLevel(zd, playerId) - 1]))
    {
      if (addResponse(zd, playerId, "Current level: %d",
		      getPlayerLevel(zd, playerId) + 1) == FAILURE ||
	  addGlobalResponse(zd, "pie %d %d 1", pos.x, pos.y) == FAILURE)
        return (FAILURE);
    }
  else
    return (addResponse(zd, playerId, "ko") == SUCCESS ?
	    addGlobalResponse(zd, "pie %d %d 0", pos.x, pos.y) : FAILURE);
  return (proccessEndIncantation(zd, pos, playerId));
}

int			incantationCmd(t_zappyData *zd, char **cmd,
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
  if (checkIncantation(zd, zd->currentClient,
		       g_incantation[getPlayerLevel(zd,
						    zd->currentClient) - 1])
      ? addResponse(zd, zd->currentClient, "Elevation underway") :
      addResponse(zd, zd->currentClient, "ko") == FAILURE)
    return (FAILURE);
  action.playerId = zd->currentClient;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (300.0 / zd->freq) * 1000000;
  action.action = INCANTATION;
  action.param = NULL;
  return (sendBeginIncantation(zd) == SUCCESS ? addAction(zd, action)
	  : FAILURE);
}
