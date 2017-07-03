//
// ModuleLoader.cpp for ModuleLoader in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Bin/Srcs/Module/ModuleLoader/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:38:05 2017 jsx
// Last update Sun Jun 18 02:48:33 2017 Maxime Cauvin
//

#include "ModuleLoader.hpp"
#include "Connection.hpp"
#include "Game.hpp"

using namespace zpyclient;

ModuleLoader::ModuleLoader(const std::string& startingModuleName)
:
  _control(std::make_shared<Control>()),
  _current(nullptr),
  _modules({
    {"connection", std::make_shared<Connection>(*this, this->_control)},
    {"game", std::make_shared<Game>(*this, this->_control)}
  }){
  if (!this->_control->getKirrlicht().start("Zappy", kirr::Pos<int>(1280, 720))
    || !this->loadFonts()
    || !this->loadMeshs()
    || !this->loadTextures())
    throw Error("Load window");
  if (!this->switcher(startingModuleName))
    throw Error("Constructor moduleLoader");
}

ModuleLoader::~ModuleLoader(){
  this->_current->clear();
  this->_control->getKirrlicht().drop();
}

////////////////////////////////////
//_____________TOOLS _____________//
////////////////////////////////////
bool                    ModuleLoader::switcher(const std::string& moduleName){
  if (this->_modules.find(moduleName) == this->_modules.end()){
    std::cerr << "module <" << moduleName << "> Doesn't exist"<< std::endl;
    return false;
  }
  if (this->_current && !this->_current->clear())
    return false;
  this->_current = this->_modules[moduleName];
  std::cerr << "Switch to <" << moduleName << ">" << std::endl;
  if (this->_current->load() == State::EXIT_ON_ERROR)
    return false;
  return true;
}

////////////////////////////////////
//_____________LOADERS____________//
////////////////////////////////////
bool                    ModuleLoader::loadMeshs(){
  std::vector<std::string>  allMesh({
    "./Assets/Objects/deraumere.obj",
    "./Assets/Objects/linemate.obj",
    "./Assets/Objects/mendiane.obj",
    "./Assets/Objects/phiras.obj",
    "./Assets/Objects/sibur.obj",
    "./Assets/Objects/thystame.obj",
    "./Assets/Objects/food.obj",
    "./Assets/Objects/ship.obj",
    "./Assets/Objects/asteroid.obj"
  });
  if (!this->_control->getKirrlicht().loadAlphabet("./Assets/Objects/AlphaNumeric/"))
    return false;
  for (size_t i = 0; i < allMesh.size(); i++){
    if (!this->_control->getKirrlicht().loadStaticMesh(allMesh.at(i))){
        std::cerr << "Error: Missing Mesh: " << allMesh.at(i) << '\n';
        return false;
      }
  }
  return true;
}

bool                    ModuleLoader::loadTextures()
{
  std::vector<std::string>  allTexture({
    "./Assets/Textures/Backgrounds/neurone_connection.jpg",
    "./Assets/Textures/Sprites/fire.bmp",
    "./Assets/Textures/Sprites/smoke.bmp",
    "./Assets/Textures/Colors/blue.png",
    "./Assets/Textures/Colors/cyan.png",
    "./Assets/Textures/Colors/green.png",
    "./Assets/Textures/Colors/orange.png",
    "./Assets/Textures/Colors/pink.png",
    "./Assets/Textures/Colors/purple.png",
    "./Assets/Textures/Colors/yellow.png",
    "./Assets/Textures/Skyboxes/skyboxe_up.png",
    "./Assets/Textures/Skyboxes/skyboxe_down.png",
    "./Assets/Textures/Skyboxes/skyboxe_left.png",
    "./Assets/Textures/Skyboxes/skyboxe_right.png",
    "./Assets/Textures/Skyboxes/skyboxe_front.png",
    "./Assets/Textures/Skyboxes/skyboxe_back.png"
  });
  for (size_t i = 0; i < allTexture.size(); i++){
    if (!this->_control->getKirrlicht().loadTexture(allTexture.at(i)))
      std::cerr << "Error: Missing Texture: " << allTexture.at(i) << std::endl;
  }
  return true;
}

bool                    ModuleLoader::loadFonts(){
  return (this->_control->getKirrlicht().loadFonts("./Assets/Fonts/ebrima", ".xml", {10, 12, 14, 16, 18, 20, 26, 32, 36, 42, 48}, this->_control->getFonts()));
}
