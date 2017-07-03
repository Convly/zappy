/*
** ZappyData.h for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Includes
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 11:50:20 2017 Antoine Dury
** Last update Sun Jul  2 20:18:05 2017 Antoine Dury
*/

#ifndef ZAPPYDATA_H_
# define ZAPPYDATA_H_

#include "Macros.h"

extern const char	*g_minerals[];

typedef int(*fct)();

/* Orientation enum */
typedef enum	Orientation
{
  NORTH = 1,
  EAST = 2,
  SOUTH,
  WEST
}		Orientation;

/* Action enum */
typedef enum	Action
{
  BROADCAST = 0,
  EJECT = 1,
  FORK,
  FORWARD,
  INCANTATION,
  INVENTORY,
  LEFT,
  LOOK,
  RIGHT,
  SET,
  TAKE,
  EAT,
  DIE,
  HATCHING
}		Action;

/* Resources enum */
typedef enum	Resources
{
  LINEMATE = 0,
  DERAUMERE = 1,
  SIBUR,
  MENDIANE,
  PHIRAS,
  THYSTAME
}		Resources;

/* Vector direction struct */
typedef struct	s_vecDir
{
  int		val;
  int		x;
  int		y;
}		t_vecDir;

/* Client mode enum */
typedef enum	ClientMode
{
  UNDEFINED = -1,
  AI = 0,
  GRAPHIC = 1
}		ClientMode;

/* Pos struct */
typedef struct	s_pos
{
  int		x;
  int		y;
}		t_pos;

/* Incantation struct */
typedef struct  s_incantion
{
  int		nbPlayers;
  int		resources[NB_RESOURCES];
}		t_incantation;

/* Response struct */
typedef struct  s_response
{
  int		fd;
  char		*msg;
}		t_response;

/* Egg struct */
typedef struct  s_egg
{
  int		playerId;
  int		eggId;
  t_pos		pos;
}		t_egg;

/* Client action struct */
typedef struct		s_clientAction
{
  int			playerId;
  struct timeval	tv;
  int			duration;
  Action		action;
  char			*param;
}			t_clientAction;

/* Zappy map struct */
typedef struct  s_zappyMap
{
  int		resources[NB_RESOURCES];
  int		nbFoods;
  int		nbPlayers;
}		t_zappyMap;

/* Team data struct */
typedef struct	s_teamData
{
  char		*name;
  int		nbPlayers;
  int		maxPlayers;
  int		nbEggs;
  int		players[SOMAXCONN];
  t_egg		eggs[MAX_EGGS];
}		t_teamData;

/* Client data struct */
typedef struct	s_clientData
{
  int		fdType;
  fct		fctEvent;
  ClientMode	mode;
  t_pos		pos;
  int		teamId;
  int		orientation;
  int		level;
  int		resources[NB_RESOURCES];
  int		nbFoods;
  bool		connected;
  bool		dead;
}		t_clientData;

/* Zappy data struct */
typedef struct		s_zappyData
{
  int			indexOpt;
  int			port;
  int			width;
  int			height;
  int			freq;
  int			nbTeams;
  int			nbClients;
  int			nbEggs;
  int			serverSocket;
  int			currentClient;
  Orientation		currentClientOrientation;
  bool			exitHelp;
  t_clientData		clients[SOMAXCONN];
  t_teamData		*teams;
  t_zappyMap		**map;
  t_clientAction	actions[MAX_ACTIONS];
  t_response		responses[MAX_RESPONSES];
}			t_zappyData;

/* Circular buffer sturct */
typedef struct	s_circularBuffer
{
  void		*buffer;
  void		*endBuffer;
  void		*head;
  void		*tail;
  int		nbItem;
}		t_circularBuffer;

/* Commands struct */
typedef struct	s_commands
{
  char		*cmd;
  int		(*exec)(t_zappyData*, char**, const int);
}		t_commands;

/* Launching options struct */
typedef struct	s_launching
{
  char		*opt;
  int		(*exec)(t_zappyData*, char**, const int);
}		t_launching;

#endif /* !ZAPPYDATA_H_ */
