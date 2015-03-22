#include "int_map.h"

IntMap::IntMap(unsigned int rows, unsigned int cols) : Mat2<unsigned int>(rows, cols) {}

IntMap::IntMap(IntMappable* raw) : Mat2<unsigned int>(raw->height(), raw->width())
{
	unsigned int wdth = raw->width();

	for (size_t j = 0; j < raw->height(); j++) {
		for (size_t i = 0; i < wdth; i++) {
			setElem((j * wdth) +  i, raw->pixelInt(j, i));
		}
	}
}

IntMap::IntMap(const std::unique_ptr<IntMappable>& raw) : Mat2<unsigned int>(raw->height(), raw->width())
{
	unsigned int wdth = raw->width();

	auto fe = begin();
	
	for (size_t j = 0; j < raw->height(); j++) {
		for (size_t i = 0; i < wdth; i++) {
			// setElem(j*wdth + i, raw->pixelInt(j, i));
			*(fe++) =  raw->pixelInt(j, i);
		}
	}
}

IntMap::~IntMap() {}
