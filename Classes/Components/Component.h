/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_COMPONENT_H__
#define _COMPONENTS_COMPONENT_H__

#include "base/CCRef.h"

namespace Components
{
  class Component {
  public:
    virtual const char* componentName() const = 0;

    virtual void cRetain() = 0;
    virtual void cRelease() = 0;
  };

  //class ComponentRef;


#define DEFINE_COMPONENT(CLASS) \
  static const char* sComponentName() { return #CLASS; } \
  virtual const char* componentName() const override { return #CLASS; }

#define DEFINE_COCOS2DX_COMPONENT \
  private: \
      virtual void cRetain() final { \
        this->retain(); \
      } \
      virtual void cRelease() final { \
        this->release(); \
      } \
  public:



  class ComponentRef: public cocos2d::Ref, public Component {
    DEFINE_COCOS2DX_COMPONENT
  };



#define COMPONENT_ALLOC(CLASS) CLASS* component = new (std::nothrow)CLASS
#define COMPONENT_INIT(CLASS) \
  if (component) { \
    component->autorelease(); \
    return component; \
    } \
  SIA_LOG_ERR("Can't allocation component - "#CLASS); \
  CC_SAFE_DELETE(component); \
  return nullptr

};

#endif // _COMPONENTS_COMPONENT_H__
