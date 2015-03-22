#ifndef PIV_OPTIONS_H
#define PIV_OPTIONS_H

#include <iostream>
#include <map>
#include <memory>
#include <cmath>

class PivOptions
{
	public:
		typedef std::unique_ptr<PivOptions> Uptr;
		typedef std::map<int, int> WinSizePair;
			
		PivOptions();
		PivOptions(std::map<std::string, std::string> optionMap);
		~PivOptions();

		// Getters
		int winWidth();
		int winHeight();
		int olvpHoriz();
		int olvpVert();
		int numPeaks();
		int maxDispX();
		int maxDispY();
		std::pair<int, int>& winSize();

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
		int _winWidth,
			_winHeight,
			_ovlpHoriz,
			_ovlpVert,
			_noPeaks;
		std::pair<int, int> _winSize;
		std::pair<int, int> _maxDisp;

		static int keyExistsToInt(std::map<std::string, std::string>& optMap, std::string key, int defaultVal);
};
#endif
