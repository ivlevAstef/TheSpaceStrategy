/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_SCENE_LAYERS_H__
#define _OBJECTS_SCENE_LAYERS_H__

#include "Object.h"

namespace Objects
{
  class SceneLayer: public Object {
  public:
    static std::shared_ptr<SceneLayer> create();

    bool addObject(ObjectPtr pObject);
    void eraseObject(ObjectPtr pObject);

    Scene();
    ~Scene();

    virtual void update(SceneInterfacePtr pScene) override;

  private:
    void touchBegan(Common::GameTouchData data);

  private:
    Components::View::GameLayer* m_cacheGameLayer;
    Components::Data::Area* m_cacheArea;

    std::vector<ObjectPtr> m_objects;
  };
};

#endif // _OBJECTS_SCENE_LAYERS_H__
