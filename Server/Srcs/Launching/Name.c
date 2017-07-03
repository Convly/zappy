/*
** Name.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 20 17:03:46 2017 Antoine Dury
** Last update Sun Jul  2 20:52:47 2017 Antoine Dury
*/

#include "Zappy.h"

static int	initNewTeam(t_zappyData *zd,
			    char **args,
			    const int i,
			    const int j)
{
  if (strcmp(args[j], "GRAPHIC") == 0 || strlen(args[j]) > 512)
    {
      errorLog("-n option only accepts valid team names\n");
      return (printServerUsage(zd, args[0], FAILURE));
    }
  if ((zd->teams[i].name = strdup(args[j])) == NULL)
    return (printPerror("strdup"));
  zd->nbTeams++;
  zd->teams[i].maxPlayers = zd->nbClients;
  zd->teams[i].nbPlayers = 0;
  bzero(zd->teams[i].players, SOMAXCONN);
  return (SUCCESS);
}

int	nameOption(t_zappyData *zd,
		   char **args,
		   const int i)
{
  int	j;
  int	k;

  j = i - 1;
  k = 0;
  freeTeams(zd);
  while (args[++j] && args[j][0] != '-');
  zd->indexOpt += j - i - 1;
  if ((zd->teams = malloc(sizeof(t_teamData) * (j - i))) == NULL)
    return (printPerror("malloc"));
  j = i - 1;
  zd->nbTeams = 0;
  while (args[++j] && args[j][0] != '-')
    {
      if (teamExists(zd, args[j], k))
        {
          errorLog("-n option only accepts unique team names\n");
          return (printServerUsage(zd, args[0], FAILURE));
        }
      if (initNewTeam(zd, args, k, j) == FAILURE)
        return (FAILURE);
      k++;
    }
  return (SUCCESS);
}
