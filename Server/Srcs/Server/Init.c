/*
** Init.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 19:04:43 2017 Antoine Dury
** Last update Sun Jul  2 21:00:24 2017 Antoine Dury
*/

#include "Zappy.h"

static int	generateResourcesMap(t_zappyData *zd)
{
  int		i;
  int		total;
  int		resources[NB_RESOURCES];

  i = -1;
  total = 1;
  resources[LINEMATE] = 7 * zd->nbTeams * zd->nbClients * 2;
  resources[DERAUMERE] = 6 * zd->nbTeams * zd->nbClients * 2;
  resources[SIBUR] = 8 * zd->nbTeams * zd->nbClients * 2;
  resources[MENDIANE] = 3 * zd->nbTeams * zd->nbClients * 2;
  resources[PHIRAS] = 4 * zd->nbTeams * zd->nbClients * 2;
  resources[THYSTAME] = 1 * zd->nbTeams * zd->nbClients * 2;
  while (total > 0)
    {
      i = -1;
      total = 0;
      while (++i < NB_RESOURCES)
        {
          total += resources[i];
          resources[i] = setResources(zd, i, resources[i]);
        }
    }
  return (SUCCESS);
}

int	initZappyMap(t_zappyData *zd)
{
  int	i;
  t_pos pos;

  pos.y = -1;
  if ((zd->map = malloc(sizeof(t_zappyMap*) * zd->height)) == NULL)
    return (printPerror("malloc"));
  while (++pos.y < zd->height)
    {
      if ((zd->map[pos.y] = malloc(sizeof(t_zappyMap) * zd->width)) == NULL)
        return (printPerror("malloc"));
    }
  pos.y = -1;
  while (++pos.y < zd->height)
    {
      pos.x = -1;
      while (++pos.x < zd->width)
        {
          i = -1;
          while (++i < NB_RESOURCES)
            zd->map[pos.y][pos.x].resources[i] = 0;
          zd->map[pos.y][pos.x].nbFoods = 0;
          zd->map[pos.y][pos.x].nbPlayers = 0;
        }
    }
  return (generateResourcesMap(zd));
}

int	initZappyData(t_zappyData *zd)
{
  zd->port = 8484;
  zd->width = 10;
  zd->height = 10;
  zd->freq = 100;
  zd->nbClients = 3;
  zd->nbTeams = 4;
  zd->nbEggs = 0;
  zd->map = NULL;
  zd->serverSocket = 0;
  if ((zd->teams = malloc(sizeof(t_teamData) * zd->nbTeams)) == NULL)
    return (printPerror("malloc"));
  if ((zd->teams[0].name = strdup("Team1")) == NULL ||
      (zd->teams[1].name = strdup("Team2")) == NULL ||
      (zd->teams[2].name = strdup("Team3")) == NULL ||
      (zd->teams[3].name = strdup("Team4")) == NULL)
    return (printPerror("strdup"));
  zd->teams[0].nbPlayers = 0;
  zd->teams[1].nbPlayers = 0;
  zd->teams[2].nbPlayers = 0;
  zd->teams[3].nbPlayers = 0;
  initPlayers(zd);
  initTeams(zd);
  initActions(zd);
  initResponses(zd);
  return (SUCCESS);
}

int			initZappyServer(t_zappyData *zd)
{
  int			i;
  struct sockaddr_in	sin;

  i = -1;
  if ((zd->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return (printPerror("socket"));
  if (setsockopt(zd->serverSocket, SOL_SOCKET, SO_REUSEPORT, &(int){1},
		 sizeof(int)) < 0)
    return (printPerror("setsockopt"));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(zd->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(zd->serverSocket, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    return (printPerror("bind"));
  if (listen(zd->serverSocket, SOMAXCONN) < 0)
    return (printPerror("listen"));
  while (++i < SOMAXCONN)
    zd->clients[i].fdType = FD_FREE;
  zd->clients[zd->serverSocket].fdType = FD_SERVER;
  zd->clients[zd->serverSocket].fctEvent = handleClientConnection;
  return (SUCCESS);
}
