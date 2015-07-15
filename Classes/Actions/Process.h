//
//File: Process.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 19:37 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_PROCESS_H__
#define _SIA_THE_SPACE_STRATEGY_PROCESS_H__

#include "Action.h"

namespace Actions
{
  class Process {
  public:

    Process(Properties::PropertyContainer& properties) : m_properties(properties) {

    }

    void update(double dt) {
    }

  private:

    Properties::PropertyContainer& m_properties;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_PROCESS_H__