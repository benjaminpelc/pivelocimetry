/* Class Mat2
 *
 * Implementation using single block of memory
 */

#ifndef MAT2_H
#define MAT2_H

#include <iostream>
#include <memory>

template<typename T>
class Mat2
{
	public:
		Mat2(unsigned int rows, unsigned int cols);
		Mat2(unsigned int rows, unsigned int cols, T v);
		~Mat2();

		T getElem(int idx);
		T getElem(int j, int i);

		int size();
		int rows();
		int cols();
		int getIndex(int j, int i);
		
		void setElem(int j, int i, T v);
		void setElem(int idx, T v);

		T* begin() { return &m_mat[0]; };
		T* end () { return &m_mat[m_size]; };

	protected:
		T* m_mat;
		T* m_begin;
		T* m_end;
		int m_size;
		int m_rows, m_cols;
	
	private:
};

template<typename T>
Mat2<T>::Mat2(unsigned int rows, unsigned int cols) :
	m_size(rows * cols),
	m_rows(rows),
	m_cols(cols)
{
	/* Constructor, must provide the number of rows, number of 
	 * columns and an initial value */
	m_mat = new T[m_size]{0};
}

template<typename T>
Mat2<T>::Mat2(unsigned int rows, unsigned int cols, T v) :
	m_size(rows * cols),
	m_rows(rows),
	m_cols(cols)
{
	/* Constructor, must provide the number of rows, number of 
	 * columns and an initial value */
	m_mat = new T[m_size];
	std::fill(m_mat, m_mat + m_size, v);
}

template<typename T>
T Mat2<T>::getElem(int idx)
{
	/* Return element with linear index, this 
	 * will be fastest */
	return m_mat[idx];
}

template<typename T>
T Mat2<T>::getElem(int j, int i)
{
	/* Return element with 2D index */
	// return m_mat[m_cols * j + i];
	return *(m_begin + m_cols * j + i);
}

template<typename T>
void Mat2<T>::setElem(int j, int i, T v)
{
	/* Set element with 2D index */
	// m_mat[m_cols * j + i] = v;
	*(m_begin + m_cols * j + i) = v;
}

template<typename T>
void Mat2<T>::setElem(int idx, T v)
{
	m_mat[idx] = v;
}

template<typename T>
int Mat2<T>::size()
{
	return m_size;
}

template<typename T>
int Mat2<T>::rows()
{
	return m_rows;
}

template<typename T>
int Mat2<T>::cols()
{
	return m_cols;
}

template<typename T>
int Mat2<T>::getIndex(int j, int i)
{
	return m_cols * j + i;
}

template<typename T>
Mat2<T>::~Mat2() { delete[] m_mat; }

#endif
