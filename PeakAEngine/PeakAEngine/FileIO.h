#pragma once

#include <fstream>

class FileIO final
{
public:
	FileIO(const std::string& inputFilePath, bool useLogger = true);
	~FileIO();

	FileIO(const FileIO& other) = delete;
	FileIO(FileIO&& other) noexcept = delete;
	FileIO& operator=(const FileIO& other) = delete;
	FileIO& operator=(FileIO&& other) noexcept = delete;

	void WriteLine(const std::string& line);
	std::string ReadLine();
	void DeleteAllLines();
	void ReturnToStart();
	void ReOpenFile();
private:
	bool m_UseLogger;
	std::string m_FilePath;
	std::fstream m_FileStream;
};

