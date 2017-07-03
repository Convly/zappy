/*
** Look2.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/AI
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 29 16:54:39 2017 Antoine Dury
** Last update Sun Jul  2 20:32:32 2017 Antoine Dury
*/

#include "Zappy.h"

void	processNorthLook(t_zappyData *zd,
			 t_pos pos,
			 const int vision,
			 const int nbUnits)
{
  int	i;

  i = -1;
  while (++i < nbUnits)
    {
      lookSquare(zd->map[circularLook(pos.y, zd->width)]
		 [circularLook(pos.x - vision, zd->height)]);
      pos.x++;
    }
}

void	processSouthLook(t_zappyData *zd,
			 t_pos pos,
			 const int vision,
			 const int nbUnits)
{
  int	i;

  i = -1;
  while (++i < nbUnits)
    {
      lookSquare(zd->map[circularLook(pos.y, zd->width)]
		 [circularLook(pos.x + vision, zd->height)]);
      pos.x--;
    }
}

void	processWestLook(t_zappyData *zd,
			t_pos pos,
			const int vision,
			const int nbUnits)
{
  int	i;

  i = -1;
  while (++i < nbUnits)
    {
      lookSquare(zd->map[circularLook(pos.y - vision, zd->width)]
		 [circularLook(pos.x, zd->height)]);
      pos.y++;
    }
}

void	processEastLook(t_zappyData *zd,
			t_pos pos,
			const int vision,
			const int nbUnits)
{
  int	i;

  i = -1;
  while (++i < nbUnits)
    {
      lookSquare(zd->map[circularLook(pos.y + vision, zd->width)]
		 [circularLook(pos.x, zd->height)]);
      pos.y--;
    }
}
