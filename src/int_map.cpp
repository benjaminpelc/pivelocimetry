#include "int_map.h"

IntMap::IntMap(unsigned int rows, unsigned int cols) : Matrix2<unsigned int>(rows, cols) {}

IntMap::IntMap(IntMappable* raw) : Matrix2<unsigned int>(raw->getHeight(), raw->getWidth())
{
	unsigned int wdth = raw->getWidth();

	for (int j = 0; j < raw->getHeight(); j++) {
		for (int i = 0; i < wdth; i++) {
			set_elem(j, i, raw->getPixelIntensity(j, i));
		}
	}
}

IntMap::IntMap(const std::unique_ptr<IntMappable>& raw) : Matrix2<unsigned int>(raw->getHeight(), raw->getWidth())
{
	unsigned int wdth = raw->getWidth();

	for (int j = 0; j < raw->getHeight(); j++) {
		for (int i = 0; i < wdth; i++) {
			set_elem(j, i, raw->getPixelIntensity(j, i));
		}
	}
}

IntMap::~IntMap() {}
