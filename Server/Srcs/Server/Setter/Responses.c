/*
** Responses.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Setter
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 28 14:17:45 2017 Antoine Dury
** Last update Wed Jun 28 14:26:19 2017 Antoine Dury
*/

#include "Zappy.h"

void	initResponses(t_zappyData *zd)
{
  int	i;

  i = -1;
  while (++i < MAX_RESPONSES)
    zd->responses[i].fd = 0;
}
