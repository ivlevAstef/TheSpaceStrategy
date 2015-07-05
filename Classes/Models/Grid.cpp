#include "Grid.h"

using namespace Models;

void Grid::update(const EntityArray& pEntities) {

}

void Grid::setSize(size_t width, size_t height) {
  if (m_width != width || m_height != height) {
    m_width = width;
    m_height = height;
  }
}