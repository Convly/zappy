/*
** Game.cpp for PSU_2016_zappy in /Users/metge_q/rendu/PSU_2016_zappy/Client/Srcs/Module/Game
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Thu Jun 22 18:14:08 2017 Quentin Metge
** Last update Sun Jul 02 20:17:45 2017 Quentin Metge
*/

#include "Game.hpp"

using namespace zpyclient;

kirr::Pos<float>        angleCamera = kirr::Pos<float>();
static float            distCamera = 120;
static const int        H = 100;

Game::Game(ModuleLoader& ml, std::shared_ptr<Control> control)
:
  AModule(ml, control){
}

Game::~Game(){
}

State           Game::loadAssets(){
  if (!this->_skybox){this->_skybox = this->_control->getKirrlicht().getSceneManager()->addSkyBoxSceneNode(
    this->_control->getKirrlicht().getTexture("./Assets/Textures/Skyboxes/skyboxe_down.png"),
    this->_control->getKirrlicht().getTexture("./Assets/Textures/Skyboxes/skyboxe_up.png"),
    this->_control->getKirrlicht().getTexture("./Assets/Textures/Skyboxes/skyboxe_left.png"),
    this->_control->getKirrlicht().getTexture("./Assets/Textures/Skyboxes/skyboxe_right.png"),
    this->_control->getKirrlicht().getTexture("./Assets/Textures/Skyboxes/skyboxe_front.png"),
    this->_control->getKirrlicht().getTexture("./Assets/Textures/Skyboxes/skyboxe_back.png"));
  }
  else
    this->_skybox->setVisible(true);
  this->_frequenceText = this->_control->getKirrlicht().getGUIEnvironment()->addStaticText(L"100", kirr::Core::rect<kirr::s32>(1065 + 66, 33, 1065 + 150, 33 + 15));
  this->_frequenceText->setOverrideColor(kirr::Video::SColor(255, 255, 255, 255));
  this->_scrollFrequence = this->_control->getKirrlicht().getGUIEnvironment()->addScrollBar(true, kirr::Core::rect<kirr::s32>(1065, 15, 1065 + 150, 15 + 15), nullptr);
  this->_scrollFrequence->setMin(2);
  this->_scrollFrequence->setMax(152);
  this->_scrollFrequence->setSmallStep(5);
  this->_cmdWin = this->_control->getKirrlicht().getGUIEnvironment()->addWindow(kirr::Core::rect<kirr::s32>({0, 0}, {350, 178}), false, L"Commands", nullptr, -1);
  this->_cmdWin->getCloseButton()->setVisible(false);
  this->_tableCmd = this->_control->getKirrlicht().getGUIEnvironment()->addTable(kirr::Core::rect<kirr::s32>({0, 20}, {349, 177}), this->_cmdWin, -1);
  this->_tableCmd->addColumn(L"", -1);
  this->_tableCmd->setColumnWidth(0, 348);
  this->_serverWin = this->_control->getKirrlicht().getGUIEnvironment()->addWindow(kirr::Core::rect<kirr::s32>({0, 670}, {300, 720}), false, L"Server", nullptr, -1);
  this->_serverWin->getCloseButton()->setVisible(false);
  this->_tableServer = this->_control->getKirrlicht().getGUIEnvironment()->addTable(kirr::Core::rect<kirr::s32>({0, 20}, {299, 50}), this->_serverWin, -1);
  this->_tableServer->addColumn(L"", -1);
  this->_tableServer->setColumnWidth(0, 298);
  this->_tableServer->addRow(0);
  this->_playersWin = this->_control->getKirrlicht().getGUIEnvironment()->addWindow(kirr::Core::rect<kirr::s32>({350, 0}, {903, 178}), false, L"Players", nullptr, -1);
  this->_playersWin->getCloseButton()->setVisible(false);
  this->_tablePlayers = this->_control->getKirrlicht().getGUIEnvironment()->addTable(kirr::Core::rect<kirr::s32>({0, 20}, {552, 177}), this->_playersWin, -1);
  this->_tablePlayers->addColumn(L"Team", static_cast<int>(TableCol::TEAM));
  this->_tablePlayers->addColumn(L"Id", static_cast<int>(TableCol::ID));
  this->_tablePlayers->addColumn(L"Pos", static_cast<int>(TableCol::POS));
  this->_tablePlayers->addColumn(L"Dir", static_cast<int>(TableCol::DIR));
  this->_tablePlayers->addColumn(L"Lvl", static_cast<int>(TableCol::LVL));
  this->_tablePlayers->addColumn(L"food", static_cast<int>(TableCol::FOOD));
  this->_tablePlayers->addColumn(L"linemate", static_cast<int>(TableCol::LINEMATE));
  this->_tablePlayers->addColumn(L"deraumere", static_cast<int>(TableCol::DERAUMERE));
  this->_tablePlayers->addColumn(L"sibur", static_cast<int>(TableCol::SIBUR));
  this->_tablePlayers->addColumn(L"mendiane", static_cast<int>(TableCol::MENDIANE));
  this->_tablePlayers->addColumn(L"phiras", static_cast<int>(TableCol::PHIRAS));
  this->_tablePlayers->addColumn(L"thystame", static_cast<int>(TableCol::THYSTAME));
  this->_resourcesWin = this->_control->getKirrlicht().getGUIEnvironment()->addWindow(kirr::Core::rect<kirr::s32>({410, 670}, {846, 720}), false, L"Cell", nullptr, -1);
  this->_resourcesWin->getCloseButton()->setVisible(false);
  this->_tableRessources = this->_control->getKirrlicht().getGUIEnvironment()->addTable(kirr::Core::rect<kirr::s32>({0, 20}, {436, 50}), this->_resourcesWin, -1);
  this->_tableRessources->addColumn(L"FOOD", static_cast<int>(TableCol::FOOD));
  this->_tableRessources->addColumn(L"LINEMATE", static_cast<int>(TableCol::LINEMATE));
  this->_tableRessources->addColumn(L"DERAUMERE", static_cast<int>(TableCol::DERAUMERE));
  this->_tableRessources->addColumn(L"SIBUR", static_cast<int>(TableCol::SIBUR));
  this->_tableRessources->addColumn(L"MENDIANE", static_cast<int>(TableCol::MENDIANE));
  this->_tableRessources->addColumn(L"PHIRAS", static_cast<int>(TableCol::PHIRAS));
  this->_tableRessources->addColumn(L"THYSTAME", static_cast<int>(TableCol::THYSTAME));
  if (!(this->_camera = this->_control->getKirrlicht().getSceneManager()->addCameraSceneNode()))
    return State::EXIT_ON_ERROR;
  this->_camera->setPosition({distCamera * static_cast<float>(std::cos(angleCamera.x)), H, distCamera * static_cast<float>(std::sin(angleCamera.z))});
  this->_camera->setTarget({0, 0, 0});
  this->_control->getKirrlicht().getSceneManager()->setActiveCamera(this->_camera);
  this->_control->getKirrlicht().getSceneManager()->drawAll();
  auto cameraLight = this->_control->getKirrlicht().getSceneManager()->addLightSceneNode(this->_camera);
  cameraLight->setRadius(200);
  this->_meshs.push_back(cameraLight);
  auto centerLight = this->_control->getKirrlicht().getSceneManager()->addLightSceneNode();
  centerLight->setPosition({0, 100, 0});
  centerLight->setRadius(300);
  this->_meshs.push_back(centerLight);
  this->_music = this->_control->getKirrlicht().add3dSound({0, H , 0}, "./Assets/Sounds/music_in_game.wav", true);
  this->_music->setMinDistance(50);
  return State::CONTINUE;
}

