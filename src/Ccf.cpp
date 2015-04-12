#include "Ccf.hpp"

namespace PivEng {

/* Constructor:
 * Must be passed with row and column number specifiers.
 * Calls default Matrix2<double> constructor.
 * Initialize all values to -1.0  */
CCF::CCF(unsigned int rows, unsigned int cols) : Mat2<double>(rows, cols, -1.0) {}

/* Destructor:
 * Nothing exciting here, all memory is deallocated inside Matrix2 
 * parent class */
CCF::~CCF() {}


}
