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
  struct MessageData {
    const char* logLevel;
    std::string msg;
    const char* file;
    int line;
    const char* module;
        
    MessageData(const char* file, int line, const char* module, const char* message, ...);
        
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

template<typename T> static T SIADefaultModuleName() { static T value = nullptr; return value; }
#define SIASetModuleName(NAME) template<> static const char* SIADefaultModuleName<const char*>() { static const char* value = #NAME; return value; }

#define SIAMsg(MSG, ...) (SIA::MessageData(__FILE__, __LINE__, SIADefaultModuleName<const char*>(), MSG, ##__VA_ARGS__))

#define SIAFatal(MSG, ...) SIA::Fatal::fast(SIAMsg(MSG, ##__VA_ARGS__))
#define SIAError(MSG, ...) SIA::Error::fast(SIAMsg(MSG, ##__VA_ARGS__))
#define SIAWarning(MSG, ...) SIA::Warning::fast(SIAMsg(MSG, ##__VA_ARGS__))
#define SIADebug(MSG, ...) SIA::Debug::fast(SIAMsg(MSG, ##__VA_ARGS__))
#define SIAInfo(MSG, ...) SIA::Info::fast(SIAMsg(MSG, ##__VA_ARGS__))
#define SIATrace(MSG, ...) SIA::Trace::fast(SIAMsg(MSG, ##__VA_ARGS__))

#define SIAAssert(CONDITION) SIA::Assert::fast((CONDITION) ? true : false, SIAMsg(#CONDITION" failed."))
#define SIAAssertMsg(CONDITION, MSG, ...) SIA::Assert::fast((CONDITION) ? true : false, SIAMsg(MSG, ##__VA_ARGS__))

#define SIAFatalAssert(CONDITION) \
   if((CONDITION) ? false : true) { SIA::Fatal::fast(SIAMsg(#CONDITION" failed.")); }

#define SIACheck(CONDITION) SIA::Check::fast((CONDITION) ? true : false, SIAMsg(#CONDITION" failed."))

#define SIACheckRet(CONDITION) \
  if (SIA::Check::fast((CONDITION) ? true : false, SIAMsg(#CONDITION" failed."))) { \
     return; \
  }

#define SIACheckRetValue(CONDITION, RET_VALUE) \
  if (SIA::Check::fast((CONDITION) ? true : false, SIAMsg(#CONDITION" failed."))) { \
    return RET_VALUE; \
  }

#endif // _SIA_LOGGER_H__