State           Game::load(){
  State         state;

  std::cout << "[game] load" << std::endl;
  this->_endGame = false;
  this->_time = -1;
  this->loadAssets();
  this->_control->getSocketServer().write("GRAPHIC");
  state = this->mainLoop();
  if (state == State::NEXT){
    this->_moduleLoader.switcher("connection");
    return State::EXIT_ON_SUCCESS;
  }
  return state;
}

bool            Game::clear(){
  std::cout << "[game] clear" << std::endl;
  this->_music->stop();
  this->_control->getKirrlicht().getGUIEnvironment()->clear();
  for (size_t i = 0; i < this->_meshs.size(); i++)
    this->_control->getKirrlicht().getSceneManager()->addToDeletionQueue(this->_meshs.at(i));
  this->_meshs.clear();
  for (size_t i = 0; i < this->_map.size(); i++)
    this->_map.at(i).clear();
  this->_map.clear();
  this->_players.clear();
  this->_eggs.clear();
  this->_teamsColors.clear();
  this->_time = 100;
  this->_skybox->setVisible(false);
  for (size_t i = 0; i < this->_incantationMesh.size(); i++)
    this->_incantationMesh.at(i)->setEmitter(0);
  for (size_t i = 0; i < this->_incantationMeshInProgress.size(); i++)
    this->_incantationMeshInProgress.at(i)->setEmitter(0);
  this->_incantationMeshInProgress.clear();
  this->_incantationMesh.clear();
  this->_incantationPos.clear();
  this->_transitions.clear();
  this->_dots.clear();
  return true;
}

