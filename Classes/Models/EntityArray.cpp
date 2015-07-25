#include "EntityArray.h"
#include "SIALogger.h"
#include "Common/ModelMath.h"

SIASetModuleName(Model);

using namespace Models;
using namespace Common;

bool EntityArray::add(EntityPtr pEntity) {
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

bool EntityArray::remove(EntityPtr pEntity) {
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

void EntityArray::update() {
  for (EntityPtr pIterEntity : m_pEntities) {
    pIterEntity->update();
  }
}

void EntityArray::foreachCell(Common::CellPos pos, FindResultCallback callback) const {
  SIAAssert(callback);
  for (EntityPtr iter : m_pEntities) {
    if (ModelMath::cell(iter->pos()) == pos) {
      if (!callback(iter)) {
        break;
      }
    }
  }
}

void EntityArray::foreach(FindResultCallback callback) const {
  SIAAssert(callback);
  for (EntityPtr iter : m_pEntities) {
    if (!callback(iter)) {
      break;
    }
  }
}