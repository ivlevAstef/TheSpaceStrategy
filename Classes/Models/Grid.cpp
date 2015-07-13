#include "Grid.h"
#include "Grid_Cell.h"

#include "SIALogger.h"
#include "Common/ModelMath.h"
#include "Components/EnergyGenerator.h"
#include "Components/TransmitterEnergy.h"

SIASetModuleName(Model);

using namespace Models;
using namespace Common;
using namespace Components;

void Grid::update(const EntityArray& entities) {
  cleanCells();

  std::list<Cell::EnergyNode*> generators;

  entities.foreach([this, &generators] (EntityPtr iter) -> bool {
    CellPos cellPos = ModelMath::cell(iter->pos());
    Cell* cell = getCell(cellPos.x, cellPos.y);

    if (cell) {
      bool isGenerator = iter->is<EnergyGenerator>();
      bool isTransmitter = iter->is<TransmitterEnergy>();

      if (isGenerator) {
        generators.push_back(&cell->m_energyNode);
        cell->m_energyNode.isGenerator = true;
      }


      cell->m_energyNode.isTransmitter |= isTransmitter;

      if (cell->isJoined()) {
        cell->addJoinIfNeed(getCell(cellPos.x - 1, cellPos.y));
        cell->addJoinIfNeed(getCell(cellPos.x, cellPos.y - 1));
        cell->addJoinIfNeed(getCell(cellPos.x + 1, cellPos.y));
        cell->addJoinIfNeed(getCell(cellPos.x, cellPos.y + 1));
      }

    }

    return true;
  });


  for (auto node : generators) {
    distributeEnergyFrom(node);
  }

}

void Grid::distributeEnergyFrom(Cell::EnergyNode* node) {
  if (!node || node->isEnergy) {
    return;
  }

  node->isEnergy = true;

  for (auto join : node->joins) {
    distributeEnergyFrom(join);
  }

}

void Grid::setSize(size_t width, size_t height) {
  if (m_width != width || m_height != height) {
    m_width = width;
    m_height = height;

    m_Cells.resize(m_width * m_height);
  }
}

void Grid::cleanCells() {
  for (Cell& cell : m_Cells) {
    cell.clean();
  }
}

#define MIN(V1, V2) (((V1) < (V2)) ? (V1) : (V2))
#define MAX(V1, V2) (((V1) > (V2)) ? (V1) : (V2))

#define INTERVAL(BEGIN, V, END) MIN(MAX(V, BEGIN), END)

void Grid::foreach(int x, int y, 
                   int width, int height, 
                   std::function<void(size_t, size_t , const Cell&)> cell) const {
  SIAAssert((bool)cell);
  size_t bX = INTERVAL(0, x, (int)m_width);
  size_t bY = INTERVAL(0, y, (int)m_height);

  size_t eX = INTERVAL(0, x + width, (int)m_width);
  size_t eY = INTERVAL(0, y + height, (int)m_height);

  for (int x = bX; x < eX; x++) {
    for (int y = bY; y < eY; y++) {
      cell(x, y, m_Cells.at(y * m_height + x));
    }
  }
}

Cell* Grid::getCell(int x, int y) {
  SIAAssert(m_Cells.size() == m_width * m_height);
  
  if (x < 0 || y < 0 || (size_t)x > m_width || (size_t)y > m_height) {
    return nullptr;
  }

  return &m_Cells.at(y * m_height + x);

}