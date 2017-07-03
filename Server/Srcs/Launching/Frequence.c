/*
** Frequence.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 16:43:59 2017 Antoine Dury
** Last update Sun Jul  2 20:50:46 2017 Antoine Dury
*/

#include "Zappy.h"

int	frequenceOption(t_zappyData *zd,
			char **args,
			const int i)
{
  if ((zd->freq = atoi(args[i])) < 2 || zd->freq > 10000)
    {
      if (errorLog("-f option only accepts integer values between 2 and \
10000\n") == FAILURE)
	return (FAILURE);
      return (printServerUsage(zd, args[0], FAILURE));
    }
  return (SUCCESS);
}
