/*
** Graphic.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/GRAPHIC
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 14:00:09 2017 Antoine Dury
** Last update Sun Jul  2 20:41:14 2017 Antoine Dury
*/

#include "Zappy.h"

static int	processGraphicCmd(t_zappyData *zd)
{
  int		i;
  int		j;
  t_pos		pos;

  i = -1;
  if (mszCmd(zd, NULL, 1) == FAILURE || sgtCmd(zd, NULL, 1) == FAILURE ||
      mctCmd(zd, NULL, 1) == FAILURE || tnaCmd(zd, NULL, 1) == FAILURE)
    return (FAILURE);
  while (++i < zd->nbTeams)
    {
      j = -1;
      while (++j < SOMAXCONN)
        {
          if (zd->teams[i].players[j] != 0)
            {
              pos = getPlayerPos(zd, zd->teams[i].players[j]);
              addResponse(zd, zd->currentClient, "pnw %d %d %d %d %d %s",
			  zd->teams[i].players[j], pos.x, pos.y,
			  getPlayerOrientation(zd, zd->teams[i].players[j]),
			  getPlayerLevel(zd, zd->teams[i].players[j]),
			  getPlayerTeam(zd, zd->teams[i].players[j]));
            }
        }
    }
  return (SUCCESS);
}

int	graphicCmd(t_zappyData *zd,
		   char **cmd,
		   const int nbParams)
{
  (void)cmd;
  (void)nbParams;
  if (!rightMode(zd, UNDEFINED))
    return (rightMode(zd, AI) ? addResponse(zd, zd->currentClient, "ko") :
	    addResponse(zd, zd->currentClient, "suc"));
  zd->clients[zd->currentClient].mode = GRAPHIC;
  return (processGraphicCmd(zd) == SUCCESS &&
	  infoLog("Client n°%d entered graphic mode", zd->currentClient)
	  == SUCCESS ? SUCCESS : FAILURE);
}
