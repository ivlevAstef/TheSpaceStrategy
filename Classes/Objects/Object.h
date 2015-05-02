/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _OBJECTS_OBJECT_H__
#define _OBJECTS_OBJECT_H__

#include <map>
#include <memory>
#include "Components/Component.h"
#include "Components/Features.h"

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

  protected:
    void addComponent(Components::Component* component);

    std::map<std::string, Components::Component*> m_components;

  protected:
    Components::Features m_features;
  };

};

#endif // _OBJECTS_OBJECT_H__
