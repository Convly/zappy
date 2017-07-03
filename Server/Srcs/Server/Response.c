/*
** Response.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 11:50:38 2017 Antoine Dury
** Last update Sun Jul  2 21:02:31 2017 Antoine Dury
*/

#include "Zappy.h"

int		addResponse(t_zappyData *zd, const int fd,
			    const char *fmt, ...)
{
  int		i;
  char		msg[strlen(fmt)];
  va_list	ap;

  i = -1;
  if (strcpy(msg, fmt) == NULL)
    return (printPerror("strcpy"));
  va_start(ap, fmt);
  while (++i < MAX_RESPONSES)
    {
      if (zd->responses[i].fd == 0)
        {
          if (vasprintf(&zd->responses[i].msg, strcat(msg, "\n"), ap) < 0)
            return (printPerror("vasprintf"));
          zd->responses[i].fd = fd;
          break;
        }
    }
  va_end(ap);
  return (SUCCESS);
}

int  addIncantationResponse(t_zappyData *zd, const int id)
{
  if (addGlobalResponse(zd, "plv %d %d", id, zd->clients[id].level)
      == FAILURE ||
      infoLog("Player n°%d elevated to level %d", id, zd->clients[id].level)
      == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

static bool	unableToSendResponse(t_zappyData *zd,
				     const int i)
{
  return (zd->responses[i].fd == 0 ||
	  (zd->clients[zd->responses[i].fd].connected &&
	   zd->clients[zd->responses[i].fd].dead));
}

int	sendResponses(t_zappyData *zd)
{
  int	i;
  int	len;
  int	writeSize;

  i = -1;
  writeSize = 0;
  while (++i < MAX_RESPONSES)
    {
      if (unableToSendResponse(zd, i) || !(len = strlen(zd->responses[i].msg)))
        continue;
      while ((writeSize += write(zd->responses[i].fd, zd->responses[i].msg,
				 len)) < len);
      zd->responses[i].msg[len - 1] = '\0';
      if (debugLog("Send response to client n°%d - [%s]",
		   zd->responses[i].fd, zd->responses[i].msg) == FAILURE)
        return (FAILURE);
      if (strcmp(zd->responses[i].msg, "dead") == 0)
        {
          if (shutdownClientConnection(zd, zd->responses[i].fd) == FAILURE)
	    return (FAILURE);
        }
      zd->responses[i].fd = 0;
      free(zd->responses[i].msg);
    }
  return (SUCCESS);
}

int		addGlobalResponse(t_zappyData *zd,
				  const char *fmt, ...)
{
  int		i;
  int		j;
  char		msg[strlen(fmt)];
  va_list	ap;

  i = -1;
  if (strcpy(msg, fmt) == NULL || strcat(msg, "\n") == NULL)
    return (printPerror("strcpy / strcat"));
  while (++i < SOMAXCONN)
    {
      if (zd->clients[i].fdType != FD_CLIENT || zd->clients[i].mode != GRAPHIC)
        continue;
      j = -1;
      while (++j < MAX_RESPONSES)
        if (zd->responses[j].fd == 0)
          {
            va_start(ap, fmt);
            if (vasprintf(&zd->responses[j].msg, msg, ap) < 0)
              return (printPerror("vasprintf"));
            zd->responses[j].fd = i;
            va_end(ap);
            break;
          }
    }
  return (SUCCESS);
}
