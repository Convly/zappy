/*
** Player.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Check
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 26 14:48:58 2017 Antoine Dury
** Last update Sun Jul  2 21:06:28 2017 Antoine Dury
*/

#include "Zappy.h"

bool	playerExists(t_zappyData *zd, const int id)
{
  if (id < 0 || id > SOMAXCONN)
    return (false);
  if (zd->clients[id].fdType == FD_CLIENT && zd->clients[id].connected)
    return (true);
  return (false);
}

bool	playerHasFood(t_zappyData *zd,
		      const int playerId)
{
  return (zd->clients[playerId].nbFoods > 0);
}

bool	playerHasMineral(t_zappyData *zd,
			 const int playerId,
			 const Resources resource)
{
  return (zd->clients[playerId].resources[resource] > 0);
}

bool	playerSamePos(const t_pos pos1, const t_pos pos2)
{
  return (pos1.x == pos2.x && pos1.y == pos2.y);
}
