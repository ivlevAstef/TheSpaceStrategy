#include "Entity_Factory.h"

#include "SIALogger.h"
#include "Common/FeatureNames.h"

#include "Properties/EnergyGenerator.h"
#include "Properties/TransmitterEnergy.h"
#include "Properties/Build.h"

#include "Actions/Building.h"
#include "Actions/Inaction.h"

SIASetModuleName(Model);

using namespace Models;
using namespace Actions;

EntityPtr Entity::Factory::createBuildByName(std::string name) {
  auto entity = EntityPtr(new Models::Entity());
  SIAAssert(entity.get());

  if ("MainBase" == name && initMainBase(*entity.get())) {
    return entity;
  }

  if ("Pylon" == name && initPylon(*entity.get())) {
    return entity;
  }

  if ("MinerMinerals" == name && initMinerMinerals(*entity.get())) {
    return entity;
  }

  if ("Minerals" == name && initMinerals(*entity.get())) {
    return entity;
  }
 
  SIAError("Can't find build with name:%s.", name.c_str());
  return EntityPtr(nullptr);
}

bool Entity::Factory::initMainBase(Entity& entity) {
  SIADebug("Init main base.");
  Common::Features& features = *entity.m_pFeatures.get();

  features[Common::FeatureNames::maxHP] = 100;
  features[Common::FeatureNames::HP] = 100;
  features[Common::FeatureNames::physic] = true;

  entity.prop() += Properties::Build::create();
  entity.prop() += Properties::EnergyGenerator::create(25.0);

  ActionDataPtr building = Building::createActionData(5.0);
  ActionDataPtr inaction = Inaction::createActionData();

  entity.proc().addJoin(building, Building::sComplete, inaction);
  entity.proc().setCurrentAction(building);

  return true;
}

bool Entity::Factory::initPylon(Entity& entity) {
  SIADebug("Init pylon.");
  Common::Features& features = *entity.m_pFeatures.get();

  features[Common::FeatureNames::maxHP] = 100;
  features[Common::FeatureNames::HP] = 100;
  features[Common::FeatureNames::physic] = true;

  entity.prop() += Properties::Build::create();
  entity.prop() += Properties::TransmitterEnergy::create(1.0);

  ActionDataPtr building = Building::createActionData(10.0);
  ActionDataPtr inaction = Inaction::createActionData();

  entity.proc().addJoin(building, Building::sComplete, inaction);
  entity.proc().setCurrentAction(building);

  return true;
}
bool Entity::Factory::initMinerMinerals(Entity& entity) {
  SIADebug("Init miner minerals.");
  Common::Features& features = *entity.m_pFeatures.get();
  
  features[Common::FeatureNames::maxHP] = 50;
  features[Common::FeatureNames::HP] = 50;
  features[Common::FeatureNames::physic] = true;

  entity.prop() += Properties::Build::create();

  return true;

}
bool Entity::Factory::initMinerals(Entity& entity) {
  SIADebug("Init minerals.");
  Common::Features& features = *entity.m_pFeatures.get();

  features[Common::FeatureNames::maxHP] = 1000;
  features[Common::FeatureNames::HP] = 1000;
  features[Common::FeatureNames::physic] = true;

  entity.prop() += Properties::Build::create();

  return true;
}