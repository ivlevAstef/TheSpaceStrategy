/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_SCENE_H__
#define _SIA_THE_SPACE_STRATEGY_SCENE_H__

#include "Object.h"
#include "Views/GameLayer.h"
#include "Views/InterfaceView/BuildButtonLayer.h"
#include "Models/ModelController.h"
#include "SceneInterface.h"
#include <vector>

namespace Objects
{
  class Scene;
  typedef std::shared_ptr<Scene> ScenePtr;

  class Scene: public SceneInterface {
  public:
    static ScenePtr create(size_t width, size_t height);
    
    inline Views::GameLayer* getGameLayer() const {
      return m_pGameLayer;
    }

    void addObject(ObjectPtr pObject);
    void eraseObject(ObjectPtr pObject);

    Scene(size_t width, size_t height);
    Scene(const Scene&) = delete;
    ~Scene();

    void draw(SceneInterfacePtr pScene, double dt);

    virtual const Common::ViewMath& viewMath() const override {
      return m_viewMath;
    }

  private:
    void touchBegan(cocos2d::Vec2 touch);
    void touchMoved(cocos2d::Vec2 touch);
    void touchEnded(cocos2d::Vec2 touch);
    void move(cocos2d::Vec2 moveDt);
    void erase(cocos2d::Vec2 erasePos);

  private:
    Views::GameLayer* m_pGameLayer;
    Views::BuildButtonLayer* m_pButtonLayer;
    Models::ModelController m_modelController;

    std::vector<ObjectPtr> m_pObjects;

    Common::ViewMath m_viewMath;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_SCENE_H__
