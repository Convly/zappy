/*
** Movement1.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:55:37 2017 Antoine Dury
** Last update Sun Jul  2 20:33:26 2017 Antoine Dury
*/

#include "Zappy.h"

int			forwardCmd(t_zappyData *zd,
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
  action.action = FORWARD;
  action.param = NULL;
  return (addAction(zd, action));
}

int			leftCmd(t_zappyData *zd,
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
  action.action = LEFT;
  action.param = NULL;
  return (addAction(zd, action));
}

int			rightCmd(t_zappyData *zd,
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
  action.action = RIGHT;
  action.param = NULL;
  return (addAction(zd, action));
}
