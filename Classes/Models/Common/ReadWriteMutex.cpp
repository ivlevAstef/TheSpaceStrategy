#include "ReadWriteMutex.h"
#include "Utils/SIALogger.h"

SIASetModuleName(Sync);

using namespace Common;

ReadWriteMutex::~ReadWriteMutex() {
  std::lock_guard<std::mutex> _(m_mutex);
}

void ReadWriteMutex::readLock() {
  std::unique_lock<std::mutex> lk(m_mutex);

  while (m_writer) {
    m_writerNotify.wait(lk);
  }

  m_readers++;
}
void ReadWriteMutex::readUnlock() {
  std::unique_lock<std::mutex> lk(m_mutex);

  SIAAssertMsg(m_readers > 0, "Please check program, because unlock didn't without lock, for read.");

  if (m_readers > 0) {
    m_readers--;

    m_readersNotify.notify_all();
  }
}

int ReadWriteMutex::readerCount() {
  std::unique_lock<std::mutex> lk(m_mutex);

  return m_readers;
}

void ReadWriteMutex::writeLock() {
  std::unique_lock<std::mutex> lk(m_mutex);

  while (m_writer) {
    m_writerNotify.wait(lk);
  }

  m_writer = true;

  while (m_readers > 0) {
    m_readersNotify.wait(lk);
  }
}
void ReadWriteMutex::writeUnlock() {
  std::unique_lock<std::mutex> lk(m_mutex);

  SIAAssertMsg(m_writer, "Please check program, because unlock didn't without lock, for write.");

  if (m_writer) {
    m_writer = false;

    m_writerNotify.notify_all();
  }
}

bool ReadWriteMutex::writer() {
  std::unique_lock<std::mutex> lk(m_mutex);

  return m_writer;
}

bool ReadWriteMutex::locked() {
  std::unique_lock<std::mutex> lk(m_mutex);

  return m_writer || m_readers > 0;
}
bool ReadWriteMutex::unlocked() {
  std::unique_lock<std::mutex> lk(m_mutex);

  return !m_writer && 0 == m_readers;
}