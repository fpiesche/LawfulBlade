#include <cstdlib>
#include <fstream>
#include <sstream>

#include "unseallog.h"

std::ofstream m_logFs;
int m_logLevel = UNSEAL_LOG_LEVEL_NONE;

void UnsealLog(const std::string& message, const std::string& heading, int level)
{
    // Don't log anything when we're not allow
    if (level <= m_logLevel || !m_logFs.is_open())
        return;

    m_logFs << "<[" << heading << "]> " << message << std::endl;
}

void UnsealLoggerInit(int logLevel)
{
    if (logLevel == UNSEAL_LOG_LEVEL_NONE)
        return;

    char* log_file_name = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&log_file_name, &sz, "UNSEALER_LOG_FILE") == 0 && log_file_name != nullptr) {
    	m_logFs.open(log_file_name);
    }
    else {
    	m_logFs.open("unsealer.log");
    }
    m_logLevel = logLevel;
}

void UnsealLoggerKill()
{
    if (!m_logFs.is_open())
        return;

    m_logFs.flush();
    m_logFs.close();
}