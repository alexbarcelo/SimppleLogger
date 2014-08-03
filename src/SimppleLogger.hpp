#ifndef SIMPPLELOGGER_HPP_
#define SIMPPLELOGGER_HPP_

// Required by the macro, forcing it in the include header
#include <sstream>
#include <map>

#include <iostream>

/**
Logs a message to a specified logger with the TRACE level.

@param logger the logger to be used.
@param message the message string to log.
*/
#define STDLOG_TRACE(logger, message) { \
        if (logger.getLevel() <= pplelog::TRACE) {\
           std::ostringstream oss_; \
           oss_ << "TRACE " message; \
           logger.log(oss_.str()); }}

/**
Logs a message to a specified logger with the DEBUG level.

@param logger the logger to be used.
@param message the message string to log.
*/
#define STDLOG_DEBUG(logger, message) { \
        if (logger.getLevel() <= pplelog::DEBUG) {\
           std::ostringstream oss_; \
           oss_ << "DEBUG " << message; \
           logger.log(oss_.str()); }}


namespace pplelog {

/**
 * List of possible levels associated to a logger
 */
enum levels{
	TRACE,
	DEBUG = 0,
	INFO,
	WARN,
	ERROR,
	FATAL,
	NEVER_LOG = 1000
};

class LevelTracker;
class SimppleLogger;

levels getDefaultLevel();
void setDefaultLevel(levels newlevel);
void setLogLevel(std::string name, levels level);
SimppleLogger &getLogger(std::string s);
}; // namespace pplelog

class pplelog::LevelTracker {
public:
	LevelTracker();
	LevelTracker(levels &startLevel);
	operator levels();
private:
	levels storedLevel;
//	LevelTracker &assignedLevel;
};

class pplelog::SimppleLogger {
public:
	levels getLevel() const;
	void setLogLevel(levels level);
	void log(std::string s_);
	const std::string &getName() const;

private:
	std::string name;
	int hash;
	SimppleLogger(std::string s);
	~SimppleLogger();

// Friends
	friend levels getDefaultLevel();
	friend void setDefaultLevel(levels newlevel);
	friend void setLogLevel(std::string name, levels level);
	friend SimppleLogger &getLogger(std::string s);
};



#endif /* SIMPPLELOGGER_HPP_ */
