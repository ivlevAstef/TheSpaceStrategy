//
//File: SIALogLevels.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
class LogLevel {
protected:
	void LogToStream(const char* logLevel, MessageData& logInfo);
};

class Exit : protected LogLevel {
public:
	Exit(MessageData& logInfo) {
		logInfo.msg = "Exit from application.";
		LogToStream("Exit", logInfo);
		exit( EXIT_FAILURE);
	}
};

class Fatal : protected LogLevel {
public:
	Fatal(MessageData& logInfo) { LogToStream("Fatal", logInfo); Exit exit(logInfo); }
};

class Error : protected LogLevel {
public:
	Error(MessageData& logInfo) { LogToStream("Error", logInfo);
	#ifdef ENABLE_DEBUG
	  Exit exit(logInfo);
	#endif
	}
};

class Warning : protected LogLevel {
public:
	Warning(MessageData& logInfo) { LogToStream("Warning", logInfo); }
};

#ifdef ENABLE_DEBUG

class Debug : protected LogLevel {
public:
	Debug(MessageData& logInfo) { LogToStream("Debug", logInfo); }
};

class Info : protected LogLevel {
public:
	Info(MessageData& logInfo) { LogToStream("Info", logInfo); }
};

#ifdef ENABLE_TRACE
class Trace : protected LogLevel {
public:
	Trace(MessageData& logInfo) { LogToStream("Trace", logInfo); }
};
#else
class Trace { public: Trace(MessageData& logInfo) {} };
#endif

#else
class Debug { public: Debug(MessageData& logInfo) {} };
class Info { public: Info(MessageData& logInfo) {} };
class Trace { public: Trace(MessageData& logInfo) {} };
#endif


class Assert : protected LogLevel {
public:
	Assert(bool Conditional, MessageData& logInfo) {
		if (!Conditional) {
			LogToStream("Assert", logInfo);
#ifdef ENABLE_DEBUG
			Exit exit(logInfo);
#endif
		}
	}
};

class Check : protected LogLevel {
public:
	Check(bool Conditional, MessageData& logInfo) : m_failed(false) {
		if (Conditional) {
			LogToStream("Check", logInfo);
			m_failed = true;
		}
	}
	
	inline bool failed() const { return m_failed; }
	
private:
	bool m_failed;
};