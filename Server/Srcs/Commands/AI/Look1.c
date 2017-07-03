/*
** Look1.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:55:32 2017 Antoine Dury
** Last update Sun Jul  2 20:31:28 2017 Antoine Dury
*/

#include "Zappy.h"

char		*g_response = NULL;
const char	*g_minerals[] = {"linemate", "deraumere", "sibur", "mendiane",
				 "phiras", "thystame"};

static int	lookMineralsSquare(const t_zappyMap map)
{
  int		i;
  int		j;

  i = -1;
  while (++i < NB_RESOURCES)
    {
      j = -1;
      while (++j < map.resources[i])
	{
	  if ((g_response = reallocat(g_response, " ")) == NULL ||
	      (g_response = reallocat(g_response, g_minerals[i])) == NULL)
	    return (FAILURE);
	}
    }
  return ((g_response = reallocat(g_response, ",")) == NULL ?
	  FAILURE : SUCCESS);
}

int	lookSquare(const t_zappyMap map)
{
  int	i;

  i = -1;
  while (++i < map.nbPlayers)
    {
      if ((g_response = reallocat(g_response, " player")) == NULL)
	return (FAILURE);
    }
  i = -1;
  while (++i < map.nbFoods)
    {
      if ((g_response = reallocat(g_response, " food")) == NULL)
	return (FAILURE);
    }
  return (lookMineralsSquare(map));
}

static void	processLookLoop(t_zappyData *zd,
				t_pos *pos,
				const int vision,
				const int nbUnits)
{
  if (zd->currentClientOrientation == NORTH)
    {
      processNorthLook(zd, *pos, vision, nbUnits);
      pos->y++;
    }
  else if (zd->currentClientOrientation == SOUTH)
    {
      processSouthLook(zd, *pos, vision, nbUnits);
      pos->y--;
    }
  else if (zd->currentClientOrientation == EAST)
    {
      processEastLook(zd, *pos, vision, nbUnits);
      pos->x++;
    }
  else if (zd->currentClientOrientation == WEST)
    {
      processWestLook(zd, *pos, vision, nbUnits);
      pos->x--;
    }
}

int	processLook(t_zappyData *zd,
		    char **cmd,
		    const int actionId)
{
  int	depth;
  int	playerId;
  t_pos pos;

  (void)cmd;
  depth = -1;
  playerId = zd->actions[actionId].playerId;
  pos.x = zd->clients[playerId].pos.x;
  pos.y = zd->clients[playerId].pos.y;
  if ((g_response = malloc(sizeof(char) * 1)) == NULL)
    return (printPerror("malloc"));
  bzero(g_response, 1);
  if ((g_response = reallocat(g_response, "[")) == NULL)
    return (FAILURE);
  zd->currentClientOrientation = zd->clients[playerId].orientation;
  while (++depth < zd->clients[playerId].level + 1)
    processLookLoop(zd, &pos, depth, (depth * 2) + 1);
  if ((g_response = reallocat(g_response, "]")) == NULL)
    return (FAILURE);
  g_response[strlen(g_response) - 2] = ' ';
  if (addResponse(zd, playerId, g_response) == FAILURE)
    return (FAILURE);
  free(g_response);
  return (SUCCESS);
}

int			lookCmd(t_zappyData *zd,
				char **cmd,
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
  action.duration = (7.0 / zd->freq) * 1000000;
  action.action = LOOK;
  action.param = NULL;
  return (addAction(zd, action));
}
