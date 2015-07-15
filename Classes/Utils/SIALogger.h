//
//File: SIALogger.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#pragma once
#ifndef _SIA_LOGGER_H__
#define _SIA_LOGGER_H__

#include <string>
#include <cstdlib>
#include <chrono>

///Fatal - log and exit. (use only if can't be corrected data)
///Error - log and if enable debug then exit. (use if can't be corrected data but the application can run)
///Warning - log. (use if can be correct data, but they should not be сorrectly)
///Debug - if enable debug then log. (use for log important code/event)
///Info - if enable debug then log. (use for log not often code/event)
///Trace - if enable debug and trace then log. (use for unimportant code/event)

///Assert - if conditional then equivalent error, else not log.
///Check - if conditional then log.

//fatal,error,warning, check worked always.
//enable debug,info,assert level, also error stoped program.
#define ENABLE_DEBUG
//enable trace level
#define ENABLE_TRACE

namespace SIA {
  struct Module {
    const char* module;
    Module(const char* module) : module(module) {}
  };
    
  struct MessageData {
    const char* logLevel;
    std::string msg;
    const char* file;
    int line;
    const char* module;
        
    MessageData(const char* file, int line, const char* message, ...);
        
    MessageData& operator<<(const Module& module);
        
    std::string toString() const;
  };

  #include "Private/SIALogLevels.h"
    
  class Logger {
  public:
   static void Initialization();
        
  private:
    Logger();
        
    friend class LogLevel;
    void LogToStream(const MessageData& logInfo);
    std::string formatLog(const MessageData& logInfo);
        
  private:
    static Logger* single;
        
    std::chrono::steady_clock::time_point m_startApplicationTime;
  };
    
};

template<typename T> static T SIADefaultModuleName() { static T value(nullptr); return value; }
#define SIASetModuleName(NAME) template<> static SIA::Module SIADefaultModuleName<SIA::Module>() { static SIA::Module value(#NAME); return value; }

#define SIAMsg(MSG, ...) (SIA::MessageData(__FILE__, __LINE__, MSG, __VA_ARGS__) << SIADefaultModuleName<SIA::Module>())

#define SIAFatal(MSG, ...) SIA::Fatal(SIAMsg(MSG, __VA_ARGS__))
#define SIAError(MSG, ...) SIA::Error(SIAMsg(MSG, __VA_ARGS__))
#define SIAWarning(MSG, ...) SIA::Warning(SIAMsg(MSG, __VA_ARGS__))
#define SIADebug(MSG, ...) SIA::Debug(SIAMsg(MSG, __VA_ARGS__))
#define SIAInfo(MSG, ...) SIA::Info(SIAMsg(MSG, __VA_ARGS__))
#define SIATrace(MSG, ...) SIA::Trace(SIAMsg(MSG, __VA_ARGS__))

#define SIAAssert(CONDITION) SIA::Assert((bool)(CONDITION), SIAMsg(#CONDITION" failed."))
#define SIAAssertMsg(CONDITION, MSG, ...) SIA::Assert((bool)(CONDITION), SIAMsg(MSG, __VA_ARGS__))

#define SIAFatalAssert(CONDITION) \
   if(!(bool)(CONDITION)) { SIA::Fatal(SIAMsg(#CONDITION" failed.")); }

#define SIACheck(CONDITION) SIA::Check((bool)(CONDITION), SIAMsg(#CONDITION" failed."))

#define SIACheckRet(CONDITION) \
  if (SIA::Check((bool)(CONDITION), SIAMsg(#CONDITION" failed.")).failed()) { \
     return; \
  }

#define SIACheckRetValue(CONDITION, RET_VALUE) \
  if (SIA::Check((bool)(CONDITION), SIAMsg(#CONDITION" failed.")).failed()) { \
    return RET_VALUE; \
  }

#endif // _SIA_LOGGER_H__
