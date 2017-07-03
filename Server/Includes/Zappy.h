/*
** Zappy.h for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server/Includes
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Thu Jun 15 11:41:56 2017 Antoine Dury
** Last update Sun Jul 02 20:26:00 2017 Antoine Dury
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

# define _GNU_SOURCE

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "ZappyData.h"
#include "Debug.h"

/* Server */
int	zappyServer(char**);
int	initZappyData(t_zappyData*);
int	initZappyMap(t_zappyData*);
int	initZappyServer(t_zappyData*);
int	processZappyServer(t_zappyData*);
int	printServerUsage(t_zappyData*, const char*, const int);
int	handleClientEvent(t_zappyData*, fd_set*);
int	handleClientConnection(t_zappyData*, const int);
int	handleClientCommand(t_zappyData*, const int);
int	addResponse(t_zappyData *zd, const int, const char*, ...);
int	addIncantationResponse(t_zappyData *zd, const int);
int	addGlobalResponse(t_zappyData*, const char*, ...);
int	sendResponses(t_zappyData*);
int	addAction(t_zappyData*, t_clientAction);
int	addFeeding(t_zappyData*, t_clientAction);
int	getNextAction(t_zappyData*);
int	getNextFeeding(t_zappyData*);
int	processAction(t_zappyData*, const int);
int	closeClientConnection(t_zappyData*, const int, const int);
int	shutdownClientConnection(t_zappyData*, const int);
bool	rightMode(t_zappyData*, const ClientMode);
bool	teamExists(t_zappyData*, const char*, const int);
int	getTeamId(t_zappyData*, const char*);
int	getNbLevel(const t_zappyData*, const int, const int);
void	initTeams(t_zappyData*);
void	setMaxPlayers(t_zappyData*, const int);
void	unsetPlayerTeam(t_zappyData*, const int);
int	setResources(t_zappyData*, const Resources, int);
bool	playerExists(t_zappyData*, const int);
bool	playerHasFood(t_zappyData*, const int);
bool	playerHasMineral(t_zappyData*, const int, const Resources);
bool	playerSamePos(const t_pos, const t_pos);
bool	checkPlayers(t_zappyData*, const int, const int);
bool	checkMinerals(t_zappyData*, const int, const t_incantation);
bool	checkLevel(t_zappyData*, const t_pos, const int);
t_pos	getPlayerPos(t_zappyData*, const int);
int	getPlayerOrientation(t_zappyData*, const int);
int	getPlayerLevel(t_zappyData*, const int);
char	*getPlayerTeam(t_zappyData*, const int);
void	initPlayers(t_zappyData*);
void	initActions(t_zappyData*);
void	unsetPlayerInfos(t_zappyData*, const int);
void	initResponses(t_zappyData*);
bool	foodExists(const t_zappyData*, const int, const int);
bool	mineralExists(const t_zappyData*, const int, const int,
		      const Resources);

/* Launching */
int	processLaunchingOptions(t_zappyData*, char**);
int	portOption(t_zappyData*, char**, const int);
int	widthOption(t_zappyData*, char**, const int);
int	heightOption(t_zappyData*, char**, const int);
int	nameOption(t_zappyData*, char**, const int);
int	clientsOption(t_zappyData*, char**, const int);
int	frequenceOption(t_zappyData*, char**, const int);

/* Commands */
int	processCommands(t_zappyData*, char*);
int	broadcastCmd(t_zappyData*, char**, const int);
int	processBroadcast(t_zappyData*, char**, const int);
int	getClosestPath(const int, const int, const int);
int	getRelativePos(const int, const int);
int	getSoundDirection(const t_zappyData*, const t_clientData, const int,
			  const int);
int	connectNbrCmd(t_zappyData*, char**, const int);
int	ejectCmd(t_zappyData*, char**, const int);
int	processEject(t_zappyData*, char**, const int);
int	forkCmd(t_zappyData*, char**, const int);
int	processFork(t_zappyData*, char**, const int);
int	processHatching(t_zappyData*, char**, const int);
void	removeHatchingAction(t_zappyData*, const int);
int	getNextEgg(const t_zappyData*, const int);
int	forwardCmd(t_zappyData*, char**, const int);
int	processForward(t_zappyData*, char**, const int);
int	incantationCmd(t_zappyData*, char**, const int);
int	processIncantation(t_zappyData*, char**, const int);
int	inventoryCmd(t_zappyData*, char**, const int);
int	processInventory(t_zappyData*, char**, const int);
int	leftCmd(t_zappyData*, char**, const int);
int	processLeft(t_zappyData*, char**, const int);
int	lookCmd(t_zappyData*, char**, const int);
int	processLook(t_zappyData*, char**, const int);
void	processNorthLook(t_zappyData*, t_pos, const int, const int);
void	processSouthLook(t_zappyData*, t_pos, const int, const int);
void	processWestLook(t_zappyData*, t_pos, const int, const int);
void	processEastLook(t_zappyData*, t_pos, const int, const int);
int	lookSquare(const t_zappyMap);
int	rightCmd(t_zappyData*, char**, const int);
int	processRight(t_zappyData*, char**, const int);
int	setCmd(t_zappyData*, char**, const int);
int	processSet(t_zappyData*, char**, const int);
int	takeCmd(t_zappyData*, char**, const int);
int	processTake(t_zappyData*, char**, const int);
int	teamCmd(t_zappyData*, char**, const int);
int	graphicCmd(t_zappyData*, char**, const int);
int	bctCmd(t_zappyData*, char**, const int);
int	processBctCmd(t_zappyData*, const t_pos, const int, const bool);
int	mctCmd(t_zappyData*, char**, const int);
int	processGlobalMctCmd(t_zappyData*);
int	mszCmd(t_zappyData*, char**, const int);
int	pinCmd(t_zappyData*, char**, const int);
int	processPinCmd(t_zappyData*, const int);
int	plvCmd(t_zappyData*, char**, const int);
int	ppoCmd(t_zappyData*, char**, const int);
int	sgtCmd(t_zappyData*, char**, const int);
int	sstCmd(t_zappyData*, char**, const int);
int	tnaCmd(t_zappyData*, char**, const int);
int	processEat(t_zappyData*, char**, const int);
int	processDie(t_zappyData*, char**, const int);

/* Utils */
int	initCircularBuffer(t_circularBuffer*);
int	addCircularBuffer(t_circularBuffer*, const void*);
char	**split(char*, const char*, const int);
char	*reallocat(char*, const char*);
int	getNbTokens(const char*, const char);
int	freeTokens(char**, const int, const int);
int	circularLook(const int, const int);
int	getClosestPath(const int, const int, const int);
int	startLog(const char*, ...);
int	infoLog(const char*, ...);
int	debugLog(const char*, ...);
int	errorLog(const char*, ...);
int	printError(const char*);
int	printPerror(char*);
int	printErrorLaunching(t_zappyData*, const int, const char*, const char*);
int	freeZappyData(const t_zappyData*, const int);
void	freeTeams(const t_zappyData*);

#endif /* !ZAPPY_H_ */
