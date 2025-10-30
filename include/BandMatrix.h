#pragma once

#include "tmatrix.h"
#include <iostream>

class BandMatrix {
private:
	size_t rows;
	size_t diag_count;
	size_t c;
	double** pMem;
public:
	BandMatrix(size_t r = 1, size_t d = 1, size_t c = 0);
	BandMatrix(const BandMatrix& m);
	BandMatrix(BandMatrix&& m) noexcept;
	BandMatrix(const TDynamicMatrix<double>& m);
	~BandMatrix();
	size_t rsize() noexcept;
	size_t dsize() noexcept;
	size_t center() noexcept;
	friend void swap(BandMatrix&& lhs, BandMatrix&& rhs) noexcept;
	BandMatrix& operator=(const BandMatrix& m);
	BandMatrix& operator=(BandMatrix&& m) noexcept;
	BandMatrix& operator=(const TDynamicMatrix<double>& m);
	double& operator()(size_t ind1, size_t ind2);
	const double& operator()(size_t ind1, size_t ind2) const;
	double& at(size_t ind1, size_t ind2);
	const double& at(size_t ind1, size_t ind2) const;
	bool operator==(const BandMatrix& m) noexcept;
	bool operator!=(const BandMatrix& m) noexcept;
	BandMatrix operator*(double val);
	BandMatrix operator+(const BandMatrix& m);
	BandMatrix operator-(const BandMatrix& m);
	BandMatrix operator*(const BandMatrix& m);
	friend istream& operator>>(istream& istr, BandMatrix& m);
	friend ostream& operator<<(ostream& ostr, const BandMatrix& m);
	void print_in_stored_format() noexcept;
};