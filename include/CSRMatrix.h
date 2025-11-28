#pragma once

#include <iostream>
#include "tmatrix.h"
#include <LinearMatrix.h>

class CSRMatrix {
private:
	size_t rows;
	size_t cols;
	size_t elems;
	double* Data;
	size_t* Indices;
	size_t* IndexPointers;
public:
	CSRMatrix(size_t r = 1, size_t c = 1);
	CSRMatrix(const CSRMatrix& m);
	CSRMatrix(CSRMatrix&& m) noexcept;
	CSRMatrix(const TDynamicMatrix<double>& m);
	CSRMatrix(const LinearMatrix& m);
	~CSRMatrix();
	friend void swap(CSRMatrix&& lhs, CSRMatrix&& rhs) noexcept;
	CSRMatrix& operator=(const CSRMatrix& m);
	CSRMatrix& operator=(CSRMatrix&& m) noexcept;
	CSRMatrix& operator=(const TDynamicMatrix<double>& m);
	CSRMatrix& operator=(const LinearMatrix& m);
	double& operator()(size_t ind1, size_t ind2);
	const double& operator()(size_t ind1, size_t ind2) const;
	double& at(size_t ind1, size_t ind2);
	const double& at(size_t ind1, size_t ind2) const;
	bool operator==(const CSRMatrix& m) noexcept;
	bool operator!=(const CSRMatrix& m) noexcept;
	CSRMatrix operator*(double val);
	friend istream& operator>>(istream& istr, CSRMatrix& m);
	friend ostream& operator<<(ostream& ostr, const CSRMatrix& m);
	void print_in_stored_format() noexcept;
};