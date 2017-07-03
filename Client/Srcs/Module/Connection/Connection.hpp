//
// GameClient.hpp for GameClient in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 19:25:46 2017 jsx
// Last update Fri Jun 16 17:22:52 2017 Maxime Cauvin
//

#ifndef CONNECTION_HPP_
# define CONNECTION_HPP_

#include "AModule.hpp"

namespace zpyclient{
  class Connection : public AModule{
  public:
    Connection(ModuleLoader& ml, std::shared_ptr<Control> control);
    virtual ~Connection();

  public:
    virtual State     load();
    virtual bool      clear();
    virtual State     mainLoop();

  public:
    bool              connect();

  private:
    kirr::Video::ITexture*  _background;
    std::unordered_map<std::string, kirr::Gui::IGUIElement*> _components;
  };
} /* zpyclient */

#endif
