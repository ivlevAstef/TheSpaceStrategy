//
//File: Action_Factory.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 10:42 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#include "Action_Factory.h"

#include "Building.h"
#include "Inaction.h"

#include "SIALogger.h"
SIASetModuleName(Actions);

using namespace Actions;

ActionPtr Action::Factory::createAction(ActionDataPtr pActionData, Properties::PropertyContainer& properties) {
  SIAFatalAssert(pActionData.get());

  if (Building::actionName() == pActionData->name()) {
    SIADebug("Create state for name:%s.", pActionData->name().c_str());
    return ActionPtr(new Building(properties, pActionData->setting()));
  }

  if (Inaction::actionName() == pActionData->name()) {
    SIADebug("Create state for name:%s.", pActionData->name().c_str());
    return ActionPtr(new Inaction(properties));
  }

  SIAError("Can't find state with name:%s.", pActionData->name().c_str());
  return ActionPtr(nullptr);
}
