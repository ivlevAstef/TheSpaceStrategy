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

EntityGrid::EntityGrid(size_t width, size_t height) : m_grid(width*height + 1, m_cellHash) {
  m_width = width;
  m_height = height;
  m_cellHash.width = m_width;
  m_grid.max_load_factor(1.0);
}

bool EntityGrid::add(EntityPtr pEntity) {
  SIAAssert(pEntity);

  for (auto cell : m_grid) {
    if (cell.second == pEntity) {
      return false;
    }
  }

  unsafeAdd(pEntity);

  return true;
}

void EntityGrid::unsafeAdd(EntityPtr pEntity) {
  m_grid.emplace(ModelMath::cell(pEntity->pos()), pEntity);
}

bool EntityGrid::remove(EntityPtr pEntity) {
  SIAAssert(pEntity);

  for (GridType::const_iterator iter = m_grid.begin(); iter != m_grid.end(); ++iter) {
    if (iter->second == pEntity) {
      m_grid.erase(iter);
      return true;
    }
  }

  return false;
}

void EntityGrid::update() {
  std::stack<EntityPtr> entities;

  for (GridType::const_iterator iter = m_grid.begin(); iter != m_grid.end(); ) {
    auto currentPos = ModelMath::cell(iter->second->pos());
    if (currentPos == iter->first) {
      ++iter;
    } else {
      entities.push(iter->second);
      iter = m_grid.erase(iter);
    }
  }

  while (!entities.empty()) {
    unsafeAdd(entities.top());
    entities.pop();
  }
}