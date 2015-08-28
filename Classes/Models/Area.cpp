#include "Area.h"
#include "SIALogger.h"
#include "Properties/Build.h"
#include "Properties/TransmitterEnergy.h"
#include "Common/ModelMath.h"

#include <math.h>

SIASetModuleName(Model);

using namespace Models;
using namespace Common;
using namespace Properties;

bool Area::addEntity(EntityPtr pEntity) {
  SIAAssert(pEntity);
  
  if (setupEntity(pEntity)) {
    bool success = m_entities.add(pEntity);
    success &= m_grid.add(pEntity);
    success &= m_energyGraph.add(pEntity);

    if (success) {
      return true;
    } else {
      SIAError("Can't add entity. already exist?");
      m_energyGraph.erase(pEntity);
      m_grid.erase(pEntity);
      m_entities.erase(pEntity);

      return false;
    }

  }

  SIAWarning("Can't setup entity.");
  return false;
}

bool Area::eraseEntity(EntityPtr pEntity) {
  SIAAssert(pEntity);
  bool success = m_energyGraph.erase(pEntity);
  success |= m_grid.erase(pEntity);
  success |= m_entities.erase(pEntity);
  return success;
}

bool Area::setupEntity(EntityPtr pEntity) {
  if (!(bool)pEntity) {
    SIAError("Entity can't setup because it's null.");
    return false;
  }

  if (pEntity->prop().is<Build>()) {
    for (auto pEntityIter : m_grid.collision(pEntity)) {
      if (pEntityIter->prop().is<Build>()) {
        return false;
      }
    }

    return true;
  }

  return false;
}

void Area::update() {
  m_entities.update();
  m_energyGraph.update();
}