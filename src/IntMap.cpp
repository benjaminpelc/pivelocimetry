#include "IntMap.hpp"

IntMap::IntMap(unsigned int rows, unsigned int cols) : Mat2<uint16_t>(rows, cols) {}

IntMap::IntMap(IntMappable* raw) : Mat2<uint16_t>(raw->height(), raw->width())
{
	unsigned int wdth = raw->width();

	for (size_t j = 0; j < raw->height(); j++) {
		for (size_t i = 0; i < wdth; i++) {
			setElem((j * wdth) +  i, raw->pixelInt(j, i));
		}
	}
}

IntMap::IntMap(const std::unique_ptr<IntMappable>& raw) : Mat2<uint16_t>(raw->height(), raw->width())
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
