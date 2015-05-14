#include "Area.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;

Area* Area::create() {
  return new Area();
}

bool Area::addEntity(Entity* pEntity) {
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
  SIA_ASSERT(pEntity);
  SIA_ASSERT(pEntity->physical());

  SIAUtils::Position pos = pEntity->cell();
  if (!checkEntityPosition(pos)) {
    return false;
  }

  return m_cells[pos.y*m_width + pos.x].addEntity(pEntity);
}

void Area::removeEntity(Entity* pEntity) {
  SIA_ASSERT(pEntity);
  for (size_t i = 0; i < m_pEntities.size(); i++) {
    if (pEntity == m_pEntities[i]) {
      m_pEntities.erase(m_pEntities.begin() + i);
      return;
    }
  }
}

void Area::setSize(size_t width, size_t height)
{
  if (m_width != width || m_height != height) {
    m_cells.clear();

    m_width = width;
    m_height = height;

    m_cells.resize(m_width * m_height);
  }
}

void Area::recalculateCells() {

}

bool Area::checkEntityPosition(const SIAUtils::Position& position) {
  if (position.x < 0 || position.x > (int)m_width ||
      position.y < 0 || position.y >(int)m_height) {
    SIA_LOG_DBG("incorrect entity position: (%d,%d)", position.x, position.y);
    return false;
  }
  return true;
}

void Area::update() {
  static const SIAUtils::Position translated[Cell::maxPhysicalEntity] = {
    SIAUtils::Position(sCellSize*0.5f, sCellSize*0.75f),
    SIAUtils::Position(sCellSize*0.75f, sCellSize*0.5f),
    SIAUtils::Position(sCellSize*0.5f, sCellSize*0.25f),
    SIAUtils::Position(sCellSize*0.25f, sCellSize*0.5f)
  };

  SIA_ASSERT(m_cells.size() == m_width * m_height);

  for (size_t i = 0; i < m_cells.size(); i++) {
    int x = (int)(i % m_width);
    int y = (int)(i / m_width);

    size_t trIter = 0;

    for (Entity* pEntity : m_cells[i].pPhysicalEntities) {
      if (pEntity->cell().x != x || pEntity->cell().y != y) {
        SIA_LOG_ERR("physical entity moved...");
        continue;
      }

      pEntity->m_real.x = x * sCellSize + translated[trIter].x;
      pEntity->m_real.y = y * sCellSize + translated[trIter].y;

      trIter++;
    }
  }
}

bool Area::convert(const int x, const int y, float& toX, float& toY) {
  return true;
}

//////////////////////////////////////Cell

bool Area::Cell::addEntity(Entity* pEntity) {
  SIA_ASSERT(pEntity);

  if (!pEntity->physical()) {
    return true;
  }

  if (pPhysicalEntities.size() < maxPhysicalEntity) {
    pPhysicalEntities.push_back(pEntity);
    return true;
  }
  return false;
}