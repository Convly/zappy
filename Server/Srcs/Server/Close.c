/*
** Close.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 21 19:34:24 2017 Antoine Dury
** Last update Sun Jul  2 20:57:00 2017 Antoine Dury
*/

#include "Zappy.h"

int	closeClientConnection(t_zappyData *zd,
			      const int fd,
			      const int retCode)
{
  int	i;

  i = -1;
  while (++i < MAX_ACTIONS)
    {
      if (zd->actions[i].playerId == fd)
        zd->actions[i].playerId = 0;
    }
  unsetPlayerTeam(zd, fd);
  if (playerExists(zd, fd))
    {
      unsetPlayerInfos(zd, fd);
      addGlobalResponse(zd, "pdi %d", fd);
    }
  zd->clients[fd].fdType = FD_FREE;
  if (close(fd) < 0)
    return (printPerror("close"));
  if (infoLog("Connection to client closed by remote host - ID : %d", fd)
      == FAILURE)
    return (FAILURE);
  return (retCode);
}

int	shutdownClientConnection(t_zappyData *zd,
				 const int fd)
{
  if (shutdown(fd, SHUT_RDWR) < 0)
    return (printPerror("shutdown"));
  zd->clients[fd].dead = true;
  return (SUCCESS);
}
