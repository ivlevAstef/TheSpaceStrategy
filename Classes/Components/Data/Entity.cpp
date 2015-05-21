#include "Entity.h"
#include "Common/FeatureNames.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;
using namespace Common;

Entity* Entity::create(Features* features) {
  COMPONENT_ALLOC(Entity)(features);
  COMPONENT_INIT(Entity);
}

Entity::Entity(Features* features) {
  SIA_ASSERT(features);
  m_features = features;
  m_features->cRetain();

  m_physical = m_features->cache(FeatureNames::physic);
  m_generator = m_features->cache(FeatureNames::generator);
  m_energy = m_features->cache(FeatureNames::energy);
  m_entityType = m_features->cache(FeatureNames::ID);
}

Entity::~Entity() {
  m_features->cRelease();
}

Entity::EntityType Entity::type() const {
  return static_cast<EntityType>((__int32)(*m_features)[m_entityType]);
}