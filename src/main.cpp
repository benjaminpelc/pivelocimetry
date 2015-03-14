#include "ocv_image.h"
#include "matrix2.h"
#include "int_map.h"

int main(int argc, char** argv)
{
	IntMappable* rawIm = new OCVImage("../img/1.bmp");

	IntMap i2 = IntMap(rawIm);
	// std::cout << i2;

	delete rawIm;

	return 0;
}
