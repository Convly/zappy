//
// Connection.cpp for Connection in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/Connection/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Tue May  9 20:11:38 2017 JSX
// Last update Sun Jun 18 22:11:31 2017 Maxime Cauvin
//

#include "Connection.hpp"

using namespace zpyclient;

Connection::Connection(ModuleLoader& ml, std::shared_ptr<Control> control)
:
  AModule(ml, control){
}

Connection::~Connection(){
}

State           Connection::load(){
  State         state;

  std::cout << "[connection] load" << std::endl;
  if (!(this->_camera = this->_control->getKirrlicht().getSceneManager()->addCameraSceneNode()))
    return State::EXIT_ON_ERROR;
  this->_camera->setPosition({0, 0, -100});
  this->_camera->setTarget({0, 0, 0});
  this->_control->getKirrlicht().getSceneManager()->setActiveCamera(this->_camera);
  this->_background = this->_control->getKirrlicht().getTexture("./Assets/Textures/Backgrounds/neurone_connection.jpg");
  this->_control->getKirrlicht().displayString("ZAPPY", kirr::Pos<float>(-83, 110, 100), kirr::Pos<float>(0, 180, 0), kirr::Pos<float>(0.8, 0.8, 0.8), this->_meshs, "./Assets/Textures/Colors/blue.png");
  this->_components["ipTXT"] = this->_control->getKirrlicht().putText(this->_control->getFonts()[26], L"ip", kirr::Core::rect<kirr::s32>(610, 292, 710, 332), kirr::Color(255, 255, 255, 255));
  this->_components["ipBOX"] = this->_control->getKirrlicht().getGUIEnvironment()->addEditBox(L"", kirr::Core::rect<kirr::s32>(430, 330, 830, 358));
  reinterpret_cast<kirr::Gui::IGUIEditBox*>(this->_components["ipBOX"])->setOverrideFont(this->_control->getFonts()[26]);
  this->_components["portTXT"] = this->_control->getKirrlicht().putText(this->_control->getFonts()[26], L"port", kirr::Core::rect<kirr::s32>(600, 395, 700, 435), kirr::Color(255, 255, 255, 255));
  this->_components["portBOX"] = this->_control->getKirrlicht().getGUIEnvironment()->addEditBox(L"", kirr::Core::rect<kirr::s32>(430, 430, 830, 458));
  reinterpret_cast<kirr::Gui::IGUIEditBox*>(this->_components["portBOX"])->setOverrideFont(this->_control->getFonts()[26]);
  this->_components["errorTXT"] = this->_control->getKirrlicht().putText(this->_control->getFonts()[42], L"", kirr::Core::rect<kirr::s32>(430, 200, 1030, 240), kirr::Color(255, 255, 0, 0));
  this->_components["connectBT"] = this->_control->getKirrlicht().getGUIEnvironment()->addButton(kirr::Core::rect<kirr::s32>(545, 530, 695, 556), 0, 0, L"Connect", L"Attempt a connection to the server");
  this->_control->getKirrlicht().getSceneManager()->drawAll();
  if ((state = this->mainLoop()) != State::NEXT)
    return state;
  this->_moduleLoader.switcher("game");
  return State::EXIT_ON_SUCCESS;
}

bool            Connection::clear(){
  std::cout << "[connection] clear" << std::endl;
  this->_control->getKirrlicht().getGUIEnvironment()->clear();
  for (size_t i = 0; i < this->_meshs.size(); i++)
    this->_control->getKirrlicht().getSceneManager()->addToDeletionQueue(this->_meshs.at(i));
  this->_meshs.clear();
  return true;
}

/************/
/* MainLoop */
/************/
State           Connection::mainLoop(){
  this->_state = State::CONTINUE;
  while (this->_state == State::CONTINUE){
    kirr::GlobalEvent events = this->_control->getKirrlicht().getEventReceiver().getEvent();
    if (this->_control->getKirrlicht().getDevice()->isWindowActive()){
      this->_control->getKirrlicht().getDriver()->beginScene(true, true, kirr::Color(255, 200, 200, 200));
      this->_control->getKirrlicht().getDriver()->draw2DImage(this->_background, kirr::Core::position2d<kirr::s32>(0, 0));
      for (auto it = this->_components.begin(); it != this->_components.end(); it++)
        it->second->draw();
      this->_control->getKirrlicht().getSceneManager()->drawAll();
      this->_control->getKirrlicht().getDriver()->endScene();
    }
    else
      this->_control->getKirrlicht().getDevice()->yield();
    if (!this->_control->getKirrlicht().getDevice()->run())
      this->_state = State::EXIT_ON_ERROR;
    else if (this->tryEscape(events.pressTab[kirr::ALL_KEY_CODE::KEY_ESCAPE]))
      this->_state = State::EXIT_ON_SUCCESS;
    else if (this->connect())
      this->_state = State::NEXT;
  }
  return this->_state;
}
/*******************************************/

bool                  Connection::connect(){
  if (reinterpret_cast<kirr::Gui::IGUIButton*>(this->_components["connectBT"])->isPressed()){
    std::wstring wsps(this->_components["ipBOX"]->getText());
    std::wstring wspa(this->_components["portBOX"]->getText());
    std::string ip(wsps.begin(), wsps.end());
    std::string port(wspa.begin(), wspa.end());
    if (port.empty())
      port = "2685";
    if (ip == "localhost")
      ip = "127.0.0.1";
    if (this->_control->getSocketServer().connection((char*)ip.c_str(), std::stoi(port)) < 0)
      return false;
    return true;
  }
  return false;
}
