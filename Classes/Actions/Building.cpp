//
//File: Building.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 10:23 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#include "Building.h"

#include "Properties/EnergyGenerator.h"
#include "Properties/TransmitterEnergy.h"

#include "SIALogger.h"
SIASetModuleName(Actions);

using namespace Actions;
using namespace Properties;

Action::State Building::sComplete = "complete";

Building::Building(Properties::PropertyContainer& properties, const Common::Features& setting) : Action(properties) {
  SIAFatalAssert(setting.is("time"));

  m_buildingTime = setting["time"];
  begin();
}

ActionDataPtr Building::createActionData(double buildingTime) {
  Common::Features setting;

  setting["time"] = buildingTime;

  return ActionDataPtr(new ActionData(actionName(), setting));
}


Action::State Building::update(double dt) {
  if (checkDeath()) {
    return sDeath;
  }

  m_currentTime += dt;

  if (m_currentTime >= m_buildingTime) {
    m_currentTime = m_buildingTime;
    end();
    return sComplete;
  }

  return sExecuting;
}

void Building::begin() {
  properties().deactivate<EnergyGenerator>();
  properties().deactivate<TransmitterEnergy>();
}

void Building::end() {
  properties().activate<EnergyGenerator>();
  properties().activate<TransmitterEnergy>();
}