/*
** Commands2.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands/GRAPHIC
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 14:01:43 2017 Antoine Dury
** Last update Sun Jul  2 20:40:36 2017 Antoine Dury
*/

#include "Zappy.h"

int	sstCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  int	freq;

  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 2 || !cmd[1] || (freq = atoi(cmd[1])) < 2 ||
	   freq > 10000)
    return (addResponse(zd, zd->currentClient, "sbp"));
  zd->freq = freq;
  return (sgtCmd(zd, NULL, 1));
}

int	tnaCmd(t_zappyData *zd,
	       char **cmd,
	       const int nbParams)
{
  int	i;

  (void)cmd;
  i = -1;
  if (!rightMode(zd, GRAPHIC))
    return (addResponse(zd, zd->currentClient, "ko"));
  else if (nbParams != 1)
    return (addResponse(zd, zd->currentClient, "sbp"));
  while (++i < zd->nbTeams)
    {
      if (addResponse(zd, zd->currentClient, "tna %s", zd->teams[i].name)
	  == FAILURE)
        return (FAILURE);
    }
  return (SUCCESS);
}
