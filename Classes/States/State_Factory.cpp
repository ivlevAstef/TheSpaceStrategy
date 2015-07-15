#include "State_Factory.h"

#include "Building.h"
#include "Inaction.h"

#include "SIALogger.h"
SIASetModuleName(States);

using namespace States;

StatePtr State::Factory::createStateByName(std::string name, Properties::PropertyContainer& properties, const Common::Features& setting) {
  if ("building" == name) {
    SIADebug("Create state for name:%s.", name.c_str());
    return StatePtr(new Building(properties, setting));
  }

  if ("inaction" == name) {
    SIADebug("Create state for name:%s.", name.c_str());
    return StatePtr(new Inaction(properties));
  }

  SIAError("Can't find state with name:%s.", name.c_str());
  return StatePtr(nullptr);
}
