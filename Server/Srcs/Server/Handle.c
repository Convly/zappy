/*
** Handle.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 21 19:03:10 2017 Antoine Dury
** Last update Wed Jun 28 14:21:52 2017 Antoine Dury
*/

#include "Zappy.h"

int			handleClientCommand(t_zappyData *zd,
					    const int clientFd)
{
  int			readSize;
  char			buffer[BUFFER_SIZE];
  t_circularBuffer	cb;

  zd->currentClient = clientFd;
  bzero(buffer, BUFFER_SIZE);
  readSize = read(clientFd, buffer, BUFFER_SIZE - 1);
  if (readSize > 0)
    {
      if (initCircularBuffer(&cb) == FAILURE ||
	  addCircularBuffer(&cb, buffer) == FAILURE)
        return (FAILURE);
      if (buffer[0] != '\n')
	{
	  if (processCommands(zd, cb.buffer) == FAILURE)
	    return (closeClientConnection(zd, clientFd, FAILURE));
	}
      free(cb.buffer);
    }
  else
    return (closeClientConnection(zd, clientFd, SUCCESS));
  return (SUCCESS);
}

int			handleClientConnection(t_zappyData *zd,
					       const int clientFd)
{
  int			clientSocket;
  socklen_t		clientSize;
  struct sockaddr_in	sin;

  clientSize = sizeof(sin);
  if ((clientSocket = accept(clientFd, (struct sockaddr*)&sin, &clientSize))
      < 0)
    return (printPerror("accept"));
  zd->clients[clientSocket].fdType = FD_CLIENT;
  zd->clients[clientSocket].fctEvent = handleClientCommand;
  zd->clients[clientSocket].mode = UNDEFINED;
  zd->clients[clientSocket].teamId = -1;
  zd->clients[clientSocket].connected = false;
  return (addResponse(zd, clientSocket, "WELCOME") == SUCCESS &&
	  infoLog("New client successfully connected - ID : %d", clientSocket)
	  == SUCCESS ? SUCCESS : FAILURE);
}

int	handleClientEvent(t_zappyData *zd, fd_set *fd)
{
  int	i;

  i = -1;
  while (++i < SOMAXCONN)
    {
      if (FD_ISSET(i, fd))
        {
          if (zd->clients[i].fctEvent(zd, i) == FAILURE)
            return (FAILURE);
        }
    }
  return (SUCCESS);
}
