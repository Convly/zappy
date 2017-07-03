/*
** CircularBuffer.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Utils
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Wed Jun 28 12:13:53 2017 Antoine Dury
** Last update Wed Jun 28 12:14:52 2017 Antoine Dury
*/

#include "Zappy.h"

int	initCircularBuffer(t_circularBuffer *cb)
{
  if ((cb->buffer = malloc(MAX_ITEM * BUFFER_SIZE)) == NULL)
    return (printPerror("malloc"));
  cb->endBuffer = (char *)cb->buffer + MAX_ITEM * BUFFER_SIZE;
  cb->head = cb->tail = cb->buffer;
  cb->nbItem = 0;
  return (SUCCESS);
}

int	addCircularBuffer(t_circularBuffer *cb, const void *data)
{
  if (memcpy(cb->head, data, BUFFER_SIZE) == NULL)
    return (printPerror("memcpy"));
  cb->head = (char*)cb->head + BUFFER_SIZE;
  if (cb->head == cb->endBuffer)
    cb->head = cb->buffer;
  cb->nbItem++;
  return (SUCCESS);
}
