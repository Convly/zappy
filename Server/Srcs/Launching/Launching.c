/*
** Launching.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Launching
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 21 16:06:06 2017 Antoine Dury
** Last update Sun Jul  2 20:52:04 2017 Antoine Dury
*/

#include "Zappy.h"

static t_launching	g_launching[] =
  {
    {"-p", portOption},
    {"--port", portOption},
    {"-x", widthOption},
    {"--width", widthOption},
    {"-y", heightOption},
    {"--height", heightOption},
    {"-n", nameOption},
    {"--name", nameOption},
    {"-c", clientsOption},
    {"--clientsNb", clientsOption},
    {"-f", frequenceOption},
    {"--frequence", frequenceOption},
    {NULL, NULL}
  };

int	processLaunchingOptions(t_zappyData *zd,
				char **args)
{
  int	j;

  while (args[++zd->indexOpt])
    {
      j = -1;
      while (g_launching[++j].opt)
	{
	  if (strcmp(args[zd->indexOpt], "-h") == 0 ||
	      strcmp(args[zd->indexOpt], "--help") == 0)
	    return (printServerUsage(zd, args[0], SUCCESS));
	  if (strcmp(args[zd->indexOpt], g_launching[j].opt) == 0)
	    {
	      if (!args[zd->indexOpt + 1])
		return (printErrorLaunching(zd, 0, args[0],
					    args[zd->indexOpt]));
	      if (g_launching[j].exec(zd, args, ++zd->indexOpt) == FAILURE)
		return (FAILURE);
	      break;
	    }
	}
      if (!g_launching[j].opt)
	return (printErrorLaunching(zd, 1, args[0], args[zd->indexOpt]));
    }
  return (SUCCESS);
}
