#include "SettingFileReader.h"
#include <stdlib.h>
#include <fstream>

SettingFileReader::SettingFileReader(SettingReader* settingReader) {
  _SettingReader = settingReader;
}

SettingFileReader::~SettingFileReader() {
}

void SettingFileReader::UpdateSettings(std::string settingFilename, Setting* settings) {
 std::string line;

  std::ifstream scriptFile(settingFilename.c_str());
  if (scriptFile.is_open()) {
    while (getline(scriptFile, line)) {
        _SettingReader->Read(line, settings);
    }
  }
}