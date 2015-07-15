#include "Area.h"
#include "SIALogger.h"
#include "Properties/Build.h"
#include "Properties/TransmitterEnergy.h"
#include "Common/ModelMath.h"

SIASetModuleName(Model);

using namespace Models;
using namespace Common;
using namespace Properties;

bool Area::addEntity(EntityPtr pEntity) {
  SIAAssert(pEntity.get());
  
  if (setupEntity(pEntity)) {
    return m_Entities.add(pEntity);
  }

  SIADebug("Can't setup entity.");
  return false;
}

void Area::removeEntity(EntityPtr pEntity) {
  SIAAssert(pEntity.get());
  m_Entities.remove(pEntity);
}

bool Area::setupEntity(EntityPtr pEntity) {
  if (((Prop)*pEntity).is<Build>()) {
    bool buildsPosIndex[ModelMath::ePosIndexCount] = { false };
    CellPos cell = ModelMath::cell(pEntity->pos());

    m_Entities.foreachCell(cell, [&pEntity, &buildsPosIndex] (EntityPtr iter) {
      if (((Prop)*iter).is<Build>()) {
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
        SIAInfo("Set build pos to point: {%f,%f}.", buildPos.x, buildPos.y);
        return true;
      }
      return false;
    };
    
    if (((Prop)*pEntity).is<TransmitterEnergy>()) {
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
  m_pGrid->update(m_Entities);
}