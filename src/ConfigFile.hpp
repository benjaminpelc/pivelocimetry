/* Class ConfigFile
 *
 * Static function class for config file operations
 * */

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <fstream>
#include <iostream>
#include <unordered_map>

class ConfigFile {
public:
  // ConfigFile();
  // ~ConfigFile();
  static std::unordered_map<std::string, std::string>
  parse(const std::string fn);

private:
  static int findColon(const std::string &str);
};

int ConfigFile::findColon(const std::string &str) {
  /* 	findColon
   *	returns the location of the first colon in the string */
  int colon = str.find_first_of(":");
  return colon > 0 ? colon : 0;
}

std::unordered_map<std::string, std::string>
ConfigFile::parse(const std::string fn) {
  /* Load the config file, ignore blank lines and comment lines
   * and return a map of key:value string pairs */
  std::ifstream configFile(fn);
  std::string line, k, v;
  std::unordered_map<std::string, std::string> keyValues;

  while (std::getline(configFile, line)) {
    // Ignore blank lines and comments, make sure there is a colon in the string
    int splitPoint = findColon(line);
    if (!line.empty() && line[0] != '#' && splitPoint) {
      // Now place the key:values in the map
      k = line.substr(0, splitPoint);
      v = line.substr(splitPoint + 1, line.length());
      keyValues[k] = v;
    }
  }
  configFile.close();
  return keyValues;
}

#endif