/************/
/* MainLoop */
/************/
State           Game::mainLoop(){
  int           send = 0;

  this->_state = State::CONTINUE;
  while (this->_state == State::CONTINUE){
    kirr::GlobalEvent events = this->_control->getKirrlicht().getEventReceiver().getEvent();
    this->updateIncantation();
    if (this->_control->getKirrlicht().getDevice()->isWindowActive()){
      this->_control->getKirrlicht().getDriver()->beginScene(true, true, kirr::Color(255, 200, 200, 200));
      this->_control->getKirrlicht().getSceneManager()->drawAll();
      this->_control->getKirrlicht().getGUIEnvironment()->drawAll();
      this->_control->getKirrlicht().getDriver()->endScene();
    }
    else
      this->_control->getKirrlicht().getDevice()->yield();
    this->_control->getSocketServer().initSelect(&this->_control->getSocketServer().getFdRead(), {this->_control->getSocketServer().getNet().sock_fd});
    if (!this->_endGame && this->_control->getSocketServer().checkFdIsFree())
      this->readingLoop();
    if ((send = (send + 1) % 50) == 0){
      for (size_t i = 0; i < this->_players.size(); i++)
        this->_control->getSocketServer().write(std::string("pin " + std::to_string(this->_players.at(i)._playerId)).c_str());
    }
    irr::scene::ISceneNode *sceneNode = this->_control->getKirrlicht().getSceneManager()->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(irr::core::position2di(events.getCursorPosition().x, events.getCursorPosition().y), -1);
    this->_tableRessources->clearRows();
    if (sceneNode && this->isCell(sceneNode)){
      sceneNode->setMaterialTexture(0, this->_control->getKirrlicht().getTexture("./Assets/Textures/Colors/blue.png"));
      this->updateTableResources(sceneNode);
    }
    this->updateTransitions();
    this->updateTablePlayers();
    this->updateFrequence();
    this->updateBroadcast();
    this->updateEndGame();
    this->updateCamera(events);
    if (!this->_control->getKirrlicht().getDevice()->run())
      this->_state = State::EXIT_ON_ERROR;
    else if (this->tryEscape(events.pressTab[kirr::ALL_KEY_CODE::KEY_ESCAPE]))
      this->_state = State::NEXT;
  }
  return this->_state;
}

/***************************/
/*         Update          */
/***************************/
void                  Game::updateFrequence(){
  int                 frequence = this->_scrollFrequence->getPos();
  static int          prevFrequence = frequence;
  std::string         cmd;

  if (frequence < 152){
    if (prevFrequence != frequence){
      cmd = "sst " + std::to_string(frequence);
      this->_control->getSocketServer().write(cmd.c_str());
    }
    prevFrequence = frequence;
  }
}

void                  Game::updateIncantation(){
  static int          timer = 0;
  static size_t       size = 0;

  if (size != this->_incantationMeshInProgress.size())
    timer = 0;
  size = this->_incantationMeshInProgress.size();
  if (timer++ < 20)
    return ;
  timer = 0;
  for (size_t i = 0; i < this->_incantationMeshInProgress.size();){
    this->_incantationMeshInProgress.at(i)->setEmitter(0);
    this->_incantationMeshInProgress.erase(this->_incantationMeshInProgress.begin());
  }
}

