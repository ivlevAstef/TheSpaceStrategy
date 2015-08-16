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
//#define ENABLE_TRACE

namespace SIA {       
  class Logger {
  public:
   static void Initialization();

   static void logToStream(const char* logLevel, const char* file, int line, const char* module, const char* message, ...);

  private:
    Logger();
     
  private:
    static Logger* single;
        
    std::chrono::steady_clock::time_point m_startApplicationTime;
  };
};

///full list:
///SIASetModuleName

///SIAFatal
///SIAError
///SIAWarning
///SIADebug
///SIAInfo
///SIATrace

///SIAAssertMsg
///SIAAssert
///SIAFatalAssert

///SIACheck
///SIACheckRet
///SIACheckRetValue

template<typename T> static T SIADefaultModuleName() { static T value = nullptr; return value; }
#define SIASetModuleName(NAME) template<> static const char* SIADefaultModuleName<const char*>() { static const char* value = #NAME; return value; }

#define SIAMsg(MSG, ...) __FILE__, __LINE__, SIADefaultModuleName<const char*>(), MSG, ##__VA_ARGS__

#define SIAFatal(MSG, ...) { SIA::Logger::logToStream("Fatal", SIAMsg(MSG, ##__VA_ARGS__)); exit(EXIT_FAILURE); }

#ifdef ENABLE_DEBUG
#define SIAError(MSG, ...) { SIA::Logger::logToStream("Error", SIAMsg(MSG, ##__VA_ARGS__)); exit(EXIT_FAILURE); }
#else
#define SIAError(MSG, ...) { SIA::Logger::logToStream("Error", SIAMsg(MSG, ##__VA_ARGS__)); }
#endif


#define SIAWarning(MSG, ...) { SIA::Logger::logToStream("Warning", SIAMsg(MSG, ##__VA_ARGS__)); }

#ifdef ENABLE_DEBUG
#define SIADebug(MSG, ...) { SIA::Logger::logToStream("Debug", SIAMsg(MSG, ##__VA_ARGS__)); }
#define SIAInfo(MSG, ...) { SIA::Logger::logToStream("Info", SIAMsg(MSG, ##__VA_ARGS__)); }

  #ifdef ENABLE_TRACE
#define SIATrace(MSG, ...) { SIA::Logger::logToStream("Trace", SIAMsg(MSG, ##__VA_ARGS__)); }
  #else
    #define SIATrace(MSG, ...) { }
  #endif

#else
  #define SIADebug(MSG, ...) { }
  #define SIAInfo(MSG, ...) { }
#endif

#ifdef ENABLE_DEBUG
  #define SIAAssertMsg(CONDITION, MSG, ...) if (!(CONDITION)) { \
      SIA::Logger::logToStream("Assert", SIAMsg(MSG, ##__VA_ARGS__)); exit(EXIT_FAILURE); \
    }

  #define SIAAssert(CONDITION) { SIAAssertMsg(CONDITION, #CONDITION" failed."); }

#else
  #define SIAAssertMsg(CONDITION, MSG, ...) {}
  #define SIAAssert(CONDITION) {}
#endif

#define SIAFatalAssert(CONDITION)  if (!(CONDITION)) { \
    SIAFatal(#CONDITION" failed."); \
  }

#define SIACheck(CONDITION) if (CONDITION) { \
    SIA::Logger::logToStream("Check", SIAMsg(#CONDITION" failed.")); \
  }

#define SIACheckRet(CONDITION) if (CONDITION) { \
    SIA::Logger::logToStream("Check", SIAMsg(#CONDITION" failed.")); \
    return; \
  }

#define SIACheckRetValue(CONDITION, RET_VALUE) if (CONDITION) { \
    SIA::Logger::logToStream("Check", SIAMsg(#CONDITION" failed.")); \
    return RET_VALUE; \
  }

#endif // _SIA_LOGGER_H__
