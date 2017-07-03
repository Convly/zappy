/*
** Team.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Getter
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 16:01:32 2017 Antoine Dury
** Last update Sun Jul  2 21:08:00 2017 Antoine Dury
*/

#include "Zappy.h"

int	getTeamId(t_zappyData *zd, const char *name)
{
  int	i;

  i = -1;
  while (++i < zd->nbTeams)
    {
      if (strcmp(zd->teams[i].name, name) == 0)
        return (i);
    }
  return (-1);
}

int	getNbLevel(const t_zappyData *zd,
		   const int teamId,
		   const int level)
{
  int	i;
  int	nb;

  i = -1;
  nb = 0;
  while (++i < SOMAXCONN)
    {
      if (zd->clients[i].teamId == teamId && zd->clients[i].level == level)
        nb++;
    }
  return (nb);
}
