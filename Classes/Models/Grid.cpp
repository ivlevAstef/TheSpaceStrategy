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

  entities.foreach([this] (EntityPtr iter) -> bool {
    CellPos cellPos = ModelMath::cell(iter->pos());
    Cell* cell = getCell(cellPos.x, cellPos.y);

    if (cell) {
      cell->m_isGenerator |= iter->is<EnergyGenerator>();
      cell->m_isTransmitter |= iter->is<TransmitterEnergy>();
    }

    return true;
  });


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