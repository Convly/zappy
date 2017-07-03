/*
** Mode.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Server/Check
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 14:52:28 2017 Antoine Dury
** Last update Sun Jul  2 21:05:29 2017 Antoine Dury
*/

#include "Zappy.h"

bool	rightMode(t_zappyData *zd,
		  const ClientMode mode)
{
  return (zd->clients[zd->currentClient].mode == mode);
}
