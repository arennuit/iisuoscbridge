#include "Logger.h"

std::string Logger::sm_logLevelLabels[LOG_LEVELS_NUM] = 
{
	"Error",
	"Warning",
	"Info",
	"Debug"
};

//////////////////////////////////////////////////////////////////////////
std::ostringstream& Logger::Get(LogLevel level)
{
	m_outStream << "[" << sm_logLevelLabels[level] << "]: ";
	return m_outStream;
}

//////////////////////////////////////////////////////////////////////////
std::ostringstream& Logger::Get(LogLevel level, const char* file, int line)
{
	m_outStream << "[" << sm_logLevelLabels[level] << "] file " << file << " line " << line << " :";
	return m_outStream;
}

//////////////////////////////////////////////////////////////////////////
Logger::~Logger()
{
	m_outStream << std::endl;
	//fprintf(stderr, "%s", m_outStream.str().c_str());
	//fflush(stderr);
	std::clog << m_outStream.str();
}