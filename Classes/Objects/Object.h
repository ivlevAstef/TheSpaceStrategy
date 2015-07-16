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
    static ObjectPtr create(std::string objName, Common::EntityPos pos) {
      return ObjectPtr(new Object(objName, pos));
    }

    Object(std::string objName, Common::EntityPos pos);
    Object(const Object&) = delete;

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
