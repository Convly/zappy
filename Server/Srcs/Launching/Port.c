/*
** Port.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 12:21:27 2017 Antoine Dury
** Last update Sun Jul  2 20:53:09 2017 Antoine Dury
*/

#include "Zappy.h"

int	portOption(t_zappyData *zd,
		   char **args,
		   const int i)
{
  if ((zd->port = atoi(args[i])) <= 0)
    {
      if (errorLog("-p option only accepts valid ports\n") == FAILURE)
	return (FAILURE);
      return (printServerUsage(zd, args[0], FAILURE));
    }
  return (SUCCESS);
}
