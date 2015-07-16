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

    Process(Properties::PropertyContainer& properties);
    Process(const Process&) = delete;
    Process& operator=(const Process&) = delete;

    void update(double dt);

    bool setCurrentAction(ActionDataPtr pActionData);

    bool addJoin(ActionDataPtr pActionData, Action::State state, ActionDataPtr pToActionData);

  private:
    ActionDataPtr actionDataFor(Action::State state);


  private:
    typedef std::map<Action::State, ActionDataPtr> ActionStateMap;

    std::map<ActionDataPtr, ActionStateMap> m_joins;
    ActionDataPtr m_pCurrentActionData;

    ActionPtr m_pCurrentAction;

    Properties::PropertyContainer& m_properties;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_PROCESS_H__