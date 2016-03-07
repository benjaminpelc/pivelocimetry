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
  int winWidth();
  int winHeight();
  int olvpHoriz();
  int olvpVert();
  int numPeaks();
  int maxDispX();
  int maxDispY();
  std::pair<int, int> &winSize();

  // Setters
  void setWinWidth(int x);
  void setWinHeight(int x);
  void setOvlpHoriz(int x);
  void setOvlpVert(int x);
  void setNumPeaks(int n);

  // Print in console
  void print();

private:
  // Properties
  int m_noPeaks;
  std::pair<int, int> m_overlap;
  std::pair<int, int> m_winSize;
  std::pair<int, int> m_maxDisp;
  int findColon(const std::string &str);

  static int
  keyExistsToInt(std::unordered_map<std::string, std::string> &optMap,
                 std::string key, int defaultVal);
};
#endif
