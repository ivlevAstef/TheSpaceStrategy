//
//File: SIALogLevels.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
class LogLevel {
protected:
  static void logToStream(const char* logLevel, MessageData& logInfo);
};

class Exit : protected LogLevel {
public:
  Exit(MessageData logInfo) { fast(logInfo); }

  static void fast(MessageData logInfo) {
    logInfo.msg = "Exit from application.";
    logToStream("Exit", logInfo);
    exit(EXIT_FAILURE);
  }
};

class Fatal : protected LogLevel {
public:
  Fatal(MessageData logInfo) { fast(logInfo); }

  static void fast(MessageData logInfo) {
    logToStream("Fatal", logInfo);
    SIA::Exit::fast(logInfo);
  }
};

class Error : protected LogLevel {
public:
  Error(MessageData logInfo) { fast(logInfo); }

  static void fast(MessageData logInfo) {
    logToStream("Error", logInfo);
#ifdef ENABLE_DEBUG
    SIA::Exit::fast(logInfo);
#endif
  }
};

class Warning : protected LogLevel {
public:
  Warning(MessageData logInfo) {
    fast(logInfo);
  }

  static void fast(MessageData logInfo) {
    logToStream("Warning", logInfo);
  }
};

#ifdef ENABLE_DEBUG

class Debug : protected LogLevel {
public:
  Debug(MessageData logInfo) {
    fast(logInfo);
  }

  static void fast(MessageData logInfo) {
    logToStream("Debug", logInfo);
  }
};

class Info : protected LogLevel {
public:
  Info(MessageData logInfo) {
    fast(logInfo);
  }

  static void fast(MessageData logInfo) {
    logToStream("Info", logInfo);
  }
};

#ifdef ENABLE_TRACE
class Trace : protected LogLevel {
public:
  Trace(MessageData logInfo) {
    fast(logInfo);
  }

  static void fast(MessageData logInfo) {
    logToStream("Trace", logInfo); }
};
#else
class Trace { public: Trace(MessageData) {} static void fast(MessageData) {} };
#endif

#else
class Debug { public: Debug(MessageData logInfo) {} static void fast(MessageData) {} };
class Info { public: Info(MessageData logInfo) {} static void fast(MessageData) {} };
class Trace { public: Trace(MessageData logInfo) {} static void fast(MessageData) {} };
#endif


class Assert : protected LogLevel {
public:
  Assert(bool Conditional, MessageData logInfo) { fast(Conditional, logInfo); }

  static void fast(bool Conditional, MessageData logInfo) {
    if (!Conditional) {
      logToStream("Assert", logInfo);
#ifdef ENABLE_DEBUG
      SIA::Exit::fast(logInfo);
#endif
    }
  }
};

class Check : protected LogLevel {
public:
  Check(bool Conditional, MessageData logInfo) {
    m_failed = fast(Conditional, logInfo);
  }

  static bool fast(bool Conditional, MessageData logInfo) {
    if (Conditional) {
      logToStream("Check", logInfo);
      return true;
    }
    return false;
  }
  
  inline bool failed() const { return m_failed; }
  
private:
  bool m_failed;
};