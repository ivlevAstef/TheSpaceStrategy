/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_SCENE_H__
#define _OBJECTS_SCENE_H__

#include "Object.h"
#include "Components/View/GameLayer.h"
#include <memory>

namespace Objects
{
  class Scene: public Object {
  public:
    static std::shared_ptr<Scene> create();
    
    inline Components::View::GameLayer* getGameLayer() const {
      return m_cacheGameLayer;
    }

    void addObject(ObjectPtr pObject);

    Scene();

  private:
    Components::View::GameLayer* m_cacheGameLayer;
  };
};

#endif // _OBJECTS_SCENE_H__
