//
//File: Action_Factory.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 10:37 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_STATE_FACTORY_H__
#define _SIA_THE_SPACE_STRATEGY_STATE_FACTORY_H__

#include "Action.h"

namespace Actions
{
  class Action::Factory {
  public:
    static ActionPtr createAction(ActionDataPtr pActionData, Properties::PropertyContainer& properties);

  };
}

#endif //_SIA_THE_SPACE_STRATEGY_STATE_FACTORY_H__