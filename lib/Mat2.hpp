/* Class Mat2
 *
 * Implementation using single block of memory
 */

#ifndef MAT2_H
#define MAT2_H

#include <iostream>
#include <memory>
#include <numeric>

template<typename T>
class Mat2
{
	public:
		/* Constructors:
		 * Provide dimensions and an initial value or just dimenstions */
		Mat2(const unsigned int rows, const unsigned int cols);
		Mat2(const unsigned int rows, const unsigned int cols, const T v);

		/* Destructor */
		~Mat2();

		/* Copy constructor */
		Mat2(const Mat2<T>& m);
		/* Copy assign */
		Mat2<T>& operator=(const Mat2<T>& a);

		/* Move constructor */
		Mat2(Mat2<T>&& m);
		/* Move assign */
		Mat2<T>& operator=(Mat2<T>&& other);

		/* Equality */
		bool operator==(const Mat2<T>& other ) const;
		bool operator!=(const Mat2<T>& other ) const;

		// bool operator< (const Mat2<T>& rhs) const;
		/* Access elements
		 * 1) subscript index access
		 * 2) method call with subscript access 
		 * 3) method call with coordinate access */
		T& operator[](const int i) const { return m_mat[i]; };
		T getElem(const int idx) const { return m_mat[idx]; };
		T getElem(const int j, const int i) const { return m_mat[m_cols * j + i]; };

		/* Return the linear index from 2D matrix coordinates */
		int getIndex(const int j, const int i) const;

		/* Access matrix dimension information */
		constexpr int size() const { return m_size; };
		constexpr int rows() const { return m_rows; };
		constexpr int cols() const { return m_cols; };
		
		/* Set element method, use if can't use index notation [] */
		void setElem(const int j, const int i, const T v);
		void setElem(const int idx, const T v);

		/* Pointers to first and one past last elements */
		constexpr T* begin() const { return &m_mat[0]; };
		constexpr T* end () const { return &m_mat[m_size]; };

		/* Sum */
		T sum() const;

	protected:
		T* m_mat;
		int m_size;
		int m_rows, m_cols;
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
	Mat2(rows, cols)
{
	/* Constructor, must provide the number of rows, number of 
	 * columns and an initial value */
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
	for(int i = 0; i != m_size; i ++) {
		m_mat[i] = m[i];
	}
};

template<typename T>
Mat2<T>& Mat2<T>::operator=(const Mat2<T>& a)
{
	T* p = new T[a.size()];
	for(int i = 0; i != a.size(); ++i)
		p[i] = a[i];
	delete[] m_mat;
	m_mat = p;
	m_size = a.size();
	m_rows = a.rows();
	m_cols = a.cols();

	return *this;
}

template<typename T>
Mat2<T>& Mat2<T>::operator=(Mat2<T>&& other)
{
	// if (this != other ) {
		delete[] m_mat;

		m_mat = other.m_mat;
		m_rows = other.m_rows;
		m_cols = other.m_cols;
		m_size = other.m_size;

		other.m_mat = nullptr;
		other.m_cols = other.m_rows = other.m_size = 0;
	// }

	return *this;
}

template<typename T>
Mat2<T>::Mat2(Mat2<T>&& m) :
	m_mat(nullptr),
	m_size(0),
	m_rows(0),
	m_cols(0)
{
	*this = std::move(m);
}

/* Equality */
template<typename T>
bool Mat2<T>::operator==(const Mat2<T>& other ) const
{
	auto elementComp = [&](){
		for (size_t i = 0; i != m_size; i++) {
			if (m_mat[i] != other.m_mat[i])
				return false;
		}
		return true;
	};
	return other.m_size == m_size && other.m_rows == m_rows && other.m_cols == m_cols && elementComp();
}

template<typename T>
bool Mat2<T>::operator!=(const Mat2<T>& other ) const
{
	return !(*this == other);
}

// template<typename T>
// bool Mat2<T>::operator< (const Mat2<T>& rhs) const
// {
// 	if (m_size != rhs.m_size || m_cols != m_cols || m_rows != rhs.m_rows)
// 		return false;
//
// 	return std::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end(), [](auto l, auto r) {
// 			return l < r;
// 			} );
//
// 	
// }

template<typename T>
void Mat2<T>::setElem(const int j, const int i, const T v)
{
	/* Set element with 2D index */
	m_mat[m_cols * j + i] = v;
}

template<typename T>
void Mat2<T>::setElem(const int idx, const T v)
{
	m_mat[idx] = v;
}

template<typename T>
int Mat2<T>::getIndex(const int j, const int i) const
{
	return m_cols * j + i;
}

template<typename T>
T Mat2<T>::sum() const
{
	return std::accumulate(begin(), end(), T());
}

template<typename T>
Mat2<T>::~Mat2() { delete[] m_mat; }

#endif
