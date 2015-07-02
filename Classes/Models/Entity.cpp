#include "Entity.h"
#include "Common/FeatureNames.h"
#include "logger/SIAUtils_Logger.h"

using namespace Models;
using namespace Common;

Entity::Entity() {
  m_pFeatures = std::make_shared<Features>();
}

void Entity::setPos(EntityPos pos) {
  m_pos = pos;
}