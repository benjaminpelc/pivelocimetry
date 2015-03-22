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
		T **m_mat;
		int m_rows, m_cols;

	private:
		// Matrix dimensions (m x n) = (rows, cols)
		void allocate_array_memory(int a, int b);
};

// Default constructor
template<typename T>
Matrix2<T>::Matrix2() {}  //: m_rows(0), m_cols(0) {}

// Double arg constructor
template<typename T>
Matrix2<T>::Matrix2(int a, int b) : m_rows(a), m_cols(b)
{
	// Allocate the memory
	allocate_array_memory(a, b);
}

// Triple  arg constructor
template<typename T>
Matrix2<T>::Matrix2(int a, int b, T c) : m_rows(a), m_cols(b)
{
	// Allocate the memory
	allocate_array_memory(a, b);
	all(c);
}

// SETTER METHODS
template<typename T>
void Matrix2<T>::all(T a)
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			m_mat[i][j] = a;
		}
	}
}

template<typename T>
void Matrix2<T>::setElem(int j, int i, T c)
{
	m_mat[j][i] = c;
}

// GETTER METHODS

template<typename T>
T Matrix2<T>::getElem(int idx)
{
	/* Return the ith element which is equal to 
	 * */
	return *m_mat[idx];
}

template<typename T>
int Matrix2<T>::rows()
{
	return m_rows;
}

template<typename T>
int Matrix2<T>::cols()
{
	return m_cols;
}

template<typename T>
int Matrix2<T>::size()
{
	return m_cols * m_rows;
}

// Get element at
template<typename T>
T Matrix2<T>::getElem(int j, int i)
{
	return m_mat[j][i];
}

// Get maximum value
template<typename T>
T Matrix2<T>::max()
{
	// Set max to first value in array
	T max = m_mat[0][0];

	// Loop through all values replacing max if the value is greater
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_mat[i][j] > max) {
				max = m_mat[i][j];
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
	T min = m_mat[0][0];

	// Loop through all values replacing minimum if the value is greater
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_mat[i][j] < min) {
				min = m_mat[i][j];
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
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			sum += m_mat[i][j];
		}
	}
	return sum;
}

// Return the average value of the array
template<typename T>
double Matrix2<T>::mean()
{
	return (double) sum() / (double) (m_rows * m_cols);
}

template<typename T>
double Matrix2<T>::stdev(bool biased)
{
	double avg = mean();
	double std = 0.0;
	double deviation;

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			deviation = (double) m_mat[i][j] - avg;
			std += deviation * deviation;
		}
	}
	std /= biased ? (double) (m_rows * m_cols - 1) : (double) (m_rows * m_cols);
	return sqrt(std);
}

// destructor
template<typename T>
Matrix2<T>::~Matrix2() {
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_mat[i];
	}
	delete[] m_mat;
}

// SCALE 
template<typename T>
void Matrix2<T>::scale(T scaleFactor)
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			m_mat[i][j] = m_mat[i][j] * scaleFactor;
		}
	}
}

template<typename T>
void Matrix2<T>::transpose()
{
	// Allocate temporary array	nxm array and transpose original contents over
	T** tmp = new T*[m_cols];
	for (int i = 0; i < m_cols; i++) {
		tmp[i] = new T[m_rows];
		for (int j = 0; j < m_rows; j++) {
			tmp[i][j] = m_mat[j][i];
		}
	}

	// Delete the original m_mat 
	for (int i = 0; i < m_rows; i++) {
		delete[] m_mat[i];
	} delete[] m_mat;

	// Copy the contents over 
	m_mat = new T*[m_cols];
	for (int i = 0; i < m_cols; i++) {
		m_mat[i] = new T[m_rows];
		for (int j = 0; j < m_rows; j++) {
			m_mat[i][j] = tmp[i][j];
		} delete[] tmp[i];
	} delete[] tmp;

	// Swap the internal row and column counts 
	int tmpI = m_rows;
	m_rows = m_cols;
	m_cols = tmpI;
}

template<typename sT>
std::ostream& operator<<(std::ostream& os, const Matrix2<sT>& mat)
{
	for (int i = 0; i < mat.m_rows; i++) {
		for (int j = 0; j < mat.m_cols; j++) {
			os << mat.m_mat[i][j] << "\t";
		}
		os << "\n";
	}
	return os;
}

template<typename T>
void Matrix2<T>::allocate_array_memory(int a, int b)
{
	m_mat = new T*[a];
	for (int i = 0; i < a; i++)
	{
		m_mat[i] = new T[b];
	}

}

#endif
