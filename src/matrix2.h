#ifndef MATRIX2_H
#define MATRIX2_H

#include <iostream>
#include <math.h>

template<typename T>
class Matrix2
{
	public:
		Matrix2();
		// Matrix2();
		Matrix2(int a, int b);
		Matrix2(int a, int b, T c);

		~Matrix2();
		
		// SETTERS
		void all(T a);
		void setElem(int j, int i, T a);

		// GETTERS
		int rows();
		int cols();
		int size();
		T getElem(int idx);
		T getElem(int j, int i);
		T max();
		T min();
		T sum();
		double mean();
		double stdev(bool biased = false);

		// SCALE
		void scale(T scaleFactor);
		void transpose();

		// Overload the stream opp
		template <typename sT>
		friend std::ostream& operator<<(std::ostream& os, const Matrix2<sT>&mat);

	protected:
		T **_mat;
		int _rows, _cols;

	private:
		// Matrix dimensions (m x n) = (rows, cols)
		void allocate_array_memory(int a, int b);
};

// Default constructor
template<typename T>
Matrix2<T>::Matrix2() {}  //: _rows(0), _cols(0) {}

// Double arg constructor
template<typename T>
Matrix2<T>::Matrix2(int a, int b) : _rows(a), _cols(b)
{
	// Allocate the memory
	allocate_array_memory(a, b);
}

// Triple  arg constructor
template<typename T>
Matrix2<T>::Matrix2(int a, int b, T c) : _rows(a), _cols(b)
{
	// Allocate the memory
	allocate_array_memory(a, b);
	all(c);
}

// SETTER METHODS
template<typename T>
void Matrix2<T>::all(T a)
{
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			_mat[i][j] = a;
		}
	}
}

template<typename T>
void Matrix2<T>::setElem(int j, int i, T c)
{
	_mat[j][i] = c;
}

// GETTER METHODS

template<typename T>
T Matrix2<T>::getElem(int idx)
{
	/* Return the ith element which is equal to 
	 * */
	return *_mat[idx];
}

template<typename T>
int Matrix2<T>::rows()
{
	return _rows;
}

template<typename T>
int Matrix2<T>::cols()
{
	return _cols;
}

template<typename T>
int Matrix2<T>::size()
{
	return _cols * _rows;
}

// Get element at
template<typename T>
T Matrix2<T>::getElem(int j, int i)
{
	return _mat[j][i];
}

// Get maximum value
template<typename T>
T Matrix2<T>::max()
{
	// Set max to first value in array
	T max = _mat[0][0];

	// Loop through all values replacing max if the value is greater
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			if (_mat[i][j] > max) {
				max = _mat[i][j];
			}
		}
	}
	return max;
}

// Get minimum value
template<typename T>
T Matrix2<T>::min()
{
	// Set min to first value in array
	T min = _mat[0][0];

	// Loop through all values replacing minimum if the value is greater
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			if (_mat[i][j] < min) {
				min = _mat[i][j];
			}
		}
	}
	return min;
}

// Get the matrix sum
template<typename T>
T Matrix2<T>::sum()
{
	T sum = 0;
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			sum += _mat[i][j];
		}
	}
	return sum;
}

// Return the average value of the array
template<typename T>
double Matrix2<T>::mean()
{
	return (double) sum() / (double) (_rows * _cols);
}

template<typename T>
double Matrix2<T>::stdev(bool biased)
{
	double avg = mean();
	double std = 0.0;
	double deviation;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			deviation = (double) _mat[i][j] - avg;
			std += deviation * deviation;
		}
	}
	std /= biased ? (double) (_rows * _cols - 1) : (double) (_rows * _cols);
	return sqrt(std);
}

// destructor
template<typename T>
Matrix2<T>::~Matrix2() {
	for (int i = 0; i < _rows; i++)
	{
		delete[] _mat[i];
	}
	delete[] _mat;
}

// SCALE 
template<typename T>
void Matrix2<T>::scale(T scaleFactor)
{
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			_mat[i][j] = _mat[i][j] * scaleFactor;
		}
	}
}

template<typename T>
void Matrix2<T>::transpose()
{
	// Allocate temporary array	nxm array and transpose original contents over
	T** tmp = new T*[_cols];
	for (int i = 0; i < _cols; i++) {
		tmp[i] = new T[_rows];
		for (int j = 0; j < _rows; j++) {
			tmp[i][j] = _mat[j][i];
		}
	}

	// Delete the original _mat 
	for (int i = 0; i < _rows; i++) {
		delete[] _mat[i];
	} delete[] _mat;

	// Copy the contents over 
	_mat = new T*[_cols];
	for (int i = 0; i < _cols; i++) {
		_mat[i] = new T[_rows];
		for (int j = 0; j < _rows; j++) {
			_mat[i][j] = tmp[i][j];
		} delete[] tmp[i];
	} delete[] tmp;

	// Swap the internal row and column counts 
	int tmpI = _rows;
	_rows = _cols;
	_cols = tmpI;
}

template<typename sT>
std::ostream& operator<<(std::ostream& os, const Matrix2<sT>& mat)
{
	for (int i = 0; i < mat._rows; i++) {
		for (int j = 0; j < mat._cols; j++) {
			os << mat._mat[i][j] << "\t";
		}
		os << "\n";
	}
	return os;
}

template<typename T>
void Matrix2<T>::allocate_array_memory(int a, int b)
{
	_mat = new T*[a];
	for (int i = 0; i < a; i++)
	{
		_mat[i] = new T[b];
	}

}

#endif
