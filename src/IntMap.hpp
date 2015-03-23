#ifndef INT_MAP_H
#define INT_MAP_H

#include <memory>

#include "../lib/Mat2.hpp"
#include "IntMappable.hpp"

class IntMap: public Mat2<unsigned int> 
{
	public:
		/* unique pointer typedef call with IntMap::Uptr */
		typedef std::unique_ptr<IntMap> Uptr;
		typedef std::pair<IntMap::Uptr&, IntMap::Uptr&> Pair;

		IntMap(unsigned int rows, unsigned int cols); 
		IntMap(IntMappable* raw);
		IntMap(const std::unique_ptr<IntMappable>& raw);

		~IntMap();
	private:
		
};

#endif
