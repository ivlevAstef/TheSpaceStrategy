/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_OBJECT_H__
#define _OBJECTS_OBJECT_H__

#include <map>
#include <memory>
#include "Components/Component.h"

namespace Objects
{
  class Object;
  typedef std::shared_ptr<Object> ObjectPtr;

  class Object {
  public:
    template<typename ComponentType>
    ComponentType* getComponent() {
      return static_cast<ComponentType*>(getComponent(ComponentType::sComponentName()));
    }

    Components::Component* getComponent(const char* name);

    virtual ~Object();
    virtual void update() = 0;

  protected:
    void addComponent(Components::Component* component);
    void eraseComponent(Components::Component* component);

  private:
    std::map<std::string, Components::Component*> m_components;
  };

};

#endif // _OBJECTS_OBJECT_H__
