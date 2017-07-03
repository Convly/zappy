/*
** Set.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 13:56:06 2017 Antoine Dury
** Last update Sun Jul  2 20:35:32 2017 Antoine Dury
*/

#include "Zappy.h"

static int	processSetMineral(t_zappyData *zd,
				  const int actionId,
				  const int playerId,
				  const t_pos playerPos)
{
  int		i;
  bool		validMineral;

  i = -1;
  validMineral = false;
  while (++i < NB_RESOURCES)
    {
      if (strcmp(zd->actions[actionId].param, g_minerals[i]) == 0)
        {
          if (!playerHasMineral(zd, playerId, i))
            return (addResponse(zd, playerId, "ko"));
          zd->clients[playerId].resources[i]--;
          zd->map[playerPos.y][playerPos.x].resources[i]++;
          validMineral = true;
          break;
        }
    }
  if (!validMineral)
    return (addResponse(zd, playerId, "ko"));
  return (processPinCmd(zd, playerId) == SUCCESS &&
	  processBctCmd(zd, playerPos, playerId, true) == SUCCESS &&
	  addGlobalResponse(zd, "pdr %d %d", playerId, i) == SUCCESS &&
	  addResponse(zd, playerId, "ok") == SUCCESS ? SUCCESS : FAILURE);
}

static int	processSetFood(t_zappyData *zd,
			       const int playerId,
			       const t_pos playerPos)
{
  if (!playerHasFood(zd, playerId))
    return (addResponse(zd, playerId, "ko"));
  zd->clients[playerId].nbFoods--;
  zd->map[playerPos.y][playerPos.x].nbFoods++;
  return (processPinCmd(zd, playerId) == SUCCESS &&
	  processBctCmd(zd, playerPos, playerId, true) == SUCCESS &&
	  addGlobalResponse(zd, "pdr %d 0", playerId) == SUCCESS &&
	  addResponse(zd, playerId, "ok") == SUCCESS ? SUCCESS : FAILURE);
}

int	processSet(t_zappyData *zd,
		   char **cmd,
		   const int actionId)
{
  int	playerId;
  t_pos	playerPos;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  playerPos = zd->clients[playerId].pos;
  if (strcmp(zd->actions[actionId].param, "food") == 0)
    return (processSetFood(zd, playerId, playerPos));
  else
    return (processSetMineral(zd, actionId, playerId, playerPos));
  return (SUCCESS);
}

int			setCmd(t_zappyData *zd,
			       char **cmd,
			       const int nbParams)
{
  t_clientAction	action;

  if (!rightMode(zd, AI))
    return (rightMode(zd, UNDEFINED) ?
	    addResponse(zd, zd->currentClient, "ko") :
	    addResponse(zd, zd->currentClient, "suc"));
  else if (nbParams != 2 || !cmd[1])
    return (addResponse(zd, zd->currentClient, "ko"));
  action.playerId = zd->currentClient;
  if (gettimeofday(&action.tv, NULL) < 0)
    return (printPerror("gettimeofday"));
  action.duration = (7.0 / zd->freq) * 1000000;
  action.action = SET;
  if ((action.param = strdup(cmd[1])) == NULL)
    return (printPerror("strdup"));
  return (addAction(zd, action));
}
