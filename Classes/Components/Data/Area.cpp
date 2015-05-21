#include "Area.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;

Area* Area::create() {
  COMPONENT_ALLOC(Area)();
  COMPONENT_INIT(Area);
}

bool Area::addEntity(Entity* pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity);
  for (Entity* pIterEntity : m_pEntities) {
    if (pEntity == pIterEntity) {
      return false;
    }
  }

  if (pEntity->physical() && !addPhysicEntity(pEntity)) {
    return false;
  }

  m_pEntities.push_back(pEntity);

  return true;
}

bool Area::addPhysicEntity(Entity* pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity);
  SIA_ASSERT(pEntity->physical());

  SIAUtils::Position pos = pEntity->cell();
  SIA_CHECK_ZERO(!checkEntityPosition(pos), WRN);
  
  if (m_cells[pos.y*m_width + pos.x].addEntity(pEntity)) {
    calculateRealPosFor(pEntity);
    return true;
  }

  return false;
}

void Area::removeEntity(Entity* pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity);
  for (size_t i = 0; i < m_pEntities.size(); i++) {
    if (pEntity == m_pEntities[i]) {
      m_pEntities.erase(m_pEntities.begin() + i);

      if (pEntity->physical()) {
        removePhysicEntity(pEntity);
      }
      return;
    }
  }
}

void Area::removePhysicEntity(Entity* pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity);
  SIA_ASSERT(pEntity->physical());

  SIAUtils::Position pos = pEntity->cell();
  SIA_CHECK_RET(!checkEntityPosition(pos), WRN);

  m_cells[pos.y*m_width + pos.x].removeEntity(pEntity);
}

void Area::setSize(size_t width, size_t height) {
  if (m_width != width || m_height != height) {
    m_cells.clear();

    m_width = width;
    m_height = height;

    m_cells.resize(m_width * m_height);
  }
}

void Area::calculateRealPosFor(Entity* pEntity) {
  static const SIAUtils::Position translated[Cell::maxPhysicalEntity] = {
    SIAUtils::Position(sCellSize*0.5f, sCellSize*0.8f),
    SIAUtils::Position(sCellSize*0.8f, sCellSize*0.5f),
    SIAUtils::Position(sCellSize*0.5f, sCellSize*0.2f),
    SIAUtils::Position(sCellSize*0.2f, sCellSize*0.5f)
  };

  SIAUtils::Position pos = pEntity->cell();

  if (Entity::Pylon == pEntity->type()) {
    pEntity->m_real.x = pos.x * sCellSize + sCellSize * 0.5f;
    pEntity->m_real.y = pos.y * sCellSize + sCellSize * 0.5f;
    return;
  }

  size_t trIndex = 0;
  for (; trIndex < Cell::maxPhysicalEntity; trIndex++) {
    if (pEntity == m_cells[pos.y*m_width + pos.x].pPhysicalEntities[trIndex]) {
      pEntity->m_real.x = pos.x * sCellSize + translated[trIndex].x;
      pEntity->m_real.y = pos.y * sCellSize + translated[trIndex].y;
    }
  }
}

bool Area::checkEntityPosition(const SIAUtils::Position& position) {
  if (position.x < 0 || position.x > (int)m_width ||
      position.y < 0 || position.y > (int)m_height) {
    SIA_LOG_DBG("incorrect entity position: (%d,%d)", position.x, position.y);
    return false;
  }
  return true;
}

void Area::updateEnergy() {

}

void Area::update() {
  SIA_ASSERT(m_cells.size() == m_width * m_height);

  updateEnergy();
}

//////////////////////////////////////Cell

bool Area::Cell::addEntity(Entity* pEntity) {
  SIA_ASSERT(pEntity);

  SIA_CHECK_ONE(!pEntity->physical(), INFO);

  if (Entity::Pylon == pEntity->type()) {
    SIA_CHECK_ZERO(pPylon, DBG);
    
    SIA_LOG_DBG("Add pylon on area");
    pPylon = pEntity;
    return true;
  }

  for (size_t i = 0; i < maxPhysicalEntity; i++) {
    if (pPhysicalEntities[i] == nullptr) {
      SIA_LOG_DBG("Add entity on area");
      pPhysicalEntities[i] = pEntity;
      return true;
    }
  }
  
  return false;
}

void Area::Cell::removeEntity(Entity* pEntity) {
  SIA_ASSERT(pEntity);

  SIA_CHECK_RET(!pEntity->physical(), INFO);

  if (pEntity == pPylon) {
    SIA_LOG_DBG("Remove pylon from area");
    pPylon = nullptr;
    return;
  }

  for (size_t i = 0; i < pPhysicalEntities.size(); i++) {
    if (pPhysicalEntities[i] == pEntity) {
      SIA_LOG_DBG("Remove entity from area");
      pPhysicalEntities[i] = nullptr;
      return;
    }
  }

  SIA_LOG_WRN("Can't remove entity from area");
}