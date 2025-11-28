#pragma once
#include <iostream>
#include "tmatrix.h"

class LinearMatrix {
private:
	size_t cols;
	size_t rows;
	double* pMem;
public:
	LinearMatrix(size_t c = 1, size_t r = 1);
	LinearMatrix(double* arr, size_t c, size_t r);
	LinearMatrix(const LinearMatrix& m);
	LinearMatrix(LinearMatrix&& m) noexcept;
	LinearMatrix(const TDynamicMatrix<double>& m);
	~LinearMatrix();
	size_t size() const noexcept;
	double GetRows() const;
	double GetCols() const;
	friend void swap(LinearMatrix& lhs, LinearMatrix& rhs) noexcept;
	LinearMatrix& operator=(const LinearMatrix& m);
	LinearMatrix& operator=(LinearMatrix&& m) noexcept;
	LinearMatrix& operator=(const TDynamicMatrix<double>& m);
	double& operator()(size_t ind1, size_t ind2);
	const double& operator()(size_t ind1, size_t ind2) const;
	double& at(size_t ind1, size_t ind2);
	const double& at(size_t ind1, size_t ind2) const;
	double& operator[](size_t ind);
	const double& operator[](size_t ind) const;
	bool operator==(const LinearMatrix& m) const noexcept;
	bool operator!=(const LinearMatrix& m) const noexcept;
	LinearMatrix operator*(const double val);
	LinearMatrix operator+(const LinearMatrix& m);
	LinearMatrix operator-(const LinearMatrix& m);
	LinearMatrix operator*(const LinearMatrix& m);
	friend istream& operator>>(istream& istr, LinearMatrix& m);
	friend ostream& operator<<(ostream& ostr, const LinearMatrix& m);
};