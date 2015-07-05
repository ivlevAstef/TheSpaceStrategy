#include "Area.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GridMath.h"
#include "Components/Build.h"
#include "Components/TransmitterEnergy.h"
#include "Common/ModelMath.h"

using namespace Models;
using namespace Common;
using namespace Components;

bool Area::addEntity(EntityPtr pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity.get());
  
  if (setupEntity(pEntity)) {
    return m_Entities.add(pEntity);
  }
  return false;
}

void Area::removeEntity(EntityPtr pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity.get());
  m_Entities.remove(pEntity);
}

bool Area::setupEntity(EntityPtr pEntity) {
  if (pEntity->is<Build>()) {
    bool buildsPosIndex[ModelMath::ePosIndexCount] = { false };
    CellPos cell = ModelMath::cell(pEntity->pos());

    m_Entities.foreachCell(cell, [&pEntity, &buildsPosIndex] (EntityPtr iter) {
      if (iter->is<Build>()) {
        auto posIndex = ModelMath::buildPos(iter->pos());
        if (posIndex != ModelMath::eUndefined) {
          buildsPosIndex[posIndex] = true;
        }
      }
      return true;
    });

    auto setBuildPos = [&buildsPosIndex, &cell, &pEntity](ModelMath::PosIndex index) -> bool {
      if (!buildsPosIndex[index]) {
        auto buildPos = ModelMath::buildPos(cell, index);
        pEntity->setPos(buildPos);
        return true;
      }
      return false;
    };
    
    if (pEntity->is<TransmitterEnergy>()) {
      return setBuildPos(ModelMath::eCenter);
    } else {
      for (size_t i = 0; i < ModelMath::ePosIndexCount; i++) {
        if (ModelMath::eCenter != i && setBuildPos(static_cast<ModelMath::PosIndex>(i))) {
          return true;
        }
      }
    }

    return false;
  }

  return true;
}

void Area::update() {
  m_grid.update(m_Entities);
}