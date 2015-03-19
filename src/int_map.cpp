#include "int_map.h"

IntMap::IntMap(unsigned int rows, unsigned int cols) : Matrix2<unsigned int>(rows, cols) {}

IntMap::IntMap(IntMappable* raw) : Matrix2<unsigned int>(raw->height(), raw->width())
{
	unsigned int wdth = raw->width();

	for (int j = 0; j < raw->height(); j++) {
		for (int i = 0; i < wdth; i++) {
			setElem(j, i, raw->pixelInt(j, i));
		}
	}
}

IntMap::IntMap(const std::unique_ptr<IntMappable>& raw) : Matrix2<unsigned int>(raw->height(), raw->width())
{
	unsigned int wdth = raw->width();

	for (int j = 0; j < raw->height(); j++) {
		for (int i = 0; i < wdth; i++) {
			setElem(j, i, raw->pixelInt(j, i));
		}
	}
}

IntMap::~IntMap() {}
