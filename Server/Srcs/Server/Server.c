/*
** Server.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 11:40:37 2017 Antoine Dury
** Last update Sun Jul  2 21:03:43 2017 Antoine Dury
*/

#include "Zappy.h"

int	printServerUsage(t_zappyData *zd,
			 const char *prog,
			 const int retCode)
{
  if (fprintf(stderr, "USAGE: %s -p port -x width -y height -n name1 name2 \
... -c clientsNb -f freq\n						\
\tport\t\tis the port number\n						\
\twidth\t\tis the width of the world\n					\
\theight\t\tis the height of the world\n				\
\tnameX\t\tis the name of the team X\n					\
\tclientsNb\tis the number of authorized clients per team\n		\
\tfreq\t\tis the reciprocal of time unit for execution of actions\n",
	      prog) < 0)
    printPerror("fprintf");
  if (retCode || retCode == SUCCESS)
    zd->exitHelp = true;
  return (retCode);
}

static int	printServerInfos(t_zappyData *zd)
{
  return (startLog("Server listening on port %d", zd->port) == SUCCESS &&
	  startLog("Word size set to {%d, %d} and frequence set to %d",
		   zd->width, zd->height, zd->freq) == SUCCESS &&
	  startLog("%d team(s) of %d player(s) are set, let the game begin !",
		   zd->nbTeams, zd->nbClients) == SUCCESS &&
	  (DEBUG_MODE ? debugLog("Debug mode enabled, change 'DEBUG_MODE' \
macro to disable it") == SUCCESS : true) ? SUCCESS : FAILURE);
}

int		zappyServer(char **args)
{
  t_zappyData	zd;
  int		retCode;

  zd.exitHelp = false;
  zd.indexOpt = 0;
  if (initZappyData(&zd) == FAILURE)
    return (freeZappyData(&zd, FAILURE));
  else if ((retCode = processLaunchingOptions(&zd, args)) == FAILURE ||
	   zd.exitHelp)
    return (freeZappyData(&zd, retCode));
  if (zd.nbTeams == 0)
    return (printErrorLaunching(&zd, 0, args[0], "-n"));
  return ((printServerInfos(&zd) == FAILURE || initZappyMap(&zd) == FAILURE ||
	   initZappyServer(&zd) == FAILURE ||
	   processZappyServer(&zd) == FAILURE)
	  ? freeZappyData(&zd, FAILURE) : freeZappyData(&zd, SUCCESS));
}

int	main(int ac, char **av)
{
  (void)ac;
  srand(time(NULL));
  return (zappyServer(av));
}
