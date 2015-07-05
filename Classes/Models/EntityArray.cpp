#include "EntityArray.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/ModelMath.h"

using namespace Models;
using namespace Common;

bool EntityArray::add(EntityPtr pEntity) {
  SIA_ASSERT(pEntity.get());

  for (EntityPtr pIterEntity : m_pEntities) {
    if (pEntity.get() == pIterEntity.get()) {
      return false;
    }
  }

  m_pEntities.push_back(pEntity);

  return true;
}

bool EntityArray::remove(EntityPtr pEntity) {
  SIA_ASSERT(pEntity.get());

  for (size_t i = 0; i < m_pEntities.size(); i++) {
    if (pEntity == m_pEntities[i]) {
      m_pEntities.erase(m_pEntities.begin() + i);
      return true;
    }
  }

  return false;
}

void EntityArray::foreachCell(Common::CellPos pos, FindResultCallback callback) const {
  for (EntityPtr iter : m_pEntities) {
    if (ModelMath::cell(iter->pos()) == pos) {
      if (!callback(iter)) {
        break;
      }
    }
  }
}

void EntityArray::foreach(FindResultCallback callback) const {
  for (EntityPtr iter : m_pEntities) {
    if (!callback(iter)) {
      break;
    }
  }
}