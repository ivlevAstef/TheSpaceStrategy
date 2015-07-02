#include "Area.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GridMath.h"
#include "Components/Build.h"
#include "Components/TransmitterEnergy.h"
#include "Common/ModelMath.h"

using namespace Models;
using namespace Common;
using namespace Components;

class BuildPosComponent: public IComponent {
public:
  ModelMath::PosIndex m_pBuildPosIndex;

public:
  DEFINE_COMPONENT(BuildPosComponent);

  static IComponentPtr create(ModelMath::PosIndex posIndex) {
    return IComponentPtr(new BuildPosComponent(posIndex));
  }

private:
  BuildPosComponent(ModelMath::PosIndex posIndex) { 
    m_pBuildPosIndex = posIndex;
  }
};

bool Area::addEntity(EntityPtr pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity);
  for (EntityPtr pIterEntity : m_pEntities) {
    if (pEntity.get() == pIterEntity.get()) {
      return false;
    }
  }

  if (setupEntity(pEntity)) {
    m_pEntities.push_back(pEntity);
    return true;
  }
  return false;
}

void Area::removeEntity(EntityPtr pEntity) {
  SIA_LOG_FUNC("");
  SIA_ASSERT(pEntity);
  for (size_t i = 0; i < m_pEntities.size(); i++) {
    if (pEntity == m_pEntities[i]) {
      m_pEntities.erase(m_pEntities.begin() + i);
      return;
    }
  }
}

void Area::findEntityInCell(CellPos pos, std::function<void (EntityPtr entity)> FindResultCallback) {
  for each (EntityPtr iter in m_pEntities) {
    if (ModelMath::cell(iter->pos()) == pos) {
      FindResultCallback(iter);
    }
  }
}

bool Area::setupEntity(EntityPtr pEntity) {
  if (pEntity->is<Build>()) {
    bool buildsPosIndex[ModelMath::ePosIndexCount] = { false };

    findEntityInCell(ModelMath::cell(pEntity->pos()), [&buildsPosIndex] (EntityPtr pFoundEntity) {
      auto pBuildPos = pFoundEntity->as<BuildPosComponent>();
      if (pBuildPos.get()) {
        buildsPosIndex[pBuildPos->m_pBuildPosIndex] = true;
      }
    });

    if (pEntity->is<TransmitterEnergy>()) {
      if (!buildsPosIndex[ModelMath::eCenter]) {
        auto cellCenter = ModelMath::center(ModelMath::cell(pEntity->pos()));
        pEntity->setPos(cellCenter);
        pEntity->addComponent(BuildPosComponent::create(ModelMath::eCenter));
        return true;
      } 
      return false;
    }

    for (int i = ModelMath::ePosIndexBegin; i < ModelMath::ePosIndexOnlyBuildCount; i++) {
      ModelMath::PosIndex index = static_cast<ModelMath::PosIndex>(i);
      if (!buildsPosIndex[index]) {
        auto buildPos = ModelMath::buildPos(ModelMath::cell(pEntity->pos()), index);
        pEntity->setPos(buildPos);
        pEntity->addComponent(BuildPosComponent::create(index));
        return true;
      }
    }
    return false;
  }

  return true;
}

void Area::update() {
  m_grid.update(m_pEntities);
}