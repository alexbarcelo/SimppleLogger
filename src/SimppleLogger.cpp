#include "SimppleLogger.hpp"

namespace pplelog {

static std::map<int, std::pair<LevelTracker, SimppleLogger*> > loggerMap;
static levels defaultLevel = DEBUG;

int strhash(std::string name) {
	int ret = 0;
	char *ptr = reinterpret_cast<char *>(&ret);
	for (unsigned int i=0; i<name.size() ; ++i) {
		ptr[i%sizeof(int)] ^= name[i];
	}
	return ret;
}


LevelTracker::LevelTracker() : storedLevel(defaultLevel) {
	// Empty constructor
}

LevelTracker::LevelTracker(levels &startLevel) : storedLevel(startLevel){
	// Empty constructor
}

LevelTracker::operator levels() {
	return storedLevel;
}

levels getDefaultLevel() {
	return defaultLevel;
}

void setDefaultLevel(levels newlevel) {
	defaultLevel = newlevel;
}

levels SimppleLogger::getLevel() const {
	return loggerMap[this->hash].first;
}

void setLogLevel(std::string name, levels level) {
	int hash = strhash(name);
	std::pair<LevelTracker, SimppleLogger*> elem = loggerMap[hash];
	loggerMap[hash] = std::pair<LevelTracker, SimppleLogger*>
			(level, elem.second);
}

void SimppleLogger::setLogLevel(levels level) {
	loggerMap[hash] = std::pair<LevelTracker, SimppleLogger*>
		(level, this);
}

SimppleLogger &getLogger(std::string s) {
	int hash = strhash(s);
	std::pair<LevelTracker, SimppleLogger*> elem = loggerMap[hash];
	SimppleLogger *retlog;
	if (elem.second == 0) {
		retlog = new SimppleLogger(s); // elem.first also!
		loggerMap[hash] = std::pair<LevelTracker, SimppleLogger*>
			(elem.first, retlog);
		return *retlog;
	} else {
		return *(elem.second);
	}
}

void SimppleLogger::log(std::string s_) {
	std::cout << '[' << this->name << "]: " << s_ << std::endl;
}

const std::string &SimppleLogger::getName() const {
	return name;
}

SimppleLogger::SimppleLogger(std::string s): name(s), hash(strhash(name)) {
	// Unique private constructor, initializes internal values

	// Factory method should already have updated the static map
}

}; // namespace pplelog
