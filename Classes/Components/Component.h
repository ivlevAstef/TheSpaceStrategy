/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_COMPONENT_H__
#define _COMPONENTS_COMPONENT_H__

namespace Components
{
  class Component {
  public:
    virtual const char* componentName() const = 0;
  };

#define DEFINE_COMPONENT(CLASS) \
  static const char* sComponentName() { return #CLASS; } \
  virtual const char* componentName() const override { return #CLASS; }

};

#endif // _COMPONENTS_COMPONENT_H__
