/*
** Team.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Check
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 14:28:52 2017 Antoine Dury
** Last update Sun Jul  2 21:06:52 2017 Antoine Dury
*/

#include "Zappy.h"

bool	teamExists(t_zappyData *zd,
		   const char *name,
		   const int nbTeams)
{
  int	i;

  i = -1;
  while (++i < nbTeams)
    {
      if (strcmp(zd->teams[i].name, name) == 0)
        return (true);
    }
  return (false);
}
