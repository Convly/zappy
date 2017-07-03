##
## Makefile for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy/AI
##
## Made by Antoine Dury
## Login   <antoine.dury@epitech.eu>
##
## Started on  Tue Jun 13 17:59:05 2017 Antoine Dury
## Last update Tue Jun 13 17:59:05 2017 Antoine Dury
##

SRC		=	zappy_ai

NAME	= 	../zappy_ai

MODULES	=	./modules

DMODULES	=	../modules

CP		=	cp -rf

RM		=	rm -rf

all: $(NAME)

$(NAME):
	$(CP) $(SRC) $(NAME)
	$(CP) $(MODULES) $(DMODULES)
	@printf "\033[0;32mzappy_ai exported successfully !\n\033[0m"

clean:
	$(RM) $(DMODULES)
	@printf "\033[0;32mzappy_ai is clean !\n\033[0m"	

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
