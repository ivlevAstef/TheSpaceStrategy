//
//File: Inaction.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:46 14/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_INACTION_H__
#define _SIA_THE_SPACE_STRATEGY_INACTION_H__

#include "State.h"
#include "Common/Features.h"

namespace States
{
  class Inaction: public State {
  public:
    Inaction(Properties::PropertyContainer& properties) : State(properties) {

    }

    virtual StateStatus update(double dt) override {
      if (checkDeath) {
        return sDeath;
      }

      return sExecuting;
    }
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_INACTION_H__