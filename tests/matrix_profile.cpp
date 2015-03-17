#include "../src/matrix2.h"
#include "Mat2.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char** argv)
{
	std::cout << "Hello" << std::endl;	

	/* Set matrix size (in this case replicate 17 x 17 pix 
	 * correlation functions */
	int rows = 17, cols = 17;

	/* Instantiate a vector with N matrices */
	int N = 10000;
	std::vector<Matrix2<double>& > matVec(N, Matrix2<double>(rows, cols));
	// std::vector<Mat2<double>* > matVec(N, new Mat2<double>(rows, cols));

	double pi = 3.1415;
	int counter = 0;
	/* set all values to multiple of pi */
	for (int n = 0; n < N; n++) {
		for (int j = 0; j < rows; j++) {
			for (int i = 0; i < cols; i++) {
				matVec[n].setElem(j, i, pi * double(counter++));
			}
		}
		counter = 0;
	}

	// delete[] &matVec;

	std::cout << "Length of matrix vector: " << matVec.size() << std::endl;

	return 0;
}
