//
// ModuleLoader.hpp for ModuleLoader in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/ModuleLoader/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:38:16 2017 jsx
// Last update Fri Jun 16 21:25:45 2017 Maxime Cauvin
//

#ifndef MODULE_LOADER_HPP_
#define MODULE_LOADER_HPP_

#include "Error.hpp"
#include "Kirrlicht.hpp"
#include "Control.hpp"

namespace zpyclient{
  enum class State : int{
    EXIT_ON_SUCCESS = 0,
    EXIT_ON_ERROR = 1,
    CONTINUE,
    NEXT
  };

  class IModule;

  class ModuleLoader{
  public:
    ModuleLoader(const std::string& startingModuleName = "connection");
    ~ModuleLoader();

  public:
    bool    switcher(const std::string& moduleName);

  public:
    bool    loadMeshs();
    bool    loadTextures();
    bool    loadFonts();

  public:
    std::unordered_map<std::string, std::shared_ptr<IModule>>& getModules(){return this->_modules;}
    std::shared_ptr<IModule>   getCurrent() const{return this->_current;}

  private:
    std::shared_ptr<Control>    _control;
    std::shared_ptr<IModule>    _current = nullptr;
    std::unordered_map<std::string, std::shared_ptr<IModule>>  _modules;
  };
} /* zpyclient */

#endif /* end of include guard: MODULE_LOADER_HPP_ */
