//
// IModule.hpp for IMODULE in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Modules/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:23:00 2017 jsx
// Last update Sat May  6 01:03:26 2017 jsx
//

#ifndef IMODULE_INDIE_STUDIO_HPP_
#define IMODULE_INDIE_STUDIO_HPP_

#include "ModuleLoader.hpp"
#include <iostream>
#include <string>

namespace zpyclient{
  class IModule{
  public:
    virtual ~IModule(){};

  public:
    virtual State     load() = 0;
    virtual bool      clear() = 0;
    virtual State     mainLoop() = 0;
  };
} /* zpyclient */

#endif /* end of include guard: IMODULE_INDIE_STUDIO_HPP_ */
