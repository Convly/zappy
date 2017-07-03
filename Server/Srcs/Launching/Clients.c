/*
** Clients.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 16:39:43 2017 Antoine Dury
** Last update Sun Jul  2 20:50:31 2017 Antoine Dury
*/

#include "Zappy.h"

int	clientsOption(t_zappyData *zd,
		      char **args,
		      const int i)
{
  if ((zd->nbClients = atoi(args[i])) <= 0)
    {
      if (errorLog("-c option only accepts integer values greater or equal \
to 1\n") == FAILURE)
	return (FAILURE);
      return (printServerUsage(zd, args[0], FAILURE));
    }
  setMaxPlayers(zd, zd->nbClients);
  return (SUCCESS);
}
