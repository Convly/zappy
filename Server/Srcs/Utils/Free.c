/*
** Free.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Utils
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 18:30:32 2017 Antoine Dury
** Last update Wed Jun 21 16:50:09 2017 Antoine Dury
*/

#include "Zappy.h"

static void   freeMap(const t_zappyData *zd)
{
  int y;

  if (!zd->map)
    return;
  y = -1;
  while (++y < zd->height)
    free(zd->map[y]);
  free(zd->map);
}

void	freeTeams(const t_zappyData *zd)
{
  int	i;

  i = -1;
  while (++i < zd->nbTeams)
    free(zd->teams[i].name);
  free(zd->teams);
}

int freeZappyData(const t_zappyData *zd, const int retCode)
{
  freeTeams(zd);
  freeMap(zd);
  if (zd->serverSocket != 0)
    {
      if (close(zd->serverSocket) < 0)
        return (printPerror("close"));
    }
  return (retCode);
}
