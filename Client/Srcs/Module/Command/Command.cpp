/*
** Command.cpp for PSU_2016_zappy in /Users/metge_q/rendu/PSU_2016_zappy/Client/Srcs/Module/Command
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Jun 26 14:08:03 2017 Quentin Metge
** Last update Sun Jul 02 15:52:54 2017 Quentin Metge
*/

#include "Game.hpp"
#include "Command.hpp"

using namespace zpyclient;

static const int                leaderTray = 2;
static int                      adjustmentX = -1;
static int                      adjustmentY = -1;
static kirr::vector3df          scaleCell;
static std::vector<std::string> colors = {
  "",
  "purple.png",
  "green.png",
  "orange.png",
  "blue.png",
  "cyan.png",
  "pink.png",
  "yellow.png"
};

std::unordered_map<std::string, std::function<void (Game& game, std::vector<std::string>& cmdArgs)>> cmdFunctions =
{
  {"msz", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_msz(game, cmdArgs);}},
  {"bct", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_bct(game, cmdArgs);}},
  {"tna", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_tna(game, cmdArgs);}},
  {"pnw", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pnw(game, cmdArgs);}},
  {"ppo", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_ppo(game, cmdArgs);}},
  {"plv", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_plv(game, cmdArgs);}},
  {"pin", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pin(game, cmdArgs);}},
  {"pex", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pex(game, cmdArgs);}},
  {"pbc", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pbc(game, cmdArgs);}},
  {"pic", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pic(game, cmdArgs);}},
  {"pie", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pie(game, cmdArgs);}},
  {"pfk", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pfk(game, cmdArgs);}},
  {"pdr", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pdr(game, cmdArgs);}},
  {"pgt", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pgt(game, cmdArgs);}},
  {"pdi", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_pdi(game, cmdArgs);}},
  {"enw", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_enw(game, cmdArgs);}},
  {"eht", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_eht(game, cmdArgs);}},
  {"ebo", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_ebo(game, cmdArgs);}},
  {"edi", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_edi(game, cmdArgs);}},
  {"sgt", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_sgt(game, cmdArgs);}},
  {"seg", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_seg(game, cmdArgs);}},
  {"smg", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_smg(game, cmdArgs);}},
  {"sbp", [&](Game& game, std::vector<std::string>& cmdArgs){Command::cmd_sbp(game, cmdArgs);}}
};

void                Command::setCmd(std::string const& str){
  std::stringstream ss(str);
  std::string       token;
  bool              first = true;

  while (ss >> token){
    if (first){
      this->_name = token;
      first = false;
    }
    else
      this->_args.push_back(token);
  }
}

/***********************************************/
void                Command::execCmds(Game& game, Command& command){
  if (cmdFunctions.find(command._name) != cmdFunctions.end())
    cmdFunctions.at(command._name)(game, command._args);
}

/***********************************************/
void                Command::createCell(Game& game, std::vector<std::string>& cmdArgs, size_t x, size_t y){
  // Asteroid
  auto mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/asteroid.obj", "");

  mesh->setScale(kirr::vector3df(leaderTray, leaderTray, leaderTray));
  scaleCell = mesh->getTransformedBoundingBox().getExtent() + 2;
  adjustmentX = (game.getMap().at(0).size() - 1) * scaleCell.X;
  adjustmentY = (game.getMap().size() - 1) * scaleCell.Z;
  game.getMeshs().push_back(mesh);
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX, 0, ((y * scaleCell.Z) * leaderTray) - adjustmentY));
  game.getMap().at(y).at(x) = Cell(Minerals(std::stoi(cmdArgs.at(2)), std::stoi(cmdArgs.at(3)), std::stoi(cmdArgs.at(4)), std::stoi(cmdArgs.at(5)), std::stoi(cmdArgs.at(6)), std::stoi(cmdArgs.at(7)), std::stoi(cmdArgs.at(8))), mesh);
  // Minerals
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/food.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX, 6, ((y * scaleCell.Z) * leaderTray) - adjustmentY));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("food").second = mesh;
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/linemate.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX + 2.5, 6.2, ((y * scaleCell.Z) * leaderTray) - adjustmentY + 1));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("linemate").second = mesh;
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/deraumere.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX - 5, 7, ((y * scaleCell.Z) * leaderTray) - adjustmentY - 3));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("deraumere").second = mesh;
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/sibur.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX + 1, 7.5, ((y * scaleCell.Z) * leaderTray) - adjustmentY + 2.5));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("sibur").second = mesh;
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/mendiane.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX + 1, 7, ((y * scaleCell.Z) * leaderTray) - adjustmentY - 3));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("mendiane").second = mesh;
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/phiras.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX - 4, 7.3, ((y * scaleCell.Z) * leaderTray) - adjustmentY + 3.5));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("phiras").second = mesh;
  mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/thystame.obj", "");
  mesh->setPosition(kirr::vector3df(((x * scaleCell.X) * leaderTray) - adjustmentX - 6, 7.5, ((y * scaleCell.Z) * leaderTray) - adjustmentY));
  game.getMeshs().push_back(mesh);
  game.getMap().at(y).at(x)._minerals._env.at("thystame").second = mesh;
}

