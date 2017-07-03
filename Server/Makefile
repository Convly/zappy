##
## Makefile for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/Server
##
## Made by Antoine Dury
## Login   <antoine.dury@epitech.eu>
##
## Started on  Tue Jun 13 17:59:05 2017 Antoine Dury
## Last update Sun Jul  2 20:19:14 2017 Antoine Dury
##

NAME	=	../zappy_server

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-W -Wall -Werror -Wextra	\
		-I./Includes -lm		\

SRCS	=	Srcs/Server/Init.c		\
		Srcs/Server/Server.c		\
		Srcs/Server/Exec.c		\
		Srcs/Server/Handle.c		\
		Srcs/Server/Response.c		\
		Srcs/Server/Action.c		\
		Srcs/Server/Close.c		\
		Srcs/Server/Check/Mode.c	\
		Srcs/Server/Check/Team.c	\
		Srcs/Server/Getter/Team.c	\
		Srcs/Server/Setter/Team.c	\
		Srcs/Server/Setter/Resources.c	\
		Srcs/Server/Check/Player.c	\
		Srcs/Server/Getter/Player.c	\
		Srcs/Server/Setter/Player.c	\
		Srcs/Server/Setter/Responses.c	\
		Srcs/Server/Check/Map.c		\

SRCS	+=	Srcs/Launching/Launching.c	\
		Srcs/Launching/Port.c		\
		Srcs/Launching/Width.c		\
		Srcs/Launching/Height.c		\
		Srcs/Launching/Name.c		\
		Srcs/Launching/Clients.c	\
		Srcs/Launching/Frequence.c	\

SRCS	+=	Srcs/Commands/Process.c			\
		Srcs/Commands/AI/Broadcast.c		\
		Srcs/Commands/AI/Eject.c		\
		Srcs/Commands/AI/Fork.c			\
		Srcs/Commands/AI/Getter.c		\
		Srcs/Commands/AI/Incantation.c		\
		Srcs/Commands/AI/Look1.c		\
		Srcs/Commands/AI/Look2.c		\
		Srcs/Commands/AI/Movement1.c		\
		Srcs/Commands/AI/Movement2.c		\
		Srcs/Commands/AI/Set.c			\
		Srcs/Commands/AI/Take.c			\
		Srcs/Commands/AI/Team.c			\
		Srcs/Commands/AI/Hunger.c		\
		Srcs/Commands/GRAPHIC/Graphic.c		\
		Srcs/Commands/GRAPHIC/Commands1.c	\
		Srcs/Commands/GRAPHIC/Commands2.c	\
		Srcs/Commands/GRAPHIC/Map.c		\

SRCS	+=	Srcs/Utils/CircularBuffer.c	\
		Srcs/Utils/String.c		\
		Srcs/Utils/Calculations.c	\
		Srcs/Utils/Log.c		\
		Srcs/Utils/Error.c		\
		Srcs/Utils/Free.c		\

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\033[0;32mzappy_server compiled successfully !\n\033[0m"

clean:
	$(RM) $(OBJS)
	@printf "\033[0;32mzappy_server is clean !\n\033[0m"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
