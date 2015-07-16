//
//File: SIALogger.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#include "../SIALogger.h"

#include <iomanip>
#include <ctime>

#include <iostream>
#include <sstream>
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr

#if defined(_WIN32)
#include <Windows.h>
#endif

#define ABS(a) ((a) < 0 ? -(a) : (a))

#pragma warning( push )
#pragma warning( disable : 4996 )

static std::string vStringFormat(const char* fmt, va_list ap) {

  int n = ((int)strlen(fmt)) * 2;
  n = (n < 1024) ? 1024 : n;

  std::string str;
  std::unique_ptr<char[]> formatted;

  formatted.reset(new char[n]);
  strncpy(&formatted[0], fmt, n);

  int res = vsnprintf(&formatted[0], n, fmt, ap);
  if (res < 0 || res >= n) {
    return "";
  }
    
  return std::string(formatted.get());
}

static std::string stringFormat(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  std::string res = vStringFormat(fmt, ap);
  va_end(ap);

  return res;
}


using namespace SIA;

void LogLevel::logToStream(const char *logLevel, MessageData& logInfo) {
  SIAAssert(Logger::single != nullptr);
  logInfo.logLevel = logLevel;
  Logger::single->LogToStream(logInfo);
}

MessageData::MessageData(const char* lFile, int lLine, const char* lModule, const char* lFmt, ...) {
  logLevel = nullptr;
  file = lFile;
  line = lLine;
  module = lModule;

  std::unique_ptr<char[]> formatted;
  int n = ((int)strlen(lFmt)) * 2;
  n = (n < 1024) ? 1024 : n;

  formatted.reset(new char[1024]);

  va_list ap;
  va_start(ap, lFmt);
  msg = vStringFormat(lFmt, ap);
  va_end(ap);
}

static std::string fileName(std::string filePath) {
  std::size_t found = filePath.find_last_of("/\\");
  if (found == std::string::npos) {
     return filePath;
  }
  return filePath.substr(found+1);
}

std::string MessageData::toString() const {
  std::stringstream stream;
    
  if (nullptr != module) {
    stream << "[" << module << "] ";
  }
    
  if (nullptr != logLevel) {
    stream << logLevel << "-";
  }
    
  if (nullptr != file) {
    stream << "{" << fileName(file) << ":" << line << "}: ";
  }
    
  stream << msg << std::endl;
    
  return stream.str();
}

Logger* Logger::single = nullptr;

void Logger::Initialization() {
  SIAAssert(nullptr == single);
  single = new Logger();
}

Logger::Logger() {
  m_startApplicationTime = std::chrono::high_resolution_clock::now();
    
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::cout << "Application Start at " << std::put_time(std::localtime(&now_c), "%F %T") << "." << std::endl;
}

void Logger::LogToStream(const SIA::MessageData& logInfo) {
  auto diff = std::chrono::high_resolution_clock::now() - m_startApplicationTime;
    
  auto min = std::chrono::duration_cast<std::chrono::minutes>(diff).count();
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
  sec -= min * 60;
    
  auto date = stringFormat("%02d:%02d ", min, sec);
  auto message = date + logInfo.toString();


  std::cerr << message;
#if defined(_WIN32)
  OutputDebugStringA(message.c_str());
  //OutputDebugStringA("\n");
#endif
}

#pragma warning( pop )