/*
** Process.c for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Srcs/Commands
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 22 10:50:20 2017 Antoine Dury
** Last update Sun Jul  2 20:21:50 2017 Antoine Dury
*/

#include "Zappy.h"

static t_commands	g_commands[] =
  {
    {"Broadcast", broadcastCmd},
    {"Connect_nbr", connectNbrCmd},
    {"Eject", ejectCmd},
    {"Fork", forkCmd},
    {"Forward", forwardCmd},
    {"Incantation", incantationCmd},
    {"Inventory", inventoryCmd},
    {"Left", leftCmd},
    {"Look", lookCmd},
    {"Right", rightCmd},
    {"Set", setCmd},
    {"Take", takeCmd},
    {"GRAPHIC", graphicCmd},
    {"bct", bctCmd},
    {"mct", mctCmd},
    {"msz", mszCmd},
    {"pin", pinCmd},
    {"plv", plvCmd},
    {"ppo", ppoCmd},
    {"sgt", sgtCmd},
    {"sst", sstCmd},
    {"tna", tnaCmd},
    {NULL, NULL}
  };

static int	unknownCommand(t_zappyData *zd)
{
  return (rightMode(zd, GRAPHIC) ? addResponse(zd, zd->currentClient, "suc") :
	  addResponse(zd, zd->currentClient, "ko"));
}

static int	getNbCommands(const char *str, const char delim)
{
  int		i;
  int		nbCommands;

  i = -1;
  nbCommands = 0;
  while (str[++i])
    {
      if (str[i] == delim)
        nbCommands++;
    }
  if (nbCommands == 0)
    return (1);
  return (nbCommands);
}

static int	execCommands(t_zappyData *zd, char *buffer)
{
  int		i;
  int		nbParam;
  char		**cmd;

  i = -1;
  nbParam = getNbTokens(buffer, ' ');
  if (!(cmd = split(buffer, " ", nbParam)))
    return (SUCCESS);
  while (g_commands[++i].cmd)
    {
      if (strcmp(cmd[0], g_commands[i].cmd) == 0)
        {
          if (g_commands[i].exec(zd, cmd, nbParam) == SUCCESS)
            return (freeTokens(cmd, nbParam, SUCCESS));
          return (freeTokens(cmd, nbParam, FAILURE));
        }
    }
  return ((teamExists(zd, cmd[0], zd->nbTeams) ? teamCmd(zd, cmd, nbParam) :
	   unknownCommand(zd)) == SUCCESS && freeTokens(cmd, nbParam, SUCCESS)
	  == SUCCESS ? SUCCESS : FAILURE);
}

int	processCommands(t_zappyData *zd, char *buffer)
{
  int	i;
  int	nbCommands;
  char	**commands;

  i = -1;
  nbCommands = getNbCommands(buffer, '\n');
  if (!(commands = split(buffer, "\n", nbCommands)))
    return (FAILURE);
  while (++i < nbCommands)
    {
      if (!commands[i])
        continue;
      if (debugLog("Command received from client n°%d - ['%s']",
		   zd->currentClient, commands[i]) == FAILURE ||
	  execCommands(zd, commands[i]) == FAILURE)
        return (freeTokens(commands, nbCommands, FAILURE));
    }
  return (freeTokens(commands, nbCommands, SUCCESS));
}
