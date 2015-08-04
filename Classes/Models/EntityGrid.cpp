//
//File: EntityGrid.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 19:57 3/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#include "EntityGrid.h"
#include "Utils/SIALogger.h"
#include <stack>

SIASetModuleName(Models);

using namespace Models;
using namespace Common;

EntityGrid::EntityGrid(size_t width, size_t height) : m_grid(width*height) {
  m_width = width;
  m_height = height;
}

bool EntityGrid::add(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity) {
    auto cellPos = Common::ModelMath::cell(pEntity->pos());
    int index = getIndex(cellPos);

    if (0 <= index && index < m_grid.size()) {
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

void EntityGrid::unsafeAdd(EntityPtr pEntity) {
  auto cellPos = Common::ModelMath::cell(pEntity->pos());
  int index = getIndex(cellPos);

  m_grid[index].push_back(pEntity);
}

bool EntityGrid::remove(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity) {
    auto cellPos = Common::ModelMath::cell(pEntity->pos());
    int index = getIndex(cellPos);

    if (0 <= index && index < m_grid.size()) {
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

bool EntityGrid::update(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity) {
    auto cellLastPos = Common::ModelMath::cell(pEntity->lastPos());
    auto cellPos = Common::ModelMath::cell(pEntity->pos());

    if (cellLastPos != cellPos) {
      int lastIndex = getIndex(cellLastPos);
      int index = getIndex(cellPos);

      if (0 <= lastIndex && lastIndex < m_grid.size()) {
        for (auto iter = m_grid[lastIndex].begin(); iter != m_grid[lastIndex].end(); ++iter) {
          if ((*iter) == pEntity) {
            m_grid[lastIndex].erase(iter);
            break;
          }
        }

        if (0 <= index && index < m_grid.size()) {
          unsafeAdd(pEntity);
        }
      }
    }
  }

}