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

namespace Common
{
  class TimeStamp {
  public:
    static TimeStamp now();
    static double deltaTime(TimeStamp t1, TimeStamp t2);

    double deltaTime(/*now*/);
    double deltaTime(TimeStamp timeStamp);
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_TIME_STAMP_H__
