/*
** Log.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Utils
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 12:32:30 2017 Antoine Dury
** Last update Sun Jul  2 20:48:58 2017 Antoine Dury
*/

#include "Zappy.h"

int	startLog(const char *msg, ...)
{
  va_list	ap;

  va_start(ap, msg);
  if (printf("\x1b[32m[START]\x1b[0m : ") < 0)
    return (printPerror("printf"));
  if (vprintf(msg, ap) < 0)
    return (printPerror("vprintf"));
  if (printf("\n") < 0)
    return (printPerror("printf"));
  va_end(ap);
  return (SUCCESS);
}

int	infoLog(const char *msg, ...)
{
  va_list	ap;

  va_start(ap, msg);
  if (printf("\x1b[36m[INFO]\x1b[0m  : ") < 0)
    return (printPerror("printf"));
  if (vprintf(msg, ap) < 0)
    return (printPerror("vprintf"));
  if (printf("\n") < 0)
    return (printPerror("printf"));
  va_end(ap);
  return (SUCCESS);
}

int debugLog(const char *msg, ...)
{
  va_list	ap;

  if (!DEBUG_MODE)
    return (SUCCESS);
  va_start(ap, msg);
  if (printf("\x1b[33m[DEBUG]\x1b[0m : ") < 0)
    return (printPerror("printf"));
  if (vprintf(msg, ap) < 0)
    return (printPerror("vprintf"));
  if (printf("\n") < 0)
    return (printPerror("printf"));
  va_end(ap);
  return (SUCCESS);
}

int	errorLog(const char *msg, ...)
{
  va_list	ap;

  va_start(ap, msg);
  if (fprintf(stderr, "\x1b[31m[ERROR]\x1b[0m : ") < 0)
    return (printPerror("fprintf"));
  if (vfprintf(stderr, msg, ap) < 0)
    return (printPerror("vfprintf"));
  if (fprintf(stderr, "\n") < 0)
    return (printPerror("fprintf"));
  va_end(ap);
  return (SUCCESS);
}
