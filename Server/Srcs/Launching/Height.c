/*
** Height.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 16:35:35 2017 Antoine Dury
** Last update Sun Jul  2 20:51:02 2017 Antoine Dury
*/

#include "Zappy.h"

int	heightOption(t_zappyData *zd,
		     char **args,
		     const int i)
{
  if ((zd->height = atoi(args[i])) < 10 || zd->height > 30)
    {
      if (errorLog("-y option only accepts integer \
values between 10 and 30\n")
	  == FAILURE)
	return (FAILURE);
      return (printServerUsage(zd, args[0], FAILURE));
    }
  return (SUCCESS);
}
