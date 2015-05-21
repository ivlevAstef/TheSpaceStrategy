#include "EnergyGenerator.h"

#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;
using namespace Components::Data::Modificator;

const char* EnergyGenerator::generator = "Generator";
const char* EnergyGenerator::generatedEnergy = "GeneratedEnergy";

EnergyGenerator* EnergyGenerator::create(Features* features) {
  COMPONENT_ALLOC(EnergyGenerator)(features);
  COMPONENT_INIT(EnergyGenerator);
}

EnergyGenerator::EnergyGenerator(Features* features) {
  SIA_ASSERT(features);
  m_features = features;
  m_features->cRetain();

  m_features->Bool(generator) = true;
  m_features->Int(generatedEnergy) = 0;
}

EnergyGenerator::~EnergyGenerator() {
  m_features->erase(generator);
  m_features->erase(generatedEnergy);

  m_features->cRelease();
}