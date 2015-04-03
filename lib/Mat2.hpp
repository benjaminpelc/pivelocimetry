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
		Mat2(const unsigned int rows, const unsigned int cols);
		Mat2(const unsigned int rows, const unsigned int cols, const T v);
		~Mat2();

		/* Copy constructor */
		Mat2(const Mat2<T>& m);

		/* Index axxess */
		T& operator[](const int i) const { return m_mat[i]; };

		T getElem(const int idx);
		T getElem(const int j, const int i);

		constexpr int size() { return m_size; };
		constexpr int rows() { return m_rows; };
		constexpr int cols() { return m_cols; };
		int getIndex(const int j, const int i);
		
		void setElem(const int j, const int i, const T v);
		void setElem(const int idx, const T v);

		constexpr T* begin() { return &m_mat[0]; };
		constexpr T* end () { return &m_mat[m_size]; };

	protected:
		T* m_mat;
		T* m_begin;
		T* m_end;
		int m_size;
		int m_rows, m_cols;
	
	private:
};

template<typename T>
Mat2<T>::Mat2(const unsigned int rows, const unsigned int cols) :
	m_size(rows * cols),
	m_rows(rows),
	m_cols(cols)
{
	/* Constructor, must provide the number of rows, number of 
	 * columns and an initial value */
	m_mat = new T[m_size]{0};
}

template<typename T>
Mat2<T>::Mat2(const unsigned int rows, const unsigned int cols, const T v) :
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
Mat2<T>::Mat2(const Mat2<T>& m) :
	m_mat(new T[m.size()]),
	m_size(m.size()),
	m_rows(m.rows()),
	m_cols(m.cols())
{
	// m_mat = new T[m_size];
	for(size_t i = 0; i != m_size; i ++) {
		m_mat[i] = m[i];
	}
};

template<typename T>
T Mat2<T>::getElem(const int idx)
{
	/* Return element with linear index, this 
	 * will be fastest */
	return m_mat[idx];
}

template<typename T>
T Mat2<T>::getElem(const int j, const int i)
{
	/* Return element with 2D index */
	// return m_mat[m_cols * j + i];
	return *(m_begin + m_cols * j + i);
}

template<typename T>
void Mat2<T>::setElem(const int j, const int i, const T v)
{
	/* Set element with 2D index */
	// m_mat[m_cols * j + i] = v;
	*(m_begin + m_cols * j + i) = v;
}

template<typename T>
void Mat2<T>::setElem(const int idx, const T v)
{
	m_mat[idx] = v;
}

template<typename T>
int Mat2<T>::getIndex(const int j, const int i)
{
	return m_cols * j + i;
}

template<typename T>
Mat2<T>::~Mat2() { delete[] m_mat; }

#endif
