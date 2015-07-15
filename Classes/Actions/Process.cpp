//
//File: Process.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:56 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#include "Process.h"
#include "Action_Factory.h"
#include "SIALogger.h"

SIASetModuleName(Actions);

using namespace Actions;

Process::Process(Properties::PropertyContainer& properties) : m_properties(properties) {

}

void Process::update(double dt) {
  if (0 == m_joins.size()) {
    return;
  }

  SIACheckRet(nullptr == m_pCurrentActionData.get());
  
  if (!m_pCurrentAction.get()) {
    m_pCurrentAction = Action::Factory::createAction(m_pCurrentActionData, m_properties);
    SIAAssert(m_pCurrentAction.get());
  }

  Action::State newState = m_pCurrentAction->update(dt);

  ActionDataPtr newActionData = actionDataFor(newState);

  if (nullptr != newActionData) {
    m_pCurrentActionData = newActionData;
    m_pCurrentAction = ActionPtr(nullptr);
  }
}

bool Process::setCurrentAction(ActionDataPtr pActionData) {
  SIACheckRetValue(m_joins.find(pActionData) == m_joins.end(), false);

  m_pCurrentActionData = pActionData;

  return true;
}

bool Process::addJoin(ActionDataPtr pActionData, Action::State state, ActionDataPtr pToActionData) {
  ActionStateMap& stateMap = m_joins[pActionData];

  SIACheckRetValue(stateMap.find(state) != stateMap.end(), false);
  
  stateMap[state] = pToActionData;

  return true;
}

ActionDataPtr Process::actionDataFor(Action::State state) {
  auto foundJoins = m_joins.find(m_pCurrentActionData);
  
  if (foundJoins == m_joins.end()) {
    return ActionDataPtr(nullptr);
  }

  auto foundActionData = foundJoins->second.find(state);

  if (foundActionData == foundJoins->second.end()) {
    return ActionDataPtr(nullptr);
  }

  return foundActionData->second;
}