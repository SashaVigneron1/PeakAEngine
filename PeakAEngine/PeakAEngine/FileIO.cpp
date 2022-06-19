#include "PeakAEnginePCH.h"
#include "FileIO.h"



FileIO::FileIO(const std::string& filePath, bool useLogger)
	: m_FilePath{ filePath }
    , m_FileStream{  }
    , m_UseLogger{ useLogger }
{
    m_FileStream.open(m_FilePath, std::ios::in | std::ios::out);
    if (!m_FileStream.is_open())
	{
		if (m_UseLogger) Logger::LogError("[FileIO] Failed to open file: " + m_FilePath);

        if (m_UseLogger) Logger::LogWarning("[FileIO] Creating new file: " + m_FilePath);

		std::fstream fs;
        fs.open(m_FilePath, std::ios::out);
        fs.close();
	}
}

FileIO::~FileIO()
{
    m_FileStream.close();
}

void FileIO::WriteLine(const std::string& line)
{
    if (m_FileStream.is_open())
    {
        m_FileStream << line << std::endl;
    }
    else if (m_UseLogger) Logger::LogError("[FileIO] Unable to open file: " + m_FilePath);
}

std::string FileIO::ReadLine()
{
    std::string line;
    if (m_FileStream.is_open())
    {
        std::getline(m_FileStream, line);
    }
    return line;
}

void FileIO::DeleteAllLines()
{
    m_FileStream.close();
    std::remove(m_FilePath.c_str());

    // Create New File
    std::fstream fs;
    fs.open(m_FilePath, std::ios::out);
    fs.close();

    // Open Stream
    m_FileStream.open(m_FilePath, std::ios::in | std::ios::out);
}

void FileIO::ReturnToStart()
{
    m_FileStream.clear();
    m_FileStream.seekg(0);
}

void FileIO::ReOpenFile()
{
    m_FileStream.close();
    m_FileStream.open(m_FilePath, std::ios::in | std::ios::out);
}