void                  Game::updateTransitions(){
  for (size_t i = 0; i < this->_transitions.size();){
    if (this->_transitions.at(i)._depl){
      if (!this->_transitions.at(i)._without)
        this->_transitions.at(i)._mesh->setPosition({static_cast<float>(this->_transitions.at(i)._mesh->getPosition().X + this->_transitions.at(i)._movement.at(0)), static_cast<float>(this->_transitions.at(i)._mesh->getPosition().Y + this->_transitions.at(i)._movement.at(1)), static_cast<float>(this->_transitions.at(i)._mesh->getPosition().Z + this->_transitions.at(i)._movement.at(2))});
      if (this->_transitions.at(i)._without ||
        (Transition::double_equals(this->_transitions.at(i)._mesh->getPosition().X, this->_transitions.at(i)._dest.at(0))
        && Transition::double_equals(this->_transitions.at(i)._mesh->getPosition().Y, this->_transitions.at(i)._dest.at(1))
        && Transition::double_equals(this->_transitions.at(i)._mesh->getPosition().Z, this->_transitions.at(i)._dest.at(2)))){
          this->_transitions.at(i)._mesh->setPosition({static_cast<float>(this->_transitions.at(i)._dest.at(0)), static_cast<float>(this->_transitions.at(i)._dest.at(1)), static_cast<float>(this->_transitions.at(i)._dest.at(2))});
          this->_transitions.erase(this->_transitions.begin() + i);
      }
      else
        i++;
    }
    else{
      this->_transitions.at(i)._mesh->setRotation({0, static_cast<float>(this->_transitions.at(i)._destRotation.at(1)), 0});
      this->_transitions.erase(this->_transitions.begin() + i);
    }
  }
}

void                  Game::updateEndGame(){
  static int          i = 0;

  if (this->_endGame){
    if (i++ == 200)
      this->_state = State::NEXT;
  }
  else
    i = 0;
}

void                  Game::updateTablePlayers(){
  static size_t       sizePlayer = 0;

  if (sizePlayer != this->_players.size())
    this->_tablePlayers->clearRows();
  for (size_t i = 0; i < this->_players.size(); i++){
    if (sizePlayer != this->_players.size())
      this->_tablePlayers->addRow(i);
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::TEAM), std::wstring(this->_players.at(i)._team.begin(), this->_players.at(i)._team.end()).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::ID), std::to_wstring(this->_players.at(i)._playerId).c_str());
    std::string pos = std::to_string(this->_players.at(i)._posX) + " / " + std::to_string(this->_players.at(i)._posY);
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::POS), std::wstring(pos.begin(), pos.end()).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::DIR), std::to_wstring(this->_players.at(i)._orientation).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::LVL), std::to_wstring(this->_players.at(i)._level).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::FOOD), std::to_wstring(this->_players.at(i)._inventory._env.at("food").first).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::LINEMATE), std::to_wstring(this->_players.at(i)._inventory._env.at("linemate").first).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::DERAUMERE), std::to_wstring(this->_players.at(i)._inventory._env.at("deraumere").first).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::SIBUR), std::to_wstring(this->_players.at(i)._inventory._env.at("sibur").first).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::MENDIANE), std::to_wstring(this->_players.at(i)._inventory._env.at("mendiane").first).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::PHIRAS), std::to_wstring(this->_players.at(i)._inventory._env.at("phiras").first).c_str());
    this->_tablePlayers->setCellText(i, static_cast<int>(TableCol::THYSTAME), std::to_wstring(this->_players.at(i)._inventory._env.at("thystame").first).c_str());
  }
  sizePlayer = this->_players.size();
}

void                  Game::updateTableResources(kirr::Scene::ISceneNode* mesh){
  for (size_t y = 0; y < this->_map.size(); y++){
    for (size_t x = 0; x < this->_map.at(y).size(); x++){
      if (this->_map.at(y).at(x)._mesh == mesh){
        this->_tableRessources->addRow(0);
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::FOOD), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("food").first).c_str());
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::LINEMATE), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("linemate").first).c_str());
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::DERAUMERE), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("deraumere").first).c_str());
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::SIBUR), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("sibur").first).c_str());
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::MENDIANE), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("mendiane").first).c_str());
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::PHIRAS), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("phiras").first).c_str());
        this->_tableRessources->setCellText(0, static_cast<int>(TableCol::THYSTAME), std::to_wstring(this->_map.at(y).at(x)._minerals._env.at("thystame").first).c_str());
        return ;
      }
    }
  }
}

