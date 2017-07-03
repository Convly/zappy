/*
** Player.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Setter
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 26 17:11:20 2017 Antoine Dury
** Last update Sun Jul 02 20:26:32 2017 Antoine Dury
*/

#include "Zappy.h"

void	initPlayers(t_zappyData *zd)
{
  int	i;

  i = -1;
  while (++i < SOMAXCONN)
    {
      zd->clients[i].teamId = -1;
      zd->clients[i].level = 0;
    }
}

void	initActions(t_zappyData *zd)
{
  int	i;

  i = -1;
  while (++i < MAX_ACTIONS)
    zd->actions[i].playerId = 0;
}

void	unsetPlayerInfos(t_zappyData *zd, const int id)
{
  zd->map[zd->clients[id].pos.y][zd->clients[id].pos.x].nbPlayers--;
}
