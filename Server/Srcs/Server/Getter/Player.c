/*
** Player.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Getter
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 26 14:15:22 2017 Antoine Dury
** Last update Mon Jun 26 14:25:33 2017 Antoine Dury
*/

#include "Zappy.h"

t_pos	getPlayerPos(t_zappyData *zd, const int id)
{
  return (zd->clients[id].pos);
}

int	getPlayerOrientation(t_zappyData *zd, const int id)
{
  return (zd->clients[id].orientation);
}

int	getPlayerLevel(t_zappyData *zd, const int id)
{
  return (zd->clients[id].level);
}

char	*getPlayerTeam(t_zappyData *zd, const int id)
{
  return (zd->teams[zd->clients[id].teamId].name);
}
