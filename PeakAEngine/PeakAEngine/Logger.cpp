#include "PeakAEnginePCH.h"
#include "Logger.h"

Logger::ConsoleColor Logger::defaultColor = Logger::ConsoleColor::White;
FileIO Logger::m_FileIO = FileIO("Log.txt", false);
