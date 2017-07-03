/*
** Action.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 26 16:19:44 2017 Antoine Dury
** Last update Sun Jul  2 20:56:29 2017 Antoine Dury
*/

#include "Zappy.h"

static t_commands	g_commands[] =
  {
    {"Broadcast", processBroadcast},
    {"Eject", processEject},
    {"Fork", processFork},
    {"Forward", processForward},
    {"Incantation", processIncantation},
    {"Inventory", processInventory},
    {"Left", processLeft},
    {"Look", processLook},
    {"Right", processRight},
    {"Set", processSet},
    {"Take", processTake},
    {"Eat", processEat},
    {"Die", processDie},
    {"Hatching", processHatching},
    {NULL, NULL}
  };

int	addAction(t_zappyData *zd,
		  t_clientAction action)
{
  int	i;

  i = -1;
  while (++i < MAX_ACTIONS)
    {
      if (zd->actions[i].playerId == 0)
        {
          zd->actions[i] = action;
          return (SUCCESS);
        }
    }
  return (SUCCESS);
}

int	getNextAction(t_zappyData *zd)
{
  int	i;

  i = -1;
  while (++i < MAX_ACTIONS)
    {
      if (zd->actions[i].playerId != 0 && zd->actions[i].action != EAT &&
	  zd->actions[i].action != DIE && zd->actions[i].action != HATCHING)
        return (i);
    }
  return (-1);
}

int	getNextFeeding(t_zappyData *zd)
{
  int	i;
  int	nextFeeding;

  i = -1;
  nextFeeding = -1;
  while (++i < MAX_ACTIONS)
    {
      if (zd->actions[i].playerId != 0 && (zd->actions[i].action == EAT ||
					   zd->actions[i].action == DIE ||
					   zd->actions[i].action == HATCHING))
        {
          if (nextFeeding == -1 || zd->actions[i].duration < nextFeeding)
            nextFeeding = zd->actions[i].duration;
        }
    }
  return (nextFeeding);
}

static int		processFeeding(t_zappyData *zd)
{
  int			i;
  struct timeval	tv;

  i = -1;
  if (gettimeofday(&tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  while (++i < MAX_ACTIONS)
    {
      if (zd->actions[i].playerId != 0 &&
	  (zd->actions[i].action == EAT || zd->actions[i].action == DIE ||
	   zd->actions[i].action == HATCHING) &&
	  (zd->actions[i].tv.tv_sec * 1000000) + zd->actions[i].tv.tv_usec +
	  zd->actions[i].duration <= (tv.tv_sec * 1000000) + tv.tv_usec)
        {
          if (playerExists(zd, zd->actions[i].playerId) ||
	      zd->actions[i].action == HATCHING)
	    if (g_commands[zd->actions[i].action].exec(zd, NULL, i) == FAILURE)
	      return (FAILURE);
          zd->actions[i].playerId = 0;
          if (zd->actions[i].param)
            free(zd->actions[i].param);
        }
    }
  return (SUCCESS);
}

int			processAction(t_zappyData *zd,
				      const int actionId)
{
  struct timeval	tv;

  if (processFeeding(zd) == FAILURE)
    return (FAILURE);
  if (actionId == -1)
    return (SUCCESS);
  else if (gettimeofday(&tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  if (zd->actions[actionId].playerId != 0 &&
      (zd->actions[actionId].tv.tv_sec * 1000000) +
      zd->actions[actionId].tv.tv_usec +
      zd->actions[actionId].duration <= (tv.tv_sec * 1000000) + tv.tv_usec)
    {
      if (playerExists(zd, zd->actions[actionId].playerId))
        {
          if (g_commands[zd->actions[actionId].action].exec(zd, NULL, actionId)
              == FAILURE)
            return (FAILURE);
        }
      zd->actions[actionId].playerId = 0;
      if (zd->actions[actionId].param)
        free(zd->actions[actionId].param);
    }
  return (SUCCESS);
}
