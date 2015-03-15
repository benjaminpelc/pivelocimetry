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
		void set_all(T a);
		void set_elem(int j, int i, T a);

		// GETTERS
		int get_numRows();
		int get_numCols();
		T get_elementAt(int j, int i);
		T get_max();
		T get_min();
		T get_sum();
		double get_average();
		double get_std(bool biased = false);

		// SCALE
		void scale(T scaleFactor);
		void transpose();

		// Overload the stream opp
		template <typename sT>
		friend std::ostream& operator<<(std::ostream& os, const Matrix2<sT>&mat);

	protected:
		T **_mat;
		int _m, _n;

	private:
		// Matrix dimensions (m x n) = (rows, cols)
		void allocate_array_memory(int a, int b);
};

// Default constructor
template<typename T>
Matrix2<T>::Matrix2() {}  //: _m(0), _n(0) {}

// Double arg constructor
template<typename T>
Matrix2<T>::Matrix2(int a, int b) : _m(a), _n(b)
{
	// Allocate the memory
	allocate_array_memory(a, b);
}

// Triple  arg constructor
template<typename T>
Matrix2<T>::Matrix2(int a, int b, T c) : _m(a), _n(b)
{
	// Allocate the memory
	allocate_array_memory(a, b);
	set_all(c);
}

// SETTER METHODS
template<typename T>
void Matrix2<T>::set_all(T a)
{
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			_mat[i][j] = a;
		}
	}
}

template<typename T>
void Matrix2<T>::set_elem(int j, int i, T c)
{
	_mat[j][i] = c;
}

// GETTER METHODS
template<typename T>
int Matrix2<T>::get_numRows()
{
	return _m;
}

template<typename T>
int Matrix2<T>::get_numCols()
{
	return _n;
}

// Get element at
template<typename T>
T Matrix2<T>::get_elementAt(int j, int i)
{
	return _mat[j][i];
}

// Get maximum value
template<typename T>
T Matrix2<T>::get_max()
{
	// Set max to first value in array
	T max = _mat[0][0];

	// Loop through all values replacing max if the value is greater
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			if (_mat[i][j] > max) {
				max = _mat[i][j];
			}
		}
	}
	return max;
}

// Get minimum value
template<typename T>
T Matrix2<T>::get_min()
{
	// Set min to first value in array
	T min = _mat[0][0];

	// Loop through all values replacing minimum if the value is greater
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			if (_mat[i][j] < min) {
				min = _mat[i][j];
			}
		}
	}
	return min;
}

// Get the matrix sum
template<typename T>
T Matrix2<T>::get_sum()
{
	T sum = 0;
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			sum += _mat[i][j];
		}
	}
	return sum;
}

// Return the average value of the array
template<typename T>
double Matrix2<T>::get_average()
{
	return (double) get_sum() / (double) (_m * _n);
}

template<typename T>
double Matrix2<T>::get_std(bool biased)
{
	double avg = get_average();
	double std = 0.0;
	double deviation;

	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			deviation = (double) _mat[i][j] - avg;
			std += deviation * deviation;
		}
	}
	std /= biased ? (double) (_m * _n - 1) : (double) (_m * _n);
	return sqrt(std);
}

// destructor
template<typename T>
Matrix2<T>::~Matrix2() {
	for (int i = 0; i < _m; i++)
	{
		delete[] _mat[i];
	}
	delete[] _mat;
}

// SCALE 
template<typename T>
void Matrix2<T>::scale(T scaleFactor)
{
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			_mat[i][j] = _mat[i][j] * scaleFactor;
		}
	}
}

template<typename T>
void Matrix2<T>::transpose()
{
	// Allocate temporary array	nxm array and transpose original contents over
	T** tmp = new T*[_n];
	for (int i = 0; i < _n; i++) {
		tmp[i] = new T[_m];
		for (int j = 0; j < _m; j++) {
			tmp[i][j] = _mat[j][i];
		}
	}

	// Delete the original _mat 
	for (int i = 0; i < _m; i++) {
		delete[] _mat[i];
	} delete[] _mat;

	// Copy the contents over 
	_mat = new T*[_n];
	for (int i = 0; i < _n; i++) {
		_mat[i] = new T[_m];
		for (int j = 0; j < _m; j++) {
			_mat[i][j] = tmp[i][j];
		} delete[] tmp[i];
	} delete[] tmp;

	// Swap the internal row and column counts 
	int tmpI = _m;
	_m = _n;
	_n = tmpI;
}

template<typename sT>
std::ostream& operator<<(std::ostream& os, const Matrix2<sT>& mat)
{
	for (int i = 0; i < mat._m; i++) {
		for (int j = 0; j < mat._n; j++) {
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
