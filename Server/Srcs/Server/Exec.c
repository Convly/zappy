/*
** Exec.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 21 14:20:07 2017 Antoine Dury
** Last update Sun Jul  2 20:58:11 2017 Antoine Dury
*/

#include "Zappy.h"

bool	g_serverInterrupted = false;

static void	setFd(t_zappyData *zd,
		      fd_set *fdRead)
{
  int		i;

  i = -1;
  FD_ZERO(fdRead);
  while (++i < SOMAXCONN)
    {
      if (zd->clients[i].fdType != FD_FREE)
        FD_SET(i, fdRead);
    }
}

static int	displayResults(t_zappyData *zd)
{
  int i;
  int j;

  i = -1;
  if (infoLog("Results of the game") == FAILURE)
    return (FAILURE);
  while (++i < zd->nbTeams)
    {
      j = 0;
      if (printf("%s", zd->teams[i].name) < 0)
        return (printPerror("printf"));
      while (++j < 9)
        {
          if (printf(" %d", getNbLevel(zd, i, j)) < 0)
            return (printPerror("printf"));
        }
      if (printf("\n") < 0)
        return (printPerror("printf"));
    }
  return (SUCCESS);
}

static void	stopZappyServer(int sig)
{
  if (sig == SIGINT)
    {
      if (printf("\n") < 0)
        printPerror("printf");
      infoLog("Server interrupted by local host");
      g_serverInterrupted = true;
    }
}

static int	execZappyServer(t_zappyData *zd, fd_set fdRead,
				struct timeval tv)
{
  int	i;

  i = -1;
  if (select(FD_SETSIZE, &fdRead, NULL, 0,
	     (tv.tv_usec < 0 ? NULL : &tv)) < 0)
    return (errno == EINTR ? SUCCESS : printPerror("select"));
  if (handleClientEvent(zd, &fdRead) == FAILURE ||
      processAction(zd, getNextAction(zd)) == FAILURE ||
      sendResponses(zd) == FAILURE)
    return (FAILURE);
  while (++i < zd->nbTeams)
    {
      if (getNbLevel(zd, i, 8) > 0)
        {
          addGlobalResponse(zd, "seg %s", zd->teams[i].name);
          sendResponses(zd);
          g_serverInterrupted = true;
        }
    }
  return (SUCCESS);
}

int			processZappyServer(t_zappyData *zd)
{
  fd_set		fdRead;
  struct timeval	tv;
  int			nextAction;
  int			nextFeeding;

  signal(SIGINT, stopZappyServer);
  while (!g_serverInterrupted)
    {
      setFd(zd, &fdRead);
      nextAction = getNextAction(zd);
      nextFeeding = getNextFeeding(zd);
      tv.tv_sec = nextAction >= 0 ? zd->actions[nextAction].duration / 1000000
	: nextFeeding / 1000000;
      tv.tv_usec = nextAction >= 0 ? zd->actions[nextAction].duration % 1000000
	: nextFeeding % 1000000;
      if (nextFeeding == -1 ?
	  debugLog("Select syscall waiting until reading event") :
	  debugLog("Select syscall waiting for %d.%d second(s)",
		   tv.tv_sec, tv.tv_usec) == FAILURE)
	return (FAILURE);
      if (execZappyServer(zd, fdRead, tv) == FAILURE)
        return (FAILURE);
    }
  return (displayResults(zd));
}
