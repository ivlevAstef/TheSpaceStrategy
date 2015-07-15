#include "Building.h"
#include "SIALogger.h"
SIASetModuleName(States);

using namespace States;

State::StateStatus Building::sComplete = "complete";

Building::Building(Properties::PropertyContainer& properties, const Common::Features& setting) : State(properties) {
  SIAFatalAssert(setting.is("time"));

  m_buildingTime = setting["time"];
}

Common::Features Building::createSetting(double buildingTime) {
  Common::Features res;

  res["time"] = buildingTime;

  return res;
}


State::StateStatus Building::update(double dt) {
  if (checkDeath) {
    return sDeath;
  }

  m_currentTime += dt;

  if (m_currentTime >= m_buildingTime) {
    m_currentTime = m_buildingTime;
    return sComplete;
  }

  return sExecuting;
}
