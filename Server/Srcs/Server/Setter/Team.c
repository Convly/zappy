/*
** Team.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Setter
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 16:39:29 2017 Antoine Dury
** Last update Sun Jul  2 21:09:26 2017 Antoine Dury
*/

#include "Zappy.h"

void	setMaxPlayers(t_zappyData *zd,
		      const int maxClients)
{
  int	i;
  int	j;

  i = -1;
  while (++i < zd->nbTeams)
    {
      j = -1;
      zd->teams[i].maxPlayers = maxClients;
      while (++j < SOMAXCONN)
        zd->teams[i].players[j] = 0;
    }
}

void	initTeams(t_zappyData *zd)
{
  int	i;
  int	j;

  setMaxPlayers(zd, zd->nbClients);
  i = -1;
  while (++i < zd->nbTeams)
    {
      j = -1;
      zd->teams[i].nbEggs = 0;
      while (++j < MAX_ACTIONS)
        zd->teams[i].eggs[j].playerId = 0;
    }
}

void	unsetPlayerTeam(t_zappyData *zd,
			const int id)
{
  if (zd->clients[id].teamId == -1)
    return;
  zd->teams[zd->clients[id].teamId].players[id] = 0;
  zd->teams[zd->clients[id].teamId].nbPlayers--;
}
