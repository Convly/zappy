/*
** Error.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Utils
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 11:46:41 2017 Antoine Dury
** Last update Sun Jul  2 20:47:34 2017 Antoine Dury
*/

#include "Zappy.h"

int	printPerror(char *tmp)
{
  char  func[strlen(tmp)];

  strcpy(func, tmp);
  if (fprintf(stderr, "\x1b[31m[ERROR]\x1b[0m : ") < 0)
    return (printPerror("fprintf"));
  perror(strcat(func, " "));
  return (FAILURE);
}

int	printErrorLaunching(t_zappyData *zd,
			    const int errorCode,
			    const char *prog,
			    const char *arg)
{
  if (errorCode == 0)
    {
      if (fprintf(stderr, "%s: option '%s' requires an argument\n\n", prog,
		  arg) < 0)
	printPerror("fprintf");
    }
  else if (errorCode == 1)
    {
      if (fprintf(stderr, "%s: unrecognized option '%s'\n\n", prog, arg) < 0)
	printPerror("fprintf");
    }
  return (printServerUsage(zd, prog, FAILURE));
}
