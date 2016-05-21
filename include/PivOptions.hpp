// PivOptions.hpp
// Header for PivOptions class. Container class for PIV analysis options.
// Either loads options from file, applies default options or acccepts a map of
// key value pairs.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef PIV_OPTIONS_H
#define PIV_OPTIONS_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <cmath>

class PivOptions {
public:
  typedef std::unique_ptr<PivOptions> Uptr;
  typedef std::unordered_map<int, int> WinSizePair;

  PivOptions();
  PivOptions(std::string fn);
  PivOptions(std::unordered_map<std::string, std::string> optionMap);
  ~PivOptions();

  // Getters
  int winWidth() const;
  int winHeight() const;
  int olvpHoriz() const;
  int olvpVert() const;
  int numPeaks() const;
  int maxDispX() const;
  int maxDispY() const;
  std::pair<int, int> &winSize();

  // Setters
  void setWinWidth(const int x);
  void setWinHeight(const int x);
  void setOvlpHoriz(const int x);
  void setOvlpVert(const int x);
  void setNumPeaks(const int n);

  // Print in console
  void print() const;

private:
  // Properties
  int m_noPeaks;
  std::pair<int, int> m_overlap;
  std::pair<int, int> m_winSize;
  std::pair<int, int> m_maxDisp;
  int findColon(const std::string &str);

  static int
  keyExistsToInt(std::unordered_map<std::string, std::string> &optMap,
                 const std::string key, const int defaultVal);
};
#endif
