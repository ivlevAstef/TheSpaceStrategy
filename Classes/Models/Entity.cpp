#include "Entity.h"
#include "Common/FeatureNames.h"

using namespace Models;
using namespace Common;

Entity::Entity() : m_process(m_properties) {
  m_pFeatures = std::make_shared<Features>();
}

void Entity::update(double dt) {
  m_process.update(dt);
}

void Entity::setPos(EntityPos pos) {
  m_pos = pos;
}