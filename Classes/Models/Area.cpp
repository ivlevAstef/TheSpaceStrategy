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

Area::Area(size_t width, size_t height) : m_entities(width, height, MaxEntitiesCount) {
}

size_t Area::width() const {
  return m_entities.getGrid().width();
}

size_t Area::height() const {
  return m_entities.getGrid().height();
}

bool Area::addEntity(EntityPtr pEntity) {
  SIAAssert(pEntity);
  
  if (setupEntity(pEntity)) {
    if (m_entities.add(pEntity)) {
      return true;
    } else {
      SIAError("Can't add entity. already exist?");
      return false;
    }

  }

  SIAWarning("Can't setup entity.");
  return false;
}

bool Area::eraseEntity(EntityPtr pEntity) {
  SIAAssert(pEntity);
  return m_entities.erase(pEntity);
}

bool Area::setupEntity(EntityPtr pEntity) {
  if (!(bool)pEntity) {
    SIAError("Entity can't setup because it's null.");
    return false;
  }

  if (pEntity->prop().is<Build>()) {
    for (auto pEntityIter : m_entities.getGrid().collision(pEntity)) {
      if (pEntityIter->prop().is<Build>()) {
        return false;
      }
    }

    return true;
  }

  return false;
}

void Area::update() {
  TimeStamp::updateSaveNow();
  m_entities.update();
}