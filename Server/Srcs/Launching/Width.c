/*
** Width.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 15:52:12 2017 Antoine Dury
** Last update Sun Jul  2 20:53:29 2017 Antoine Dury
*/

#include "Zappy.h"

int	widthOption(t_zappyData *zd,
		    char **args,
		    const int i)
{
  if ((zd->width = atoi(args[i])) < 10 || zd->width > 30)
    {
      if (errorLog("-x option only accepts integer values between 10 and 30\n")
	  == FAILURE)
	return (FAILURE);
      return (printServerUsage(zd, args[0], FAILURE));
    }
  return (SUCCESS);
}
