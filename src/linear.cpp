#include "linear.h"

const int MAX_MATRIX_SIZE = 10000;

LinearVector::LinearVector(size_t c = 1, size_t r = 1) : cols(c), rows(r) {
	if (c > MAX_MATRIX_SIZE || r > MAX_MATRIX_SIZE) {
		throw std::out_of_range("Rows or columns are too big");
		pMem = new double[c * r];
	}

}