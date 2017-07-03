/*
** String.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Utils
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 15:50:24 2017 Antoine Dury
** Last update Sun Jul  2 20:49:53 2017 Antoine Dury
*/

#include "Zappy.h"

char	**split(char *str,
		const char *delim,
		const int nbTokens)
{
  int	i;
  char  **tokens;
  char  *tmp;

  i = 0;
  if (nbTokens == -1 || (tokens = malloc(sizeof(char*) * nbTokens)) == NULL ||
      (tmp = strtok(str, delim)) == NULL || (tokens[i] = strdup(tmp)) == NULL)
    return (NULL);
  while (++i < nbTokens)
    {
      tmp = strtok(NULL, delim);
      if (tmp)
        tokens[i] = strdup(tmp);
      else
        tokens[i] = NULL;
    }
  return (tokens);
}

char	*reallocat(char *dest,
		   const char *src)
{
  int	oldSize;

  oldSize = strlen(dest);
  if ((dest = realloc(dest, sizeof(char) * (oldSize + strlen(src) + 1)))
      == NULL)
    {
      printPerror("malloc");
      return (NULL);
    }
  bzero(dest + oldSize, strlen(src));
  if (strcat(dest, src) == NULL)
    {
      printPerror("strcat");
      return (NULL);
    }
  return (dest);
}

int	getNbTokens(const char *str, const char delim)
{
  int	i;
  int	nbToken;

  i = 0;
  nbToken = 0;
  if (!str)
    return (-1);
  while (str[i])
    {
      if (str[i] == delim)
        nbToken++;
      i++;
    }
  return (nbToken + 1);
}

int	freeTokens(char **tokens,
		   const int nbTokens,
		   const int retCode)
{
  int	i;

  i = -1;
  while (++i < nbTokens)
    free(tokens[i]);
  free(tokens);
  return (retCode);
}
