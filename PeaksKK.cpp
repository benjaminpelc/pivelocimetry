#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include "Peaks.h"

Peaks::Peaks() {

}

Peaks::Peaks(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> inputMatrix) {
	setMatrix(inputMatrix);
}

void PivEng::Peaks::setMatrix(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> inputMatrix) {
	mat = inputMatrix;
}

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> PivEng::Peaks::getMatrix() {
	return mat;
}

void PivEng::Peaks::findPeaks() {

	// temporary PivEng::Peak vector to store unsorted peaks
	std::vector<Peak> tempVec;
	double maxPeak = 0;

	// loop through each point in the matrix
	for (int i = 1; i < getMatrix().rows() - 1; i++) {
		for (int j = 1; j < getMatrix().cols() - 1; j++) {
			
			// check if point is a maximum
			if (
					getMatrix()(j,i) > getMatrix()(j,i - 1) &&
					getMatrix()(j,i) > getMatrix()(j,i + 1) &&
					getMatrix()(j,i) > getMatrix()(j - 1,i) &&
					getMatrix()(j,i) > getMatrix()(j + 1,i) 
				) {
				
				// Create a new peak structure and chuck the relevant bits in
				PivEng::Peak newPeak;
				newPeak.x_i = i;
				newPeak.y_j = j;
				newPeak.peakValue = getMatrix()(j,i);

				// Add the peak to the object peaks vector
				tempVec.push_back(newPeak);

				// How big is it
				if (getMatrix()(j,i) > maxPeak)
					maxPeak = getMatrix()(j,i);
			}
		}
	}

	while (maxPeakValue(tempVec) > 0) {
		for (int it = 0; it < tempVec.size(); it++) {
			if (tempVec[it].peakValue == maxPeakValue(tempVec) && tempVec[it].peakValue > 0) {
				peaks.push_back(tempVec[it]);
				tempVec[it].peakValue = 0;
			}
		}
	}
}

void PivEng::Peaks::printPeaks() {
	for (Peak i : peaks) {
		std::cout << "i: " << i.x_i << ", j: " << i.y_j << ", value: " << i.peakValue << std::endl;
	}
}

double PivEng::Peaks::maxPeakValue(std::vector<Peak> peakVec) {
	double mp = 0;
	for (Peak i : peakVec) {
		if (i.peakValue > mp)
			mp = i.peakValue;
	}

	return mp;
}

void PivEng::Peaks::gaussFit() {

	for (int it = 0; it < peaks.size(); it++) {

		int i = peaks[it].x_i;
		int j = peaks[it].y_j;

		double x0 = i + ( log(getMatrix()(j,i-1))-log(getMatrix()(j,i+1)) ) / ( 2*log(getMatrix()(j,i-1)) - 4*log(getMatrix()(j,i)) + 2*log(getMatrix()(j,i+1)) ) - getMatrix().cols()/2;
	    double y0 = j + ( log(getMatrix()(j-1,i))-log(getMatrix()(j+1,i)) ) / ( 2*log(getMatrix()(j-1,i)) - 4*log(getMatrix()(j,i)) + 2*log(getMatrix()(j+1,i)) ) - getMatrix().rows()/2;

	    PivEng::Displacement newDisp;
	    newDisp.u = x0;
	    newDisp.v = y0;

	    displacements.push_back(newDisp);

	    //std::cout << "u: " << x0 << ", v: " << y0 << std::endl;
	}
}

double PivEng::Peaks::getU() {
	return displacements[0].u;
}
double PivEng::Peaks::getV() {
	return displacements[0].v;
}
