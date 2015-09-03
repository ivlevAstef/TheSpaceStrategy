//
//File: TimeStamp.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 7:39 25/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_TIME_STAMP_H__
#define _SIA_THE_SPACE_STRATEGY_TIME_STAMP_H__

#include <chrono>

namespace Common
{
  class TimeStamp {
  public:
    typedef double Seconds;
    
  public:
    ///construct and set current time
    TimeStamp();

    static TimeStamp now();
    static TimeStamp saveNow();
    static TimeStamp after(Seconds seconds);
    static void updateSaveNow();

    static Seconds deltaTime(const TimeStamp& t1, const TimeStamp& t2);

    Seconds deltaTime(/*now*/) const;
    Seconds deltaTime(const TimeStamp& timeStamp) const;

    TimeStamp& operator+=(Seconds seconds);
    TimeStamp operator+(Seconds seconds) const;

    bool operator<(const TimeStamp& timestamp) const;
    bool operator<=(const TimeStamp& timestamp) const;
    bool operator>(const TimeStamp& timestamp) const;
    bool operator>=(const TimeStamp& timestamp) const;

  private:
    static TimeStamp sSaveTimeStamp;
    
    std::chrono::system_clock::time_point m_timestamp;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_TIME_STAMP_H__
