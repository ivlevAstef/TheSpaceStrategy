#include "Entity.h"
#include "Common/FeatureNames.h"

using namespace Components::Data;
using namespace Common;

Entity* Entity::create() {
  return new Entity();
}

void Entity::free(Entity* pEntity) {
  if (pEntity) {
    delete pEntity;
  }
}

Entity::Entity() {
  m_physical = m_features.cache(FeatureNames::physic);
  m_generator = m_features.cache(FeatureNames::generator);
  m_energy = m_features.cache(FeatureNames::energy);
  m_entityType = m_features.cache(FeatureNames::ID);
}

Entity::EntityType Entity::type() const {
  return static_cast<EntityType>(m_features.Int(m_entityType));
}