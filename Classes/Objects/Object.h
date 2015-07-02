/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_OBJECT_H__
#define _SIA_THE_SPACE_STRATEGY_OBJECT_H__

#include <string>
#include <memory>
#include "SceneInterface.h"

#include "Models/Entity.h"
#include "Views/GameView.h"

namespace Objects
{
  class Object;
  typedef std::shared_ptr<Object> ObjectPtr;

  class Object {
  public:
    static ObjectPtr create(std::string objName, double x, double y) {
      return ObjectPtr(new Object(objName, x, y));
    }

    Object(std::string objName, double x, double y);

    virtual void update(SceneInterfacePtr pScene);

    virtual ~Object();

    Views::GameView* view() const { return m_pView; }
    Models::EntityPtr entity() const { return m_pEntity; }

  protected:
    Models::EntityPtr m_pEntity;
    Views::GameView* m_pView;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_OBJECT_H__
