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

    Components::Component* getComponent(const char* name) {
      auto findRes = m_components.find(name);
      if (findRes != m_components.end()) {
        return findRes->second;
      }
      return nullptr;
    }

  protected:
    void addComponent(Components::Component* component) {
      if (nullptr != component) {
        m_components[component->componentName()] = component;
      }
    }

    std::map<std::string, Components::Component*> m_components;
  };

};

#endif // _OBJECTS_OBJECT_H__
