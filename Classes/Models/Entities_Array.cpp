//
//File: Entities_Array.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 20:49 30/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#include "Entities_Array.h"
#include "SIALogger.h"
#include "Common/ModelMath.h"

SIASetModuleName(Models);

using namespace Models;
using namespace Common;

Entities::Array::Array(const Entities& parent, size_t maxCount) : m_parent(parent) {
  m_maxCount = maxCount;
}

bool Entities::Array::add(EntityPtr pEntity) {
  SIAAssert(pEntity);

  for (EntityPtr pIterEntity : m_pEntities) {
    if (pEntity.get() == pIterEntity.get()) {
      SIAError("Already add entity to array.");
      return false;
    }
  }

  m_pEntities.push_back(pEntity);

  return true;

}
void Entities::Array::update(EntityPtr pEntity) {

}
bool Entities::Array::erase(EntityPtr pEntity) {
  SIAAssert(pEntity);

  for (size_t i = 0; i < m_pEntities.size(); i++) {
    if (pEntity == m_pEntities[i]) {
      m_pEntities.erase(m_pEntities.begin() + i);
      return true;
    }
  }

  SIAWarning("Can't find entity in array.");
  return false;
}

void Entities::Array::update() {
  for (EntityPtr pIterEntity : m_pEntities) {
    pIterEntity->update();
  }
}

void Entities::Array::foreachCell(Common::CellPos pos, FindResultCallback callback) const {
  SIAAssert(callback);
  for (EntityPtr iter : m_pEntities) {
    if (ModelMath::cell(iter->pos()) == pos) {
      if (!callback(iter)) {
        break;
      }
    }
  }
}

void Entities::Array::foreach(FindResultCallback callback) const {
  SIAAssert(callback);
  for (EntityPtr iter : m_pEntities) {
    if (!callback(iter)) {
      break;
    }
  }
}