##
## Makefile for PSU_2016_zappy in /home/antoine/rendu/psu/PSU_2016_zappy
##
## Made by Antoine Dury
## Login   <antoine.dury@epitech.eu>
##
## Started on  Tue Jun 13 17:54:53 2017 Antoine Dury
## Last update Tue Jun 13 17:54:53 2017 Antoine Dury
##

$@


all: zappy_server zappy_ai

zappy_server:
	make -C Server

zappy_ai:
	make -C AI

re clean fclean all:
	make -C Server $@
	make -C AI $@

.PHONY: $(RULES)
