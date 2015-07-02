//
//File:  Build.h
//Description: Component respondent for Build.
//Author: Ivlev Alexander. Stef
//Created: 25/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_BUILD_H__
#define _SIA_THE_SPACE_STRATEGY_BUILD_H__

#include "IComponent.h"

namespace Components
{
  class Build: public IComponent {
  public:
    DEFINE_COMPONENT(Build);

    static IComponentPtr create() {
      return IComponentPtr(new Build());
    }

  private:
    Build() { 
    }
  };

  typedef std::shared_ptr<Build> BuildPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_BUILD_H__
