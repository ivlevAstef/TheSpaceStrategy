/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ICOMPONENT_H__
#define _SIA_THE_SPACE_STRATEGY_ICOMPONENT_H__

#include <memory>

namespace Components
{
  class IComponent {
  public:
    virtual const char* componentName() const = 0;
  };

  typedef std::shared_ptr<IComponent> IComponentPtr;

#define DEFINE_COMPONENT(CLASS) \
  static const char* sComponentName() { return #CLASS; } \
  virtual const char* componentName() const override { return #CLASS; }

};

#endif // _SIA_THE_SPACE_STRATEGY_ICOMPONENT_H__
