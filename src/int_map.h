#ifndef INT_MAP_H
#define INT_MAP_H

#include "matrix2.h"
#include "int_mappable_abstract.h"

class IntMap:
	public Matrix2<unsigned int> 
{
	public:
		IntMap(unsigned int rows, unsigned int cols); 
		IntMap(IntMappable* raw);
		~IntMap();
	private:
		
};

#endif