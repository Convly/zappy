/*
** Map.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/GRAPHIC
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 26 11:23:35 2017 Antoine Dury
** Last update Sun Jul  2 20:45:00 2017 Antoine Dury
*/

#include "Zappy.h"

int	processBctCmd(t_zappyData *zd,
		      const t_pos pos,
		      const int id,
		      const bool global)
{
  return (global ? addGlobalResponse(zd, "bct %d %d %d %d %d %d %d %d %d",
				     pos.x, pos.y,
				     zd->map[pos.y][pos.x].nbFoods,
				     zd->map[pos.y][pos.x].resources[LINEMATE],
				     zd->map[pos.y][pos.x].resources[DERAUMERE],
				     zd->map[pos.y][pos.x].resources[SIBUR],
				     zd->map[pos.y][pos.x].resources[MENDIANE],
				     zd->map[pos.y][pos.x].resources[PHIRAS],
				     zd->map[pos.y][pos.x].resources[THYSTAME])
	  :addResponse(zd, id, "bct %d %d %d %d %d %d %d %d %d",
		       pos.x, pos.y, zd->map[pos.y][pos.x].nbFoods,
		       zd->map[pos.y][pos.x].resources[LINEMATE],
		       zd->map[pos.y][pos.x].resources[DERAUMERE],
		       zd->map[pos.y][pos.x].resources[SIBUR],
		       zd->map[pos.y][pos.x].resources[MENDIANE],
		       zd->map[pos.y][pos.x].resources[PHIRAS],
		       zd->map[pos.y][pos.x].resources[THYSTAME]));
}

static char	*getBctResponse(t_zappyData *zd,
				const t_pos pos,
				char *response)
{
  char	tmp[64];

  if (sprintf(tmp, "bct %d %d %d %d %d %d %d %d %d\n",
	      pos.x, pos.y, zd->map[pos.y][pos.x].nbFoods,
	      zd->map[pos.y][pos.x].resources[LINEMATE],
	      zd->map[pos.y][pos.x].resources[DERAUMERE],
	      zd->map[pos.y][pos.x].resources[SIBUR],
	      zd->map[pos.y][pos.x].resources[MENDIANE],
	      zd->map[pos.y][pos.x].resources[PHIRAS],
	      zd->map[pos.y][pos.x].resources[THYSTAME]) < 0)
    {
      printPerror("sprintf");
      return (NULL);
    }
  return (reallocat(response, tmp));
}

int	processGlobalMctCmd(t_zappyData *zd)
{
  int	y;
  t_pos pos;
  char	*response;

  y = -1;
  if ((response = malloc(sizeof(char) * 1)) == NULL)
    return (printPerror("malloc"));
  bzero(response, 1);
  while (++y < zd->height)
    {
      pos.x = -1;
      pos.y = y;
      while (++pos.x < zd->width)
	{
	  if ((response = getBctResponse(zd, pos, response)) == NULL)
	    return (FAILURE);
	}
    }
  response[strlen(response) - 1] = '\0';
  if (addGlobalResponse(zd, response) == FAILURE)
    return (FAILURE);
  free(response);
  return (SUCCESS);
}

int	bctCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  t_pos	pos;

  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 3 || (pos.x = atoi(cmd[1])) < 0
	   || pos.x >= zd->width ||
	   (pos.y = atoi(cmd[2])) < 0 || pos.y >= zd->height)
    return (addResponse(zd, zd->currentClient, "sbp"));
  return (processBctCmd(zd, pos, zd->currentClient, false));
}

int	mctCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  int	y;
  t_pos pos;
  char	*response;

  (void)cmd;
  y = -1;
  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  if ((response = malloc(sizeof(char) * 1)) == NULL || !memset(response, 0, 1))
    return (printPerror("malloc"));
  while (++y < zd->height)
    {
      pos.x = -1;
      pos.y = y;
      while (++pos.x < zd->width)
	if ((response = getBctResponse(zd, pos, response)) == NULL)
	  return (FAILURE);
    }
  response[strlen(response) - 1] = '\0';
  if (addResponse(zd, zd->currentClient, response) == FAILURE)
    return (FAILURE);
  free(response);
  return (SUCCESS);
}
