#include "Entity_Factory.h"

#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

#include "Components/EnergyGenerator.h"
#include "Components/TransmitterEnergy.h"
#include "Components/Build.h"

using namespace Models;

EntityPtr Entity::Factory::createBuildByName(std::string name) {
  auto entity = EntityPtr(new Models::Entity());
  SIA_ASSERT(entity.get());

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
 
  return EntityPtr(nullptr);
}

bool Entity::Factory::initMainBase(Entity& entity) {
  Common::Features& features = *entity.m_pFeatures.get();

  features[Common::FeatureNames::maxHP] = 100;
  features[Common::FeatureNames::HP] = 100;
  features[Common::FeatureNames::physic] = true;

  entity.addComponent(Components::Build::create());
  entity.addComponent(Components::EnergyGenerator::create(25.0));

  return true;
}

bool Entity::Factory::initPylon(Entity& entity) {
  Common::Features& features = *entity.m_pFeatures.get();

  features[Common::FeatureNames::maxHP] = 100;
  features[Common::FeatureNames::HP] = 100;
  features[Common::FeatureNames::physic] = true;

  entity.addComponent(Components::Build::create());
  entity.addComponent(Components::TransmitterEnergy::create(1.0));

  return true;
}
bool Entity::Factory::initMinerMinerals(Entity& entity) {
  Common::Features& features = *entity.m_pFeatures.get();
  
  features[Common::FeatureNames::maxHP] = 50;
  features[Common::FeatureNames::HP] = 50;
  features[Common::FeatureNames::physic] = true;

  entity.addComponent(Components::Build::create());

  return true;

}
bool Entity::Factory::initMinerals(Entity& entity) {
  Common::Features& features = *entity.m_pFeatures.get();

  features[Common::FeatureNames::maxHP] = 1000;
  features[Common::FeatureNames::HP] = 1000;
  features[Common::FeatureNames::physic] = true;

  entity.addComponent(Components::Build::create());

  return true;
}