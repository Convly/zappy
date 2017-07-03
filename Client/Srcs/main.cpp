/*
** main.cpp for PSU_2016_zappy in /Users/metge_q/rendu/PSU_2016_zappy/Graphic/Srcs
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Wed Jun 21 11:19:11 2017 Quentin Metge
** Last update Thu Jun 29 13:45:36 2017 Quentin Metge
*/

#include "ModuleLoader.hpp"

int             main(int ac, char** av){
  try{
    if (ac > 1){
      if (std::string(av[1]) == "--help")
        std::cerr << "./client_zappy <module name>" << std::endl;
      else
        zpyclient::ModuleLoader  moduleLoader(av[1]);
    }
    else{
      zpyclient::ModuleLoader  moduleLoader;
    }
  }
  catch(std::exception& e){
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
