/*
** Take.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 29 19:30:34 2017 Antoine Dury
** Last update Sun Jul  2 20:37:02 2017 Antoine Dury
*/

#include "Zappy.h"

int	processPinCmd(t_zappyData *zd,
		      const int playerId)
{
  t_pos	pos;

  pos = getPlayerPos(zd, playerId);
  return (addGlobalResponse(zd, "pin %d %d %d %d %d %d %d %d %d %d",
			    playerId, pos.x, pos.y,
			    zd->clients[playerId].nbFoods,
			    zd->clients[playerId].resources[LINEMATE],
			    zd->clients[playerId].resources[DERAUMERE],
			    zd->clients[playerId].resources[SIBUR],
			    zd->clients[playerId].resources[MENDIANE],
			    zd->clients[playerId].resources[PHIRAS],
			    zd->clients[playerId].resources[THYSTAME]));
}

static int	processTakeMineral(t_zappyData *zd,
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
          if (!mineralExists(zd, playerPos.x, playerPos.y, i))
            return (addResponse(zd, playerId, "ko"));
          zd->clients[playerId].resources[i]++;
          zd->map[playerPos.y][playerPos.x].resources[i]--;
          zd->map[rand() % zd->height][rand() % zd->width].resources[i]++;
          validMineral = true;
          break;
        }
    }
  if (!validMineral)
    return (addResponse(zd, playerId, "ko"));
  return (processPinCmd(zd, playerId) == SUCCESS &&
	  processBctCmd(zd, playerPos, playerId, true) == SUCCESS &&
	  addGlobalResponse(zd, "pgt %d %d", playerId, i) == SUCCESS &&
	  addResponse(zd, playerId, "ok") == SUCCESS ? SUCCESS : FAILURE);
}

static int  processTakeFood(t_zappyData *zd,
			    const int playerId,
			    const t_pos playerPos)
{
  if (!foodExists(zd, playerPos.x, playerPos.y))
    return (addResponse(zd, playerId, "ko"));
  zd->clients[playerId].nbFoods++;
  zd->map[playerPos.y][playerPos.x].nbFoods--;
  zd->map[rand() % zd->height][rand() % zd->width].nbFoods++;
  return (processPinCmd(zd, playerId) == SUCCESS &&
	  processBctCmd(zd, playerPos, playerId, true) == SUCCESS &&
	  addGlobalResponse(zd, "pgt %d 0", playerId) == SUCCESS &&
	  addResponse(zd, playerId, "ok") == SUCCESS ? SUCCESS : FAILURE);
}

int	processTake(t_zappyData *zd,
		    char **cmd,
		    const int actionId)
{
  int	playerId;
  t_pos	playerPos;

  (void)cmd;
  playerId = zd->actions[actionId].playerId;
  playerPos = zd->clients[playerId].pos;
  if (strcmp(zd->actions[actionId].param, "food") == 0)
    return (processTakeFood(zd, playerId, playerPos));
  else
    return (processTakeMineral(zd, actionId, playerId, playerPos));
  return (SUCCESS);
}

int			takeCmd(t_zappyData *zd,
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
  action.action = TAKE;
  if ((action.param = strdup(cmd[1])) == NULL)
    return (printPerror("strdup"));
  return (addAction(zd, action));
}
