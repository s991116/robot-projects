#include <FileLogger.h>
#include <Convert.h>

FileLogger::FileLogger(std::string filename) {
  _filename = filename;
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << "----Start logging----" << std::endl;
  _filestream.close();
}

void FileLogger::Log(std::string message) {
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << message << std::endl;
  _filestream.close();
}

void FileLogger::Log(float value) {
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << value << " ";
  _filestream.close();
}

void FileLogger::Log(int value) {
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << value << " ";
  _filestream.close();
}


void FileLogger::Log(std::string message, int value) {
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << message << ": " << value << std::endl;
  _filestream.close();
}

void FileLogger::Log(std::string message, float value)
{
  std::string strNumber = Convert::FloatToString(value);
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << message << ": " << strNumber << std::endl;
  _filestream.close();
} 

void FileLogger::Error(std::string message)
{
  _filestream.open(_filename.c_str(), std::ofstream::out | std::ofstream::app);
  _filestream << "ERROR: " << message << std::endl;
  _filestream.close();
}