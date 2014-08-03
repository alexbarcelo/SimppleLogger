//============================================================================
// Name        : logtest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <map>

enum levels{
	TRACE,
	DEBUG = 0,
	INFO,
	WARN,
	ERROR,
	FATAL,
	NEVER_LOG = 1000
};

using namespace std;


class StandardLogger;
class LoggerPairInitializer;

/**
Logs a message to a specified logger with the TRACE level.

@param logger the logger to be used.
@param message the message string to log.
*/
#define STDLOG_TRACE(logger, message) { \
        if (logger.getLevel() <= TRACE) {\
           std::ostringstream oss_; \
           oss_ << "TRACE " message; \
           logger.log(oss_.str()); }}

/**
Logs a message to a specified logger with the DEBUG level.

@param logger the logger to be used.
@param message the message string to log.
*/
#define STDLOG_DEBUG(logger, message) { \
        if (logger.getLevel() <= DEBUG) {\
           std::ostringstream oss_; \
           oss_ << "DEBUG " << message; \
           logger.log(oss_.str()); }}

static levels defaultLevel = DEBUG;

class InitLevel {
public:
	InitLevel() : storedLevel(defaultLevel) {
	}

	InitLevel(levels &startLevel) : storedLevel(startLevel){
	}
	operator levels() {
		return storedLevel;
	}
private:
	levels storedLevel;
};

static std::map<int, std::pair<InitLevel, StandardLogger*> > loggerMap;

class StandardLogger {
public:
	static levels getDefaultLevel() {
		return defaultLevel;
	}

	static void setDefaultLevel(levels newlevel) {
		defaultLevel = newlevel;
	}

	static int strhash(std::string name) {
		int ret = 0;
		char *ptr = reinterpret_cast<char *>(&ret);
		for (unsigned int i=0; i<name.size() ; ++i) {
			ptr[i%sizeof(int)] ^= name[i];
		}
		return ret;
	}

	levels getLevel() const {
		return loggerMap[this->hash].first;
	}

	static void setLogLevel(std::string name, levels level) {
		int hash = strhash(name);
		std::pair<InitLevel, StandardLogger*> elem = loggerMap[hash];
		loggerMap[hash] = std::pair<InitLevel, StandardLogger*>
				(level, elem.second);
	}

	void setLogLevel(levels level) {
		loggerMap[hash] = std::pair<InitLevel, StandardLogger*>
			(level, this);
	}

	static StandardLogger &getLogger(std::string s) {
		int hash = strhash(s);
		std::pair<InitLevel, StandardLogger*> elem = loggerMap[hash];
		StandardLogger *retlog;
		if (elem.second == 0) {
			retlog = new StandardLogger(s);
			loggerMap[hash] = std::pair<InitLevel, StandardLogger*>
				(elem.first, retlog);
			return *retlog;
		} else {
			return *(elem.second);
		}
	}

	void log(std::string s_) {
		cout << '[' << this->name << "]: " << s_ << std::endl;
	}

	const std::string &getName() const {
		return name;
	}

private:
	std::string name;
	int hash;
	StandardLogger(std::string s): name(s), hash(strhash(name)) {
	}
};

int main() {
	StandardLogger &logger = StandardLogger::getLogger("main");

	StandardLogger::setLogLevel("secondLogger", FATAL);

	StandardLogger &log2 = StandardLogger::getLogger("secondLogger");

	StandardLogger &log2bis = StandardLogger::getLogger("secondLogger");

	StandardLogger &logn = StandardLogger::getLogger("a_logger");

	StandardLogger &logA = StandardLogger::getLogger("loggerA");
	StandardLogger::setDefaultLevel(INFO);
	logA.setLogLevel(TRACE);
	StandardLogger &logB = StandardLogger::getLogger("loggerB");


	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	logger.log("This is a string and there is no magic");

	STDLOG_DEBUG(logger, "Hello! " << 1234 << 'c' << " this is " << &logger);
	STDLOG_DEBUG(log2, "Hello!");
	STDLOG_DEBUG(log2bis, "Hello without fooling!");
	STDLOG_DEBUG(logn, "Hello from n_th logger!");

	STDLOG_TRACE(logA, "AaA");
	STDLOG_DEBUG(logB, "BbB");


	return 0;
}
