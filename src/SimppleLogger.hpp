#ifndef SIMPPLELOGGER_HPP_
#define SIMPPLELOGGER_HPP_

// Required by the macro, forcing it in the include header
#include <sstream>
#include <map>
#include <vector>

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

/**
Logs a message to a specified logger with the TRACE level.

@param logger the logger to be used.
@param message the message string to log.
*/
#define STDLOG_INFO(logger, message) { \
        if (logger.getLevel() <= pplelog::INFO) {\
           std::ostringstream oss_; \
           oss_ << "INFO " message; \
           logger.log(oss_.str()); }}


namespace pplelog {

/**
 * List of possible levels associated to a logger
 */
enum levels{
	ALWAYS_LOG = -5,
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
void setLogLevel(const std::string &name, levels level);
void setParent(const std::string &base, const std::string &parent);
SimppleLogger &getLogger(const std::string &s);
SimppleLogger &getLogger(const std::string &s, const std::string &parent);

}; // namespace pplelog

class pplelog::LevelTracker {
public:
	LevelTracker();
	void setParent(LevelTracker &parent);
	operator levels();
	void setLevel(levels &changeLevel);
private:
	void deepLevelChanger(levels *precursor, levels *future);
	levels localLevel;
	LevelTracker *parent;
	levels *assignedLevel;
	std::vector<LevelTracker *> children;
};

class pplelog::SimppleLogger {
public:
	levels getLevel() const;
	void setLogLevel(levels level);
	void log(std::string s_);
	const std::string &getName() const;

	void setParent(const std::string &parent);
	void setParent(const SimppleLogger &parent);


private:
	std::string name;
	size_t hash;
	SimppleLogger(const std::string &s);
	~SimppleLogger();

	static void setParent(size_t hash_base, size_t hash_parent);

// Friends
	friend levels getDefaultLevel();
	friend void setDefaultLevel(levels newlevel);
	friend void setLogLevel(const std::string name, levels level);
	friend SimppleLogger &getLogger(const std::string &s);
	friend SimppleLogger &getLogger(const std::string &s, const std::string &parent);
	friend void setParent(const std::string &base, const std::string &parent);
};

#endif /* SIMPPLELOGGER_HPP_ */
