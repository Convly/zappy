/*
** Calculations.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Utils
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Fri Jun 30 16:06:44 2017 Antoine Dury
** Last update Sun Jul  2 20:46:43 2017 Antoine Dury
*/

#include "Zappy.h"

static t_vecDir	g_vd[] =
  {
    {1, 0, 1},
    {2, -1, 1},
    {3, -1, 0},
    {4, -1, -1},
    {5, 0, -1},
    {6, 1, -1},
    {7, 1, 0},
    {8, 1, 1}
  };

int	circularLook(const int a, const int b)
{
  return (a % b < 0 ? (a % b) + b : a % b);
}

int	getClosestPath(const int a,
		       const int b,
		       const int size)
{
  return (a == b ? b : a < b ? (abs(b - a) <= size ? b - 1 : b + 1) :
	  (abs(b - a) <= size ? b + 1 : b - 1));
}

int	getRelativePos(int pos, const int size)
{
  while (pos < 0)
    pos += size;
  return (pos % size);
}

static int  getDirection(const int val,
			 const int deg)
{
  return (val - deg > 0 ? val - deg : 8 + (val - deg));
}

int		getSoundDirection(const t_zappyData *zd,
				  const t_clientData receiver,
				  const int x, const int y)
{
  int		i;
  int		deg;

  i = -1;
  if (receiver.orientation == NORTH)
    deg = 0;
  else if (receiver.orientation == WEST)
    deg = 2;
  else if (receiver.orientation == SOUTH)
    deg = 4;
  else if (receiver.orientation == EAST)
    deg = 6;
  while (++i < 8)
    {
      if (x == getRelativePos(receiver.pos.x + g_vd[i].x, zd->width) &&
          y == getRelativePos(receiver.pos.y + g_vd[i].y, zd->height))
	return (getDirection(g_vd[i].val, deg));
    }
  return (-1);
}
