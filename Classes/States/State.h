//
//File: State.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:47 14/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//


#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_STATE_H__
#define _SIA_THE_SPACE_STRATEGY_STATE_H__

#include "Properties/PropertyContainer.h"
#include "Common/Features.h"
#include <memory>

namespace States
{
  class State;
  typedef std::shared_ptr<State> StatePtr;

  class State {
  public:
    class Factory;
    friend class Factory;

    typedef std::string StateStatus;//e.g. "Executing", "Death"

    static StateStatus sExecuting;
    static StateStatus sDeath;

  public:

    State(Properties::PropertyContainer& properties);
    
    virtual StateStatus update(double dt) = 0;

  protected:

    inline Properties::PropertyContainer& properties() const {
      return m_properties;
    }

    bool checkDeath();

  private:

    Properties::PropertyContainer& m_properties;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_STATE_H__
