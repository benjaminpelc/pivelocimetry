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

		T* begin() { return &_mat[0]; };
		T* end () { return &_mat[_size]; };

	protected:
		T* _mat;
		int _size;
		int _rows, _cols;
	
	private:
		T* _begin;
		T* _end;
};

#endif

template<typename T>
Mat2<T>::Mat2(unsigned int rows, unsigned int cols) :
	_size(rows * cols),
	_rows(rows),
	_cols(cols)
{
	/* Constructor, must provide the number of rows, number of 
	 * columns and an initial value */
	_mat = new T[_size]{0};
}

template<typename T>
Mat2<T>::Mat2(unsigned int rows, unsigned int cols, T v) :
	_size(rows * cols),
	_rows(rows),
	_cols(cols)
{
	/* Constructor, must provide the number of rows, number of 
	 * columns and an initial value */
	_mat = new T[_size];
	std::fill(_mat, _mat + _size, v);
}

template<typename T>
T Mat2<T>::getElem(int idx)
{
	/* Return element with linear index, this 
	 * will be fastest */
	return _mat[idx];
}

template<typename T>
T Mat2<T>::getElem(int j, int i)
{
	/* Return element with 2D index */
	return _mat[_cols * j + i];
}

template<typename T>
void Mat2<T>::setElem(int j, int i, T v)
{
	/* Set element with 2D index */
	_mat[_cols * j + i] = v;
}

template<typename T>
int Mat2<T>::size()
{
	return _size;
}

template<typename T>
int Mat2<T>::rows()
{
	return _rows;
}

template<typename T>
int Mat2<T>::cols()
{
	return _cols;
}

template<typename T>
int Mat2<T>::getIndex(int j, int i)
{
	return _cols * j + i;
}

template<typename T>
Mat2<T>::~Mat2() { delete[] _mat; }
