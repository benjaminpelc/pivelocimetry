#ifndef CCF_H
#define CCF_H

#include "matrix2.h"

class CCF : public Matrix2<double>
{
	public:
		CCF(unsigned int rows, unsigned int cols);
		~CCF();

	private:	
					
};

CCF::CCF(unsigned int rows, unsigned int cols) : Matrix2<double>(rows, cols, -1.1) {}

CCF::~CCF() {}

#endif