/***********************************************/
void                Command::cmd_msz(Game& game, std::vector<std::string>& cmdArgs){
  game.getMap() = std::vector<std::vector<Cell>>(std::stoi(cmdArgs.at(1)), std::vector<Cell>(std::stoi(cmdArgs.at(0))));
}

void                Command::cmd_bct(Game& game, std::vector<std::string>& cmdArgs){
  size_t            x = std::stoi(cmdArgs.at(0));
  size_t            y = std::stoi(cmdArgs.at(1));

  if (!game.getMap().at(y).at(x)._mesh){
    Command::createCell(game, cmdArgs, x, y);
  }
  else
    game.getMap().at(y).at(x)._minerals.setMinerals(std::stoi(cmdArgs.at(2)), std::stoi(cmdArgs.at(3)), std::stoi(cmdArgs.at(4)), std::stoi(cmdArgs.at(5)), std::stoi(cmdArgs.at(6)), std::stoi(cmdArgs.at(7)), std::stoi(cmdArgs.at(8)));
  for (auto it = game.getMap().at(y).at(x)._minerals._env.begin(); it != game.getMap().at(y).at(x)._minerals._env.end(); it++){
    if (it->second.first <= 0)
      it->second.second->setVisible(false);
    else
      it->second.second->setVisible(true);
  }
}

void                Command::cmd_tna(Game& , std::vector<std::string>& ){

}

void                Command::cmd_pnw(Game& game, std::vector<std::string>& cmdArgs){
  static int        currentColor = 0;
  std::string       color;
  if (game.getTeamsColors().find(cmdArgs.at(5)) == game.getTeamsColors().end()){
    game.getTeamsColors()[cmdArgs.at(5)] = colors.at(currentColor);
    currentColor = (currentColor + 1) % colors.size();
  }
  auto mesh = game.getControl()->getKirrlicht().addModel(kirr::Pos<float>(), "./Assets/Objects/ship.obj", "./Assets/Textures/Colors/" + game.getTeamsColors().at(cmdArgs.at(5)));
  std::vector<std::string> args = {cmdArgs.at(0), cmdArgs.at(4)};

  mesh->setPosition({game.getMap().at(std::stoi(cmdArgs.at(2))).at(std::stoi(cmdArgs.at(1)))._mesh->getPosition().X - 2, 10, static_cast<float>(game.getMap().at(std::stoi(cmdArgs.at(2))).at(std::stoi(cmdArgs.at(1)))._mesh->getPosition().Z + 0.5)});
  mesh->setRotation({mesh->getRotation().X, (std::stof(cmdArgs.at(3)) + 1) * 90, mesh->getRotation().Z});
  game.getMeshs().push_back(mesh);
  game.getPlayers().push_back(Player(std::stoi(cmdArgs.at(0)), std::stoi(cmdArgs.at(1)), std::stoi(cmdArgs.at(2)), std::stoi(cmdArgs.at(3)), std::stoi(cmdArgs.at(4)), cmdArgs.at(5), mesh));
  Command::cmd_plv(game, args);
}

