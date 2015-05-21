#include "EnergyGenerator.h"

#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;
using namespace Components::Data::Modificator;

static const char* generatorName = "Generator";
static const char* generatedEnergyName = "GeneratedEnergy";

EnergyGenerator* EnergyGenerator::create(Features* features, double generatedEnergy) {
  COMPONENT_ALLOC(EnergyGenerator)(features, generatedEnergy);
  COMPONENT_INIT(EnergyGenerator);
}

EnergyGenerator::EnergyGenerator(Features* features, double generatedEnergy) {
  SIA_ASSERT(features);
  m_features = features;
  m_features->cRetain();

  (*m_features)[generatorName] = true;
  setGeneratedEnergy(generatedEnergy);
}

void EnergyGenerator::setGeneratedEnergy(double generatedEnergy) {
  (*m_features)[generatedEnergyName] = generatedEnergy;
}

EnergyGenerator::~EnergyGenerator() {
  m_features->erase(generatorName);
  m_features->erase(generatedEnergyName);

  m_features->cRelease();
}

bool EnergyGenerator::isGenerator(const Features& features) {
  return features.is(generatorName) && (bool)features[generatorName];
}

double EnergyGenerator::getGeneratedEnergy(const Features& features) {
  return features.is(generatedEnergyName) && (double)features[generatedEnergyName];
}