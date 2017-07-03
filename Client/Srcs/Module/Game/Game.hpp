/*
** Game.hpp for PSU_2016_zappy in /Users/metge_q/rendu/PSU_2016_zappy/Client/Srcs/Module/Game
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Thu Jun 22 18:09:23 2017 Quentin Metge
** Last update Sun Jul 02 16:04:32 2017 Quentin Metge
*/

#ifndef GAME_HPP_
# define GAME_HPP_

#include <thread>
#include <utility>
#include <string>
#include <queue>
#include <map>
#include "Command.hpp"
#include "AModule.hpp"

namespace zpyclient{

  enum class TableCol : int{
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6,
    TEAM = 7,
    ID = 8,
    POS = 9,
    DIR = 10,
    LVL = 11
  };

  struct Minerals{
    Minerals()
      : _env({{"food", std::make_pair(0, nullptr)}, {"linemate", std::make_pair(0, nullptr)}, {"deraumere", std::make_pair(0, nullptr)}, {"sibur", std::make_pair(0, nullptr)}, {"mendiane", std::make_pair(0, nullptr)}, {"phiras", std::make_pair(0, nullptr)}, {"thystame", std::make_pair(0, nullptr)}}){}
    Minerals(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
      : _env({{"food", std::make_pair(food, nullptr)}, {"linemate", std::make_pair(linemate, nullptr)}, {"deraumere", std::make_pair(deraumere, nullptr)}, {"sibur", std::make_pair(sibur, nullptr)}, {"mendiane", std::make_pair(mendiane, nullptr)}, {"phiras", std::make_pair(phiras, nullptr)}, {"thystame", std::make_pair(thystame, nullptr)}}){}
    virtual ~Minerals(){}

    void                      setMinerals(const int food, const int linemate, const int deraumere, const int sibur, const int mendiane, const int phiras, const int thystame){
      this->_env.at("food").first = food;
      this->_env.at("linemate").first = linemate;
      this->_env.at("deraumere").first = deraumere;
      this->_env.at("sibur").first = sibur;
      this->_env.at("mendiane").first = mendiane;
      this->_env.at("phiras").first = phiras;
      this->_env.at("thystame").first = thystame;
    }

    std::map<std::string, std::pair<int, kirr::Scene::ISceneNode*>> _env;
    kirr::Scene::ISceneNode*  _mesh = nullptr;
  };

  struct Cell{
    Cell(){}
    Cell(Minerals minerals, kirr::Scene::ISceneNode* mesh)
      : _minerals(minerals), _mesh(mesh){}
    virtual ~Cell(){}

    Minerals                  _minerals;
    kirr::Scene::ISceneNode*  _mesh = nullptr;
  };

  struct Player{
    Player(){}
    Player(int playerId, int X, int Y, int O, int L, std::string const& N, kirr::Scene::ISceneNode* mesh)
      : _playerId(playerId), _posX(X), _posY(Y), _orientation(O), _level(L), _team(N), _mesh(mesh){}
    virtual ~Player(){}

    int                       _playerId = -1;
    int                       _posX = 0;
    int                       _posY = 0;
    int                       _orientation = 0;
    int                       _level = 1;
    Minerals                  _inventory;
    std::string               _team;
    kirr::Scene::ISceneNode*  _mesh = nullptr;

  };

  struct Eggs{
    Eggs(){}
    Eggs(int eggsId, int playerId, int posX, int posY, kirr::Scene::ISceneNode* mesh)
      : _eggsId(eggsId), _playerId(playerId), _posX(posX), _posY(posY), _mesh(mesh){}
    virtual ~Eggs(){}

    int                       _eggsId = 0;
    int                       _playerId = 0;
    int                       _posX = 0;
    int                       _posY = 0;
    kirr::Scene::ISceneNode*  _mesh = nullptr;
  };

  struct Transition{
  public:
    Transition(){}
    Transition(kirr::Scene::ISceneNode* mesh, std::vector<double> dest, std::vector<double> destRotation, int timer)
      : _dest(dest), _destRotation(destRotation), _mesh(mesh){
        double step = 2 * (100 / timer);
        if (timer > 50)
          this->_without = true;
        if (!double_equals(dest.at(0), mesh->getPosition().X, 1) || !double_equals(dest.at(1), mesh->getPosition().Y, 1) || !double_equals(dest.at(2), mesh->getPosition().Z, 1)){
          this->_movement = {static_cast<double>((dest.at(0) - mesh->getPosition().X) / step), static_cast<double>((dest.at(1) - mesh->getPosition().Y) / step), static_cast<double>((dest.at(2) - mesh->getPosition().Z) / step)};
          this->_depl = true;
        }
      }
    virtual ~Transition(){}

