//
//File: Building.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 10:23 15/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#include "Building.h"
#include "SIALogger.h"
SIASetModuleName(Actions);

using namespace Actions;

Action::State Building::sComplete = "complete";

Building::Building(Properties::PropertyContainer& properties, const Common::Features& setting) : Action(properties) {
  SIAFatalAssert(setting.is("time"));

  m_buildingTime = setting["time"];
}

Common::Features Building::createSetting(double buildingTime) {
  Common::Features res;

  res["time"] = buildingTime;

  return res;
}


Action::State Building::update(double dt) {
  if (checkDeath()) {
    return sDeath;
  }

  m_currentTime += dt;

  if (m_currentTime >= m_buildingTime) {
    m_currentTime = m_buildingTime;
    return sComplete;
  }

  return sExecuting;
}
