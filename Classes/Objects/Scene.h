/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_SCENE_H__
#define _OBJECTS_SCENE_H__

#include "Object.h"
#include "Components/View/GameLayer.h"
#include "Components/Data/Area.h"
#include <memory>
#include <vector>

namespace Objects
{
  class Scene;
  typedef std::shared_ptr<Scene> ScenePtr;

  class Scene: public Object {
  public:
    static ScenePtr create();
    
    inline Components::View::GameLayer* getGameLayer() const {
      return m_cacheGameLayer;
    }

    bool addObject(ObjectPtr pObject);

    Scene();

    virtual void update() override;

  private:
    void clickCell(size_t x, size_t y, cocos2d::Vec2 pos);

  private:
    Components::View::GameLayer* m_cacheGameLayer;
    Components::Data::Area* m_cacheArea;

    std::vector<ObjectPtr> m_objects;
  };
};

#endif // _OBJECTS_SCENE_H__
