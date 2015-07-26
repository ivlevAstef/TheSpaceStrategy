#include "EntityMutex.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Sync);

using namespace Common;

void EntityMutex::BeginDraw() {
  m_rwMutex.readLock();
}
void EntityMutex::EndDraw() {
  m_rwMutex.readUnlock();
}

void EntityMutex::BeginUpdate() {
  m_rwMutex.writeLock();
}
void EntityMutex::EndUpdate() {
  SIAAssert(m_rwMutex.writer());

  m_timestamp = TimeStamp::now();

  m_rwMutex.writeUnlock();
}

const TimeStamp& EntityMutex::timestamp() const {
  return m_timestamp;
}