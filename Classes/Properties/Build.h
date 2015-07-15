//
//File:  Build.h
//Description: Property respondent for Build.
//Author: Ivlev Alexander. Stef
//Created: 25/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_BUILD_H__
#define _SIA_THE_SPACE_STRATEGY_BUILD_H__

#include "IProperty.h"

namespace Properties
{
  class Build: public IProperty {
  public:
    DEFINE_PROPERTY(Build);

    static IPropertyPtr create() {
      return IPropertyPtr(new Build());
    }

  private:
    Build() { 
    }
  };

  typedef std::shared_ptr<Build> BuildPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_BUILD_H__