    static bool               double_equals(double a, double b, double epsilon = 0.1){return std::abs(a - b) < epsilon;}


    bool                      _without = false;
    bool                      _depl = false;
    std::vector<double>       _movement;
    std::vector<double>       _dest;
    std::vector<double>       _destRotation;
    kirr::Scene::ISceneNode*  _mesh = nullptr;
  };

  class Game : public AModule{
  public:
    Game(ModuleLoader& ml, std::shared_ptr<Control> control);
    virtual ~Game();

  public:
    bool              connect();

  public:
    virtual State     load();
    State             loadAssets();
    virtual bool      clear();
    virtual State     mainLoop();

  public:
    void              readingLoop();
    bool              isCell(kirr::Scene::ISceneNode* mesh);
    void              resetTransition(kirr::Scene::ISceneNode* mesh);

  public:
    void              endGame(){this->_endGame = true;}
    void              setTime(int const timer){this->_time = timer;}
    void              setState(State const& state){this->_state = state;}

  public:
    void              updateCamera(kirr::GlobalEvent& events);
    void              updateTablePlayers();
    void              updateTableResources(kirr::Scene::ISceneNode* mesh);
    void              updateTransitions();
    void              updateIncantation();
    void              updateFrequence();
    void              updateBroadcast();
    void              updateEndGame();

  public:
    std::vector<std::vector<Cell>>& getMap(){return this->_map;}
    std::vector<Player>&            getPlayers(){return this->_players;}
    std::vector<Eggs>&              getEggs(){return this->_eggs;}
    int                             getTime() const{return this->_time;}
    std::vector<std::vector<int>>&  getIncantationPos(){return this->_incantationPos;}
    std::vector<Transition>&        getTransitions(){return this->_transitions;}
    kirr::Gui::IGUIScrollBar*       getScrollFrequence() const{return this->_scrollFrequence;}
    kirr::klang::ISound*            getMusic() const{return this->_music;}
    kirr::Gui::IGUITable*           getTableServer() const{return this->_tableServer;}
    kirr::Gui::IGUIStaticText*      getFrequenceText() const{return this->_frequenceText;}
    kirr::Pos<float>&               getCameraAngle();
    std::unordered_map<std::string, std::string>&         getTeamsColors(){return this->_teamsColors;}
    std::vector<kirr::Scene::IParticleSystemSceneNode*>&  getIncantationMesh(){return this->_incantationMesh;}
    std::vector<kirr::Scene::IParticleSystemSceneNode*>&  getIncantationMeshInProgress(){return this->_incantationMeshInProgress;}
    std::vector<kirr::Scene::ISceneNode*>&                getDots(){return this->_dots;}

  private:
    std::vector<std::vector<Cell>>      _map;
    std::vector<Player>                 _players;
    std::vector<Eggs>                   _eggs;
    int                                 _time;

  private:
    std::vector<kirr::Scene::IParticleSystemSceneNode*> _incantationMeshInProgress;
    std::vector<std::vector<int>>                       _incantationPos;
    std::vector<kirr::Scene::IParticleSystemSceneNode*> _incantationMesh;
    std::unordered_map<std::string, std::string>        _teamsColors;
    std::vector<Transition>                             _transitions;
    std::vector<kirr::Scene::ISceneNode*>               _dots;
    bool                                                _endGame;

  private:
    kirr::Scene::ISceneNode*            _skybox = nullptr;
    kirr::Gui::IGUIWindow*              _serverWin = nullptr;
    kirr::Gui::IGUIWindow*              _playersWin = nullptr;
    kirr::Gui::IGUIWindow*              _resourcesWin = nullptr;
    kirr::Gui::IGUIWindow*              _cmdWin = nullptr;
    kirr::Gui::IGUITable*               _tablePlayers = nullptr;
    kirr::Gui::IGUITable*               _tableRessources = nullptr;
    kirr::Gui::IGUITable*               _tableCmd = nullptr;
    kirr::Gui::IGUITable*               _tableServer = nullptr;
    kirr::klang::ISound*                _music = nullptr;
    kirr::Gui::IGUIScrollBar*           _scrollFrequence = nullptr;
    kirr::Gui::IGUIStaticText*          _frequenceText;
  };
}

#endif
