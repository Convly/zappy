/*
** Resources.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Setter
**
** Made by Yamine Mansouri
** Login   <yamine.mansouri@epitech.eu>
**
** Started on  Mon Jun 26 12:14:37 2017 Yamine Mansouri
** Last update Sun Jul  2 21:08:48 2017 Antoine Dury
*/

#include "Zappy.h"

int	setResources(t_zappyData *zd,
		     const Resources resource,
		     int nbResources)
{
  t_pos pos;
  int	nbFoods;

  nbFoods = rand() % 5;
  while (nbResources >= 0)
    {
      pos.y = rand() % zd->height;
      pos.x = rand() % zd->width;
      zd->map[pos.y][pos.x].resources[resource]++;
      if (nbResources % 8 == 0)
        {
          if (zd->map[pos.y][pos.x].nbFoods != 0)
            {
              pos.y = rand() % zd->height;
              pos.x = rand() % zd->width;
            }
          zd->map[pos.y][pos.x].nbFoods = nbFoods;
        }
      nbResources -= 1;
    }
  return (nbResources);
}
