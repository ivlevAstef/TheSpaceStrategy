//
//File: ReadWriteMutex.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 7:58 25/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_READ_WRITE_MUTEX_H__
#define _SIA_THE_SPACE_STRATEGY_READ_WRITE_MUTEX_H__

#include <mutex>
#include <condition_variable>

namespace Common
{
  class ReadWriteMutex {
  public:
    ReadWriteMutex() = default;
    ReadWriteMutex(const ReadWriteMutex&) = delete;
    ~ReadWriteMutex();

    void readLock();
    void readUnlock();
    int readerCount();

    void writeLock();
    void writeUnlock();
    bool writer();

    bool locked();
    bool unlocked();

  private:
    std::mutex m_mutex;
    std::condition_variable m_writerNotify;
    std::condition_variable m_readersNotify;

    bool m_writer = false;
    int m_readers = 0;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_READ_WRITE_MUTEX_H__
