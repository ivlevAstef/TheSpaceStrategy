
#include "Entities_Grid.h"
#include "Entity_Factory.h"
#include "Utils/SIALogger.h"
#include <stack>

SIASetModuleName(Models);

using namespace Models;
using namespace Common;

Entities::Grid::Grid(const Entities& parent, size_t width, size_t height) : m_parent(parent) {
  m_width = width;
  m_height = height;
  m_grid.resize(width*height);
}

bool Entities::Grid::add(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity) {
    auto cellPos = Common::ModelMath::cell(pEntity->pos());
    int index = getIndex(cellPos);

    if (0 <= index && index < (int)m_grid.size()) {
      for (auto cell : m_grid[index]) {
        if (cell == pEntity) {
          return false;
        }
      }

      m_grid[index].push_back(pEntity);

      return true;
    }
  }
  return false;
}

void Entities::Grid::unsafeAdd(EntityPtr pEntity) {
  auto cellPos = Common::ModelMath::cell(pEntity->pos());
  int index = getIndex(cellPos);

  m_grid[index].push_back(pEntity);
}

bool Entities::Grid::erase(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity) {
    auto cellPos = Common::ModelMath::cell(pEntity->pos());
    int index = getIndex(cellPos);

    if (0 <= index && index < (int)m_grid.size()) {
      for (auto iter = m_grid[index].begin(); iter != m_grid[index].end(); ++iter) {
        if ((*iter) == pEntity) {
          m_grid[index].erase(iter);
          return true;
        }
      }
    }
  }

  return false;
}

void Entities::Grid::update(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity) {
    auto cellLastPos = Common::ModelMath::cell(pEntity->lastPos());
    auto cellPos = Common::ModelMath::cell(pEntity->pos());

    if (cellLastPos != cellPos) {
      int lastIndex = getIndex(cellLastPos);
      int index = getIndex(cellPos);

      if (0 <= lastIndex && lastIndex < (int)m_grid.size()) {
        for (auto iter = m_grid[lastIndex].begin(); iter != m_grid[lastIndex].end(); ++iter) {
          if ((*iter) == pEntity) {
            m_grid[lastIndex].erase(iter);
            break;
          }
        }

        if (0 <= index && index < (int)m_grid.size()) {
          unsafeAdd(pEntity);
        }
      }
    }
  }
}

void Entities::Grid::update() {

}

std::list<EntityPtr> Entities::Grid::get(const Common::CellPos& cell) const {
  SIAAssert(cell.x <(int)m_width && cell.y < (int)m_height);

  int index = getIndex(cell);

  return m_grid[index < (int)m_grid.size() ? index : (int)m_grid.size() - 1];
}

std::vector<CellPos> Entities::Grid::heldCell(const EntityPos& pos, const EntitySize& size) const {
  CellPos centerCellPos = ModelMath::cell(pos);

  std::vector<CellPos> cellPoss;
  cellPoss.reserve(4);

  cellPoss.push_back(centerCellPos);

  double x = pos.x - floor(pos.x);
  double y = pos.y - floor(pos.y);
  double sx = (size.x + Entity::Factory::maxEntitySize().x) / 2.0;
  double sy = (size.y + Entity::Factory::maxEntitySize().y) / 2.0;

  int hMove = (sx < x && x < 1 - sx) ? 0 : ((x < 0.5) ? -1 : 1);
  int vMove = (sy < y && y < 1 - sy) ? 0 : ((y < 0.5) ? -1 : 1);

  bool isHMove = 0 != hMove && 0 <= centerCellPos.x + hMove && centerCellPos.x + hMove < (int)m_width;
  bool isVMove = 0 != vMove && 0 <= centerCellPos.y + vMove && centerCellPos.y + vMove < (int)m_height;

  if (isHMove) {
    cellPoss.push_back(CellPos(centerCellPos.x + hMove, centerCellPos.y));
  }

  if (isVMove) {
    cellPoss.push_back(CellPos(centerCellPos.x, centerCellPos.y + vMove));
  }

  if (isHMove && isVMove) {
    cellPoss.push_back(CellPos(centerCellPos.x + hMove, centerCellPos.y + vMove));
  }

  return cellPoss;
}

static bool isCollision(EntityPtr pEntity1, EntityPtr pEntity2) {
  double radius1 = fmax(pEntity1->size().x, pEntity1->size().y) / 2.0;
  double radius2 = fmax(pEntity2->size().x, pEntity2->size().y) / 2.0;

  return ModelMath::distance(pEntity1->pos(), pEntity2->pos()) < radius1 + radius2;
}

std::list<EntityPtr> Entities::Grid::collision(const EntityPtr& pEntity) const {
  std::list<EntityPtr> res;

  std::vector<CellPos> heldCellPos = heldCell(pEntity->pos(), pEntity->size());
  for (CellPos cellPos : heldCellPos) {
    for (auto pEntityIter : get(cellPos)) {
      if (isCollision(pEntity, pEntityIter)) {
        res.push_back(pEntityIter);
      }
    }
  }

  return res;
}