void                  Game::updateBroadcast(){
  for (size_t i = 0; i < this->_dots.size();){
    this->_dots.at(i)->setPosition({this->_dots.at(i)->getPosition().X, static_cast<float>(this->_dots.at(i)->getPosition().Y + 1.5), this->_dots.at(i)->getPosition().Z});
    if (this->_dots.at(i)->getPosition().Y > 25){
      this->delFromMeshs(this->_dots.at(i));
      this->_dots.erase(this->_dots.begin() + i);
    }
    else
      i++;
  }
}

void                  Game::updateCamera(kirr::GlobalEvent& events){
  if (events.pressTab[kirr::ALL_KEY_CODE::KEY_RIGHT]){
    angleCamera.x += 0.05;
    angleCamera.z += 0.05;
  }
  else if (events.pressTab[kirr::ALL_KEY_CODE::KEY_LEFT]){
    angleCamera.x -= 0.05;
    angleCamera.z -= 0.05;
  }
  if (events.pressTab[kirr::ALL_KEY_CODE::KEY_UP]){
    if (distCamera >= 1)
      distCamera -= 1;
  }
  else if (events.pressTab[kirr::ALL_KEY_CODE::KEY_DOWN]){
    if (distCamera <= 400)
      distCamera += 1;
  }
  this->_camera->setPosition({distCamera * static_cast<float>(std::cos(angleCamera.x)), H, distCamera * static_cast<float>(std::sin(angleCamera.z))});
  this->_control->getKirrlicht().setListenerPos(this->_camera->getPosition(), this->_camera->getTarget());
}
/*****************************************/

void                  Game::resetTransition(kirr::Scene::ISceneNode* mesh){
  for (size_t i = 0; i < this->_transitions.size(); i++){
    if (this->_transitions.at(i)._mesh == mesh){
      this->_transitions.at(i)._mesh->setPosition({static_cast<float>(this->_transitions.at(i)._dest.at(0)), static_cast<float>(this->_transitions.at(i)._dest.at(1)), static_cast<float>(this->_transitions.at(i)._dest.at(2))});
      this->_transitions.erase(this->_transitions.begin() + i);
      return ;
    }
  }
}

bool                  Game::isCell(kirr::Scene::ISceneNode* mesh){
  bool                check = false;

  for (size_t y = 0; y < this->_map.size(); y++){
    if (this->_map.at(y).empty())
      return check;
    for (size_t x = 0; x < this->_map.at(y).size(); x++){
      if (!this->_map.at(y).at(x)._mesh)
        return check;
      this->_map.at(y).at(x)._mesh->setMaterialTexture(0, nullptr);
      if (this->_map.at(y).at(x)._mesh == mesh)
        check = true;
    }
  }
  return check;
}

kirr::Pos<float>&     Game::getCameraAngle(){
  return angleCamera;
}

/*******************************/
/*            Read             */
/*******************************/
void                  Game::readingLoop(){
  static std::string  buffer;
  std::string         validBuffer;
  char                c_cmd[BUFFER_SIZE];
  int                 rsize;
  static std::vector<std::string> cmds;

  bzero(c_cmd, BUFFER_SIZE + 1);
  if ((rsize = read(this->_control->getSocketServer().getNet().sock_fd, c_cmd, BUFFER_SIZE)) > 0){
    buffer += std::string(c_cmd);
    bzero(c_cmd, BUFFER_SIZE + 1);
    auto lastCr = buffer.find_last_of("\n");
    if (lastCr == std::string::npos)
      return ;
    validBuffer = buffer.substr(0, lastCr);
    buffer = buffer.substr(lastCr + 1);
    std::stringstream ss(validBuffer);
    std::string token;
    while(std::getline(ss, token, '\n')){
      std::cout << "[" << token << "]" << std::endl;
      Command cmd;
      cmd.setCmd(token);
      if (cmds.size() >= 10)
        cmds.erase(cmds.begin());
      cmds.push_back(" - " + token);
      this->_tableCmd->clearRows();
      for (size_t i = 0; i < cmds.size(); i++){
        this->_tableCmd->addRow(i);
        this->_tableCmd->setCellText(i, 0, std::wstring(cmds.at(i).begin(), cmds.at(i).end()).c_str());
      }
      Command::execCmds(*this, cmd);
    }
  }
  if (rsize == 0)
    this->_state = State::NEXT;
}
/*******************************************/
