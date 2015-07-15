//
//File: Action.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:47 14/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ACTION_H__
#define _SIA_THE_SPACE_STRATEGY_ACTION_H__

#include "Properties/PropertyContainer.h"
#include "Common/Features.h"
#include <memory>

namespace Actions
{
  class Action;
  typedef std::shared_ptr<Action> ActionPtr;

  class Action {
  public:
    class Factory;
    friend class Factory;

    typedef std::string State;//e.g. "Executing", "Death"

    static State sExecuting;
    static State sDeath;

  public:

    Action(Properties::PropertyContainer& properties);
    
    virtual State update(double dt) = 0;

  protected:

    inline Properties::PropertyContainer& properties() const {
      return m_properties;
    }

    bool checkDeath();

  private:

    Properties::PropertyContainer& m_properties;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_ACTION_H__
