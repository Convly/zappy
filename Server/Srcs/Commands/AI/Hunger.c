/*
** Eat.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 28 10:37:46 2017 Antoine Dury
** Last update Sun Jul  2 20:28:28 2017 Antoine Dury
*/

#include "Zappy.h"

int			processEat(t_zappyData *zd, char **cmd,
				   const int actionId)
{
  int			playerId;
  t_clientAction	action;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  zd->clients[playerId].nbFoods--;
  action.playerId = playerId;
  action.param = NULL;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  if (zd->clients[playerId].nbFoods == 0)
    {
      action.duration = 0;
      action.action = DIE;
    }
  else
    {
      action.duration = (126.0 / zd->freq) * 1000000;
      action.action = EAT;
    }
  return (addAction(zd, action) == SUCCESS ?
	  debugLog("Player n°%d eats, %d unit(s) of food left",
		   playerId, zd->clients[playerId].nbFoods) : FAILURE);
}

int	processDie(t_zappyData *zd, char **cmd, const int actionId)
{
  int	playerId;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  if (addResponse(zd, playerId, "dead") == FAILURE)
    return (FAILURE);
  return (infoLog("Player n°%d dies of starving :'(", playerId));
}
