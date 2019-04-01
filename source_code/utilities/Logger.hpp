#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>
#include <string.h>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

/* Modify the values inside of the REG call below to add/remove Logger levels */
#define LEVEL_VALUES REG_LVL(Finest)REG_LVL(Finer)REG_LVL(Fine)REG_LVL(Summary)REG_LVL(Warning)REG_LVL(Error)REG_LVL(Severe)

#define REG_LVL(x) x,
enum LoggerLevels { LEVEL_VALUES };
#undef REG_LVL

#define REG_LVL(x) #x,
const char * const LoggerLevelNames[] { LEVEL_VALUES };
#undef REG_LVL

#undef LEVEL_VALUES

#define __FILENAME__ strrchr("/" __FILE__, '/') + 1
#define LOG(message, logger_level) log(message, logger_level, __FILENAME__, __LINE__)


bool log(std::string message, LoggerLevels level, const char * file, int lineNumber);

/*
  Only messages logged above or equal to the currently set level will be logged to
  their respective places.
*/
extern LoggerLevels loggerConsoleLoggingLevel;
extern LoggerLevels loggerFileLoggingLevel;

#endif /* Logger_hpp */
