#include "Entity.h"
#include "Common/FeatureNames.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Models);

using namespace Models;
using namespace Common;

Entity::Entity() : m_process(m_properties) {
  m_pFeatures = std::make_shared<Features>();
  m_size.set(0, 0);
}

void Entity::update() {
  m_mutex.BeginUpdate();

  m_process.update(m_mutex.timestamp().deltaTime());

  m_mutex.EndUpdate();
}

void Entity::draw(std::function<void(const Entity& entity, double dt)> drawFunc) {
  SIAAssert((bool)drawFunc);

  m_mutex.BeginDraw();

  drawFunc(*this, m_mutex.timestamp().deltaTime());

  m_mutex.EndDraw();
}

void Entity::setPos(EntityPos pos) {
  m_lastPos = m_pos;
  m_pos = pos;
}