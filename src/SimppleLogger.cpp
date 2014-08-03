#include "SimppleLogger.hpp"

namespace pplelog {

typedef std::pair<LevelTracker, SimppleLogger*> loggerElement_t;
typedef std::map<size_t, loggerElement_t> loggerMap_t;

static loggerMap_t globalLoggerMap;
static levels defaultLevel = DEBUG;

#if __cplusplus < 201103L

// We define an internal string hash function
static size_t strhash(const std::string &name) {
	int ret = 0;
	char *ptr = reinterpret_cast<char *>(&ret);
	for (unsigned int i=0; i<name.size() ; ++i) {
		ptr[i%sizeof(int)] ^= name[i];
	}
	return ret;
}

#else
#include <functional>

// We use the C++11 provided hash function
static std::hash<std::string> strhash;

#endif

LevelTracker::LevelTracker() :
		localLevel(defaultLevel), parent(NULL), assignedLevel(&defaultLevel) {
	// Empty constructor
}

void LevelTracker::setParent(LevelTracker &parent) {
	this->parent = &parent;
	this->assignedLevel = parent.assignedLevel;
	parent.children.push_back(this);
}

LevelTracker::operator levels() {
	return *assignedLevel;
}

void LevelTracker::setLevel(levels &changeLevel) {
	levels *oldLevel = this->assignedLevel;
	localLevel = changeLevel;
	levels *newLevel = &localLevel;
	assignedLevel = newLevel;
	for (std::vector<LevelTracker *>::iterator it = this->children.begin();
			it != this->children.end(); ++it) {
		(*it)->deepLevelChanger(oldLevel, newLevel);
	}
}

void LevelTracker::deepLevelChanger(levels *precursor, levels *future) {
	if (this->assignedLevel == precursor) {
		this->assignedLevel = future;
		for (std::vector<LevelTracker *>::iterator it = this->children.begin();
				it != this->children.end(); ++it) {
			(*it)->deepLevelChanger(precursor, future);
		}
	}
}

levels getDefaultLevel() {
	return defaultLevel;
}

void setDefaultLevel(levels newlevel) {
	defaultLevel = newlevel;
}

levels SimppleLogger::getLevel() const {
	return globalLoggerMap[this->hash].first;
}

static void setLogLevel(size_t hash, levels level) {
	loggerElement_t &elem = globalLoggerMap[hash];
	elem.first.setLevel(level);
}

void setLogLevel(std::string name, levels level) {
	int hash = strhash(name);
	setLogLevel(hash, level);
}

void SimppleLogger::setLogLevel(levels level) {
	pplelog::setLogLevel(this->hash, level);
}

SimppleLogger &getLogger(const std::string &s) {
	int hash = strhash(s);
	loggerElement_t &elem = globalLoggerMap[hash];
	SimppleLogger *retlog;
	if (elem.second == 0) {
		retlog = new SimppleLogger(s);
		globalLoggerMap[hash] = loggerElement_t(elem.first, retlog);
		return *retlog;
	} else {
		return *(elem.second);
	}
}

SimppleLogger &getLogger(const std::string &s, const std::string &parent) {
	SimppleLogger &retLogger = getLogger(s);
	retLogger.setParent(parent);
	return retLogger;
}

void SimppleLogger::setParent(size_t hash_base, size_t hash_parent) {
	loggerElement_t &elem_base = globalLoggerMap[hash_base];
	loggerElement_t &elem_parent = globalLoggerMap[hash_parent];

	elem_base.first.setParent(elem_parent.first);
}

void setParent(const std::string &base, const std::string &parent) {
	SimppleLogger::setParent(strhash(base), strhash(parent));
}

void SimppleLogger::setParent(const std::string &parent) {
	setParent(this->hash, strhash(parent));
}

void SimppleLogger::setParent(const SimppleLogger &parent) {
	setParent(this->hash, parent.hash);
}

void SimppleLogger::log(std::string s_) {
	std::cout << '[' << this->name << "]: " << s_ << std::endl;
}

const std::string &SimppleLogger::getName() const {
	return name;
}

SimppleLogger::SimppleLogger(const std::string &s): name(s), hash(strhash(s)) {
	// Unique private constructor, initializes internal values

	// Factory method should already have updated the static map
}

}; // namespace pplelog
