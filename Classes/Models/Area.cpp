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
  SIAAssert(pEntity);
  
  if (setupEntity(pEntity)) {
    bool success = m_entities.add(pEntity);
    success &= m_grid.add(pEntity);

    if (success) {
      return true;
    } else {
      SIAWarning("Can't add entity. already exist?");
      m_entities.erase(pEntity);
      m_grid.erase(pEntity);

      return false;
    }

  }

  SIAWarning("Can't setup entity.");
  return false;
}

bool Area::eraseEntity(EntityPtr pEntity) {
  SIAAssert(pEntity);
  bool success = m_entities.erase(pEntity);
  success |= m_grid.erase(pEntity);
  return success;
}

bool Area::setupEntity(EntityPtr pEntity) {
  if (!(bool)pEntity) {
    SIAError("Entity can't setup because it's null.");
    return false;
  }

  if (pEntity->prop().is<Build>()) {
    return true;
  }

  return false;
}

void Area::update() {
  m_entities.update();
}