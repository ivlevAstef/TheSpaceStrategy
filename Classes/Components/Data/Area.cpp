#include "Area.h"

using namespace Components::Data;

Area* Area::create() {
  return new Area();
}

void Area::addEntity(Entity* pEntity) {
  for (Entity* pIterEntity : m_pEntities) {
    if (pEntity == pIterEntity) {
      return;
    }
  }

  m_pEntities.push_back(pEntity);
}
void Area::removeEntity(Entity* pEntity) {
  for (size_t i = 0; i < m_pEntities.size(); i++) {
    if (pEntity == m_pEntities[i]) {
      m_pEntities.erase(m_pEntities.begin() + i);
      return;
    }
  }
}

void Area::update() {
  static const int CELL_POSITION_X = 100;
  static const int CELL_POSITION_Y = 100;

  for (Entity* pEntity : m_pEntities) {
    pEntity->m_real.x = pEntity->m_cell.x * CELL_POSITION_X;
    pEntity->m_real.y = pEntity->m_cell.y * CELL_POSITION_Y;
  }
}

bool Area::convert(const int x, const int y, float& toX, float& toY) {
  return true;
}