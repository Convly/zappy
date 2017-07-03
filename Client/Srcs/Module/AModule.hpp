//
// AModule.hpp for AModule in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Modules/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:23:13 2017 jsx
// Last update Thu May 11 13:44:24 2017 JSX
//

#ifndef AMODULE_INDIE_STUDIO_HPP_
#define AMODULE_INDIE_STUDIO_HPP_

#include "IModule.hpp"

namespace zpyclient{
  class AModule : public IModule{
  public:
    AModule(ModuleLoader& ml, std::shared_ptr<Control> control) : _moduleLoader(ml), _control(control){}
    virtual ~AModule(){}

  public:
    virtual State     load() = 0;
    virtual bool      clear() = 0;
    virtual State     mainLoop() = 0;

  public:
    virtual std::shared_ptr<Control>  getControl(){return this->_control;}
    virtual ModuleLoader&             getModuleLoader() const{return this->_moduleLoader;}
    virtual std::vector<kirr::Scene::ISceneNode*>& getMeshs(){return this->_meshs;}
    virtual kirr::Camera*             getCamera(){return this->_camera;}

  public:
    bool              tryEscape(bool const key){
      static bool     prevKey = false;
      bool            pressed;

      pressed = !key && prevKey;
      prevKey = key;
      return pressed;
    }
    void              delFromMeshs(kirr::Scene::ISceneNode* mesh){
      for (size_t i = 0; i < this->_meshs.size(); i++){
        if (mesh == this->_meshs.at(i)){
          this->_control->getKirrlicht().getSceneManager()->addToDeletionQueue(mesh);
          this->_meshs.erase(this->_meshs.begin() + i);
          return ;
        }
      }
    }

  protected:
    State                     _state = State::CONTINUE;
    ModuleLoader&             _moduleLoader;
    std::shared_ptr<Control>  _control;
    kirr::Camera*             _camera;
    std::vector<kirr::Scene::ISceneNode*> _meshs;
  };
} /* module */

#endif /* end of include guard: AMODULE_INDIE_STUDIO_HPP_ */
