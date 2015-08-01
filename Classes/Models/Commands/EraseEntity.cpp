#include "EraseEntity.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Commands);

using namespace Models;
using namespace Commands;

EraseEntity::EraseEntity(Models::EntityPtr pEntity) {
  m_pEntity = pEntity;
  SIATrace("Create Erase entity command.");
}

void EraseEntity::perform(Models::AreaPtr pArea) {
  SIAFatalAssert(pArea);
  SIAAssert(m_pEntity);

  bool success = pArea->eraseEntity(m_pEntity);
  done(success);
}
