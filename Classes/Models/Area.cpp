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
    return m_entities.add(pEntity);
  }

  SIADebug("Can't setup entity.");
  return false;
}

bool Area::eraseEntity(EntityPtr pEntity) {
  SIAAssert(pEntity);
  return m_entities.remove(pEntity);
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