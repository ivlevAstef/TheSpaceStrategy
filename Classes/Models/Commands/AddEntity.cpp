#include "AddEntity.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Commands);

using namespace Models;
using namespace Commands;

AddEntity::AddEntity(Models::EntityPtr pEntity) {
  SIAAssert(pEntity);
  m_pEntity = pEntity;
  SIATrace("Create Add entity command.");
}

void AddEntity::perform(Models::AreaPtr pArea) {
  SIAFatalAssert(pArea);
  SIAAssert(m_pEntity);

  bool success = pArea->addEntity(m_pEntity);
  done(success);
}
