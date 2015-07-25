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

namespace Common
{
  class ReadWriteMutex {
  public:
    void readLock();
    void readUnlock();

    void writeLock();
    void writeUnlock();
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_READ_WRITE_MUTEX_H__
