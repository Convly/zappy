/*
** Control.hpp for PSU_2016_zappy in /Users/metge_q/rendu/PSU_2016_zappy/Client/Srcs/Control
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Wed Jun 21 23:31:38 2017 Quentin Metge
** Last update Tue Jun 27 11:30:42 2017 Quentin Metge
*/

#ifndef CONTROL_HPP_
# define CONTROL_HPP_

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Kirrlicht.hpp"
#include "Socket.hpp"

namespace zpyclient{
  class Control
  {
  public:
    Control();
    virtual ~Control();

  public:
    Socket&               getSocketServer(){return this->_socketServer;}
    kirr::Kirrlicht&      getKirrlicht(){return this->_kirrlicht;}
    std::unordered_map<int, kirr::Gui::IGUIFont*>&  getFonts(){return this->_fonts;}

  public:
    kirr::Pos<float>      calcMapPos(kirr::Pos<float> pos);

  private:
    Socket                _socketServer;
    kirr::Kirrlicht       _kirrlicht;
    std::unordered_map<int, kirr::Gui::IGUIFont*> _fonts;
  };
}

#endif
