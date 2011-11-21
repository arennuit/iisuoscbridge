#pragma once

#include <iostream>
#include <sstream>

//////////////////////////////////////////////////////////////////////////
enum LogLevel
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,

	LOG_LEVELS_NUM
};

#define SK_LOGGER(level)\
	Logger().Get(level)

#define SK_LOGGER_EXTRA(level)\
	Logger().Get(level, __FILE__, __LINE__)

//////////////////////////////////////////////////////////////////////////
/// \brief Simple application logger.
class Logger
{
public:
	Logger() {}
	virtual ~Logger();
	std::ostringstream& Get(LogLevel level);
	std::ostringstream& Get(LogLevel level, const char* file, int line);

protected:

	static std::string sm_logLevelLabels[];

	std::ostringstream m_outStream;

	//Logger(const Logger&);
	//Logger& operator =(const Logger&);
};