void                Command::cmd_ppo(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      game.getPlayers().at(i)._posX = std::stoi(cmdArgs.at(1));
      game.getPlayers().at(i)._posY = std::stoi(cmdArgs.at(2));
      game.getPlayers().at(i)._orientation = std::stoi(cmdArgs.at(3));
      game.getPlayers().at(i)._mesh->setRotation({0, (std::stof(cmdArgs.at(3)) + 1) * 90, 0});
      game.resetTransition(game.getPlayers().at(i)._mesh);
      game.getTransitions().push_back(Transition(game.getPlayers().at(i)._mesh, {game.getMap().at(std::stoi(cmdArgs.at(2))).at(std::stoi(cmdArgs.at(1)))._mesh->getPosition().X - 2, 10, static_cast<float>(game.getMap().at(std::stoi(cmdArgs.at(2))).at(std::stoi(cmdArgs.at(1)))._mesh->getPosition().Z + 0.5)}, {game.getPlayers().at(i)._mesh->getRotation().X, (std::stof(cmdArgs.at(3)) + 1) * 90, game.getPlayers().at(i)._mesh->getRotation().Z}, game.getTime()));
      return ;
    }
  }
}

void                Command::cmd_plv(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      game.getPlayers().at(i)._level = std::stoi(cmdArgs.at(1));
      float size = 0.8 + (0.2 * game.getPlayers().at(i)._level);
      game.getPlayers().at(i)._mesh->setScale({size, size, size});
      return ;
    }
  }
}

void                Command::cmd_pin(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      game.getPlayers().at(i)._posX = std::stoi(cmdArgs.at(1));
      game.getPlayers().at(i)._posY = std::stoi(cmdArgs.at(2));
      game.getPlayers().at(i)._inventory._env.at("food").first = std::stoi(cmdArgs.at(3));
      game.getPlayers().at(i)._inventory._env.at("linemate").first = std::stoi(cmdArgs.at(4));
      game.getPlayers().at(i)._inventory._env.at("deraumere").first = std::stoi(cmdArgs.at(5));
      game.getPlayers().at(i)._inventory._env.at("sibur").first = std::stoi(cmdArgs.at(6));
      game.getPlayers().at(i)._inventory._env.at("mendiane").first = std::stoi(cmdArgs.at(7));
      game.getPlayers().at(i)._inventory._env.at("phiras").first = std::stoi(cmdArgs.at(8));
      game.getPlayers().at(i)._inventory._env.at("thystame").first = std::stoi(cmdArgs.at(9));
      return ;
    }
  }
}

void                Command::cmd_pex(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      auto arrow = game.getControl()->getKirrlicht().getSceneManager()->addAnimatedMeshSceneNode(game.getControl()->getKirrlicht().getSceneManager()->addArrowMesh("Arrow"));
      arrow->setScale({10, 10, 10});
      switch (game.getPlayers().at(i)._orientation){
        case 1:
          arrow->setRotation({game.getPlayers().at(i)._mesh->getRotation().X - 90, game.getPlayers().at(i)._mesh->getRotation().Y, game.getPlayers().at(i)._mesh->getRotation().Z});
          break;
        case 2:
          arrow->setRotation({game.getPlayers().at(i)._mesh->getRotation().X, game.getPlayers().at(i)._mesh->getRotation().Y, game.getPlayers().at(i)._mesh->getRotation().Z - 90});
          break;
        case 3:
          arrow->setRotation({game.getPlayers().at(i)._mesh->getRotation().X - 90, game.getPlayers().at(i)._mesh->getRotation().Y, game.getPlayers().at(i)._mesh->getRotation().Z});
          break;
        case 4:
          arrow->setRotation({game.getPlayers().at(i)._mesh->getRotation().X, game.getPlayers().at(i)._mesh->getRotation().Y, game.getPlayers().at(i)._mesh->getRotation().Z + 90});
          break;
      }
      arrow->setPosition({game.getPlayers().at(i)._mesh->getPosition().X, 10, game.getPlayers().at(i)._mesh->getPosition().Z});
      game.getMeshs().push_back(arrow);
      game.getDots().push_back(arrow);
      return ;
    }
  }
}

void                Command::cmd_pbc(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      auto msg = game.getControl()->getKirrlicht().getSceneManager()->addTextSceneNode(game.getControl()->getFonts().at(18), std::wstring(cmdArgs.at(1).begin(), cmdArgs.at(1).end()).c_str());
      msg->setPosition({game.getPlayers().at(i)._mesh->getPosition().X, 10, game.getPlayers().at(i)._mesh->getPosition().Z});
      game.getMeshs().push_back(msg);
      game.getDots().push_back(msg);
      return ;
    }
  }
}

void                Command::cmd_pic(Game& game, std::vector<std::string>& cmdArgs){
  std::vector<float> pos = {game.getMap().at(std::stoi(cmdArgs.at(1))).at(std::stoi(cmdArgs.at(0)))._mesh->getPosition().X, game.getMap().at(std::stoi(cmdArgs.at(1))).at(std::stoi(cmdArgs.at(0)))._mesh->getPosition().Z};
  auto mesh = game.getControl()->getKirrlicht().addParticleSystem("./Assets/Textures/Sprites/smoke.bmp", kirr::vector3df(pos.at(0), -10, pos.at(1)), kirr::vector3df(0.1, 0.1, 0.1));

  if (mesh){
    game.getControl()->getKirrlicht().addParticleEmitter(mesh, 0.1, {0, 1, 0}, {30, 30, 30}, {30, 30, 0});
    game.getIncantationMesh().push_back(mesh);
    game.getIncantationPos().push_back({std::stoi(cmdArgs.at(0)), std::stoi(cmdArgs.at(1))});
  }
}

void                Command::cmd_pie(Game& game, std::vector<std::string>& cmdArgs){
  std::vector<int>  pos = {std::stoi(cmdArgs.at(0)), std::stoi(cmdArgs.at(1))};

  for (size_t i = 0; i < game.getIncantationPos().size(); i++){
    if (game.getIncantationPos().at(i).at(0) == pos.at(0) && game.getIncantationPos().at(i).at(1) == pos.at(1)){
      auto posTmp = game.getIncantationMesh().at(i)->getPosition();
      game.getIncantationMesh().at(i)->setEmitter(0);
      game.getIncantationMesh().erase(game.getIncantationMesh().begin() + i);
      game.getIncantationPos().erase(game.getIncantationPos().begin() + i);
      if (cmdArgs.at(2) == "0")
        return ;
      auto mesh = game.getControl()->getKirrlicht().addParticleSystem("./Assets/Textures/Sprites/fire.bmp", posTmp, kirr::vector3df(1, 1, 1));
      if (mesh){
        game.getControl()->getKirrlicht().addParticleEmitter(mesh, 0.1, {0, 1, 0}, {30, 30, 30}, {30, 30, 0});
        game.getIncantationMeshInProgress().push_back(mesh);
      }
      return ;
    }
  }
}

void                Command::cmd_pfk(Game& , std::vector<std::string>& ){
  // Pondre un oeuf
}

void                Command::cmd_pgt(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      game.resetTransition(game.getPlayers().at(i)._mesh);
      game.getTransitions().push_back(Transition(game.getPlayers().at(i)._mesh, {game.getPlayers().at(i)._mesh->getPosition().X, 9, game.getPlayers().at(i)._mesh->getPosition().Z}, {static_cast<double>(game.getPlayers().at(i)._mesh->getRotation().X), static_cast<double>(game.getPlayers().at(i)._mesh->getRotation().Y), static_cast<double>(game.getPlayers().at(i)._mesh->getRotation().Z)}, game.getTime()));
      return ;
    }
  }
}

void                Command::cmd_pdr(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      game.resetTransition(game.getPlayers().at(i)._mesh);
      game.getTransitions().push_back(Transition(game.getPlayers().at(i)._mesh, {game.getPlayers().at(i)._mesh->getPosition().X, 9, game.getPlayers().at(i)._mesh->getPosition().Z}, {static_cast<double>(game.getPlayers().at(i)._mesh->getRotation().X), static_cast<double>(game.getPlayers().at(i)._mesh->getRotation().Y), static_cast<double>(game.getPlayers().at(i)._mesh->getRotation().Z)}, game.getTime()));
      return ;
    }
  }
}

void                Command::cmd_pdi(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getPlayers().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getPlayers().at(i)._playerId){
      for (size_t j = 0; j < game.getTransitions().size(); j++){
        if (game.getTransitions().at(j)._mesh == game.getPlayers().at(i)._mesh){
          game.getTransitions().erase(game.getTransitions().begin() + j);
          break;
        }
      }
      game.delFromMeshs(game.getPlayers().at(i)._mesh);
      game.getPlayers().erase(game.getPlayers().begin() + i);
      return ;
    }
  }
}

void                Command::cmd_enw(Game& game, std::vector<std::string>& cmdArgs){
  auto              mesh = game.getControl()->getKirrlicht().getSceneManager()->addSphereSceneNode(2, 16, nullptr, -1, {1, 1, 1});

  mesh->setPosition({game.getMap().at(std::stoi(cmdArgs.at(3))).at(std::stoi(cmdArgs.at(2)))._mesh->getPosition().X - 2, 10, static_cast<float>(game.getMap().at(std::stoi(cmdArgs.at(3))).at(std::stoi(cmdArgs.at(2)))._mesh->getPosition().Z + 0.5)});
  game.getMeshs().push_back(mesh);
  game.getEggs().push_back(Eggs(std::stoi(cmdArgs.at(0)), std::stoi(cmdArgs.at(1)), std::stoi(cmdArgs.at(2)), std::stoi(cmdArgs.at(3)), mesh));
}

void                Command::cmd_eht(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getEggs().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getEggs().at(i)._eggsId){
      game.delFromMeshs(game.getEggs().at(i)._mesh);
      game.getEggs().erase(game.getEggs().begin() + i);
      return ;
    }
  }
}

void                Command::cmd_ebo(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getEggs().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getEggs().at(i)._eggsId){
      game.delFromMeshs(game.getEggs().at(i)._mesh);
      game.getEggs().erase(game.getEggs().begin() + i);
      return ;
    }
  }
}

void                Command::cmd_edi(Game& game, std::vector<std::string>& cmdArgs){
  for (size_t i = 0; i < game.getEggs().size(); i++){
    if (std::stoi(cmdArgs.at(0)) == game.getEggs().at(i)._eggsId){
      game.delFromMeshs(game.getEggs().at(i)._mesh);
      game.getEggs().erase(game.getEggs().begin() + i);
      return ;
    }
  }
}

void                Command::cmd_sgt(Game& game, std::vector<std::string>& cmdArgs){
  int               frequence = std::stoi(cmdArgs.at(0));

  if (game.getTime() == -1)
    game.getScrollFrequence()->setPos(frequence);
  game.setTime(frequence);
  game.getFrequenceText()->setText(std::to_wstring(frequence).c_str());
}

void                Command::cmd_seg(Game& game, std::vector<std::string>& cmdArgs){
  std::string       msg = cmdArgs.at(0) + " WIN !";
  std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
  game.getControl()->getKirrlicht().displayString(msg, kirr::Pos<float>(-adjustmentX, 40, 0), kirr::Pos<float>(0, 180, 0), kirr::Pos<float>(0.2, 0.2, 0.2), game.getMeshs(), "./Assets/Textures/Colors/blue.png");
  game.getCameraAngle().x = -1.56;
  game.getCameraAngle().z = -1.56;
  game.endGame();
}

void                Command::cmd_smg(Game& game, std::vector<std::string>& cmdArgs){
  game.getTableServer()->setCellText(0, 0, std::wstring(cmdArgs.at(0).begin(), cmdArgs.at(0).end()).c_str());
}

void                Command::cmd_sbp(Game& , std::vector<std::string>& ){
  std::cerr << "Bad parameters" << std::endl;
}
