/*
** Map.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Check
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 29 18:18:25 2017 Antoine Dury
** Last update Sun Jul  2 21:04:52 2017 Antoine Dury
*/

#include "Zappy.h"

bool	foodExists(const t_zappyData *zd,
		   const int x,
		   const int y)
{
  return (zd->map[y][x].nbFoods > 0);
}

bool	mineralExists(const t_zappyData *zd,
		      const int x,
		      const int y,
		      const Resources resource)
{
  return (zd->map[y][x].resources[resource] > 0);
}

bool	checkPlayers(t_zappyData *zd,
		     const int playerId,
		     const int nbPlayers)
{
  t_pos	playerPos;

  playerPos = getPlayerPos(zd, playerId);
  return (checkLevel(zd, playerPos, zd->clients[playerId].level) &&
	  zd->map[playerPos.y][playerPos.x].nbPlayers == nbPlayers);
}

bool	checkMinerals(t_zappyData *zd,
		      const int playerId,
		      const t_incantation incantation)
{
  int	i;
  t_pos	playerPos;

  i = -1;
  playerPos = getPlayerPos(zd, playerId);
  while (++i < NB_RESOURCES)
    {
      if (zd->map[playerPos.y][playerPos.x].resources[i] !=
	  incantation.resources[i])
        return (false);
    }
  return (true);
}

bool	checkLevel(t_zappyData *zd,
		   const t_pos pos,
		   const int level)
{
  int	i;

  i = -1;
  while (++i < SOMAXCONN)
    {
      if (zd->clients[i].fdType == FD_CLIENT && zd->clients[i].connected &&
	  zd->clients[i].pos.x == pos.x && zd->clients[i].pos.y == pos.y)
        {
          if (zd->clients[i].level != level)
            return (false);
        }
    }
  return (true);
}
