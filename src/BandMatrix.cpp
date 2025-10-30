#include "BandMatrix.h"

BandMatrix::BandMatrix(size_t r, size_t d, size_t c) : rows(r), diag_count(d), c(c) {
	if (r < d || r < c) {
		throw logic_error("The amount of diagonals can't be greater than rows of square matrix");
	}
	if (r > MAX_MATRIX_SIZE) {
		throw out_of_range("The matrix is too big");
	}
	pMem = new double* [diag_count];
	for (size_t i = 0; i < diag_count; i++) {
		pMem[i] = new double[rows] {0};
	}
}
BandMatrix::BandMatrix(const BandMatrix& m) : rows(m.rows), diag_count(m.diag_count), c(m.c) {
	if (m.pMem == nullptr) {
		throw std::logic_error("Can't copy the matrix with null pointer");
	}
	pMem = new double* [diag_count];
	for (size_t i = 0; i < diag_count; i++) {
		pMem[i] = new double[rows];
		for (size_t j = 0; j < rows; j++) {
			pMem[i][j] = m.pMem[i][j];
		}
	}
}
BandMatrix::BandMatrix(BandMatrix&& m) noexcept : rows(m.rows), diag_count(m.diag_count), pMem(m.pMem), c(m.c) {
	m.rows = 0;
	m.diag_count = 0;
	m.pMem = nullptr;
}
BandMatrix::BandMatrix(const TDynamicMatrix<double>& m) : rows(m.size()) {
	size_t diag_size = m.size() * 2 - 1;
	size_t tmp = m.size();
	size_t cent = tmp;
	size_t k = 1;
	bool flag = false;
	size_t first = 0;
	for (size_t i = tmp - 1; i > 0; i--) {
		size_t counter = 0;
		for (size_t j = 0; j < tmp - i; j++) {
			if (m[i + j][j] != 0) {
				flag = true;
				break;
			}
			counter++;
		}
		if (k - counter == 0 && !flag) {
			diag_size--;
		}
		else if (flag) {
			first = k;
		}
		k++;
	}
	size_t second = k;
	k--;
	for (size_t i = 1; i < tmp; i++) {
		size_t counter = 0;
		for (size_t j = 0; j < tmp - i; j++) {
			if (m[j][i + j] != 0) {
				second++;
				break;
			}
			counter++;
		}
		if (k - counter == 0) {
			diag_size--;
		}
		k--;
	}
	diag_count = diag_size;
	c = tmp - first + 1;
	pMem = new double* [diag_count];
	for (size_t i = 0; i < diag_count; i++) {
		pMem[i] = new double[rows] {0};
	}
	k = 0;
	for (size_t i = (tmp - first); i > 0; i--) {
		for (size_t j = 0; j < tmp - i; j++) {
			pMem[k][j+i] = m[i + j][j];
		}
		k++;
	}
	for (size_t i = 0; i < second - tmp + 1; i++) {
		for (size_t j = 0; j < tmp - i; j++) {
			pMem[k][j] = m[j][i + j];
		}
		k++;
	}
}
BandMatrix::~BandMatrix() {
	if (pMem != NULL) {
		for (size_t i = 0; i < diag_count; i++) {
			delete[] pMem[i];
		}
		delete[] pMem;
	}
}
size_t BandMatrix::rsize() noexcept {
	return rows;
}
size_t BandMatrix::dsize() noexcept {
	return diag_count;
}
size_t BandMatrix::center() noexcept {
	return c;
}
void swap(BandMatrix&& lhs, BandMatrix&& rhs) noexcept {
	swap(lhs.pMem, rhs.pMem);
	swap(lhs.diag_count, rhs.diag_count);
	swap(lhs.rows, rhs.rows);
}
BandMatrix& BandMatrix::operator=(const BandMatrix& m) {
	if (m.pMem == nullptr) {
		throw std::logic_error("Can't copy the matrix with null pointer");
	}
	if (diag_count == m.diag_count) {
		if (rows != m.rows) {
			for (size_t i = 0; i < m.rows; i++) {
				delete[] pMem[i];
				pMem[i] = new double[m.rows];
			}
		}
	}
	else {
		for (size_t i = 0; i < m.rows; i++) {
			delete[] pMem[i];
		}
		delete[] pMem;
		pMem = new double* [m.diag_count];
		for (size_t i = 0; i < m.rows; i++) {
			pMem[i] = new double[m.rows];
		}
	}
	rows = m.rows;
	diag_count = m.diag_count;
	c = m.c;
	for (size_t i = 0; i < diag_count; i++) {
		for (size_t j = 0; j < rows; j++) {
			pMem[i][j] = m.pMem[i][j];
		}
	}
	return* this;
}
BandMatrix& BandMatrix::operator=(BandMatrix&& m) noexcept {
	swap(*this, m);
	return *this;
}
double& BandMatrix::operator()(size_t ind1, size_t ind2) {
	if (ind1 >= rows || ind2 >= rows) {
		throw out_of_range("The indexes are out of range");
	}
	if (abs(((int)ind1 - (int)ind2)) >= diag_count && ind2 < rows || c - 1 + ind2 - ind1 >= diag_count) {
		double exc = 0;
		return exc;
	}
	return pMem[c - 1 + ind2 - ind1][ind1];
}
const double& BandMatrix::operator()(size_t ind1, size_t ind2) const {
	if (ind1 >= rows || ind2 >= rows) {
		throw out_of_range("The indexes are out of range");
	}
	if (abs(((int)ind1 - (int)ind2)) >= diag_count && ind2 < rows || c - 1 + ind2 - ind1 >= diag_count) {
		return 0;
	}
	return pMem[c - 1 + ind2 - ind1][ind1];
}
double& BandMatrix::at(size_t ind1, size_t ind2) {
	if (ind1 >= rows || ind2 >= rows) {
		throw out_of_range("The indexes are out of range");
	}
	if (abs(((int)ind1 - (int)ind2)) >= diag_count && ind2 < rows || c - 1 + ind2 - ind1 >= diag_count) {
		double exc = 0;
		return exc;
	}
	return pMem[c - 1 + ind2 - ind1][ind1];
}
const double& BandMatrix::at(size_t ind1, size_t ind2) const {
	if (ind1 >= rows || ind2 >= rows) {
		throw out_of_range("The indexes are out of range");
	}
	if (abs(((int)ind1 - (int)ind2)) >= diag_count && ind2 < rows || c - 1 + ind2 - ind1 >= diag_count) {
		return 0;
	}
	return pMem[c - 1 + ind2 - ind1][ind1];
}
bool BandMatrix::operator==(const BandMatrix& m) noexcept {
	if (rows != m.rows || diag_count != m.diag_count || c != m.c) {
		return false;
	}
	if (pMem == m.pMem) {
		return true;
	}
	if (pMem == nullptr && m.pMem == nullptr) {
		return true;
	}
	if (pMem == nullptr || m.pMem == nullptr) {
		return false;
	}
	for (size_t i = 0; i < diag_count; i++) {
		for (size_t j = 0; j < rows; j++) {
			if (pMem[i][j] != m.pMem[i][j]) {
				return false;
			}
		}
	}
	return true;
}
bool BandMatrix::operator!=(const BandMatrix& m) noexcept {
	return !(*this == m);
}
BandMatrix BandMatrix::operator*(double val) {
	BandMatrix res(rows, diag_count, c);
	for (size_t i = 0; i < diag_count; i++) {
		for (size_t j = 0; j < rows; j++) {
			res.pMem[i][j] = pMem[i][j] * val;
		}
	}
	return res;
}
BandMatrix BandMatrix::operator+(const BandMatrix& m) {
	if (rows != m.rows) {
		throw logic_error("Can't add matrices of different size");
	}
	TDynamicMatrix<double> tmp(rows);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rows; j++) {
			tmp[i][j] = this->at(i, j) + m(i, j);
		}
	}
	BandMatrix res(tmp);
	return res;
}
BandMatrix BandMatrix::operator-(const BandMatrix& m) {
	if (rows != m.rows) {
		throw logic_error("Can't substract matrices of different size");
	}
	TDynamicMatrix<double> tmp(rows);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rows; j++) {
			tmp[i][j] = this->at(i, j) - m(i, j);
		}
	}
	BandMatrix res(tmp);
	return res;
}
BandMatrix BandMatrix::operator*(const BandMatrix& m) {
	if (rows != m.rows) {
		throw logic_error("Can't substract matrices of different size");
	}
	TDynamicMatrix<double> tmp(rows);
	for (size_t k = 0; k < rows; k++) {
		for (size_t i = 0; i < rows; i++) {
			double sum = 0;
			for (size_t j = 0; j < rows; j++) {
				sum += this->at(k, j) * m(j, i);
			}
			tmp[k][i] = sum;
		}
	}
	BandMatrix res(tmp);
	return res;
}
istream& operator>>(istream& istr, BandMatrix& m) {
	for (size_t i = 0; i < m.rows; i++) {
		for (size_t j = 0; j < m.diag_count; j++) {
			istr >> m.pMem[j][i];
		}
	}
	return istr;
}
ostream& operator<<(ostream& ostr, const BandMatrix& m) {
	for (size_t i = 0; i < m.rows; i++) {
		for (size_t j = 0; j < m.rows; j++) {
			ostr << m(i, j) << ' ';
		}
		ostr << endl;
	}
	return ostr;
}
void BandMatrix::print_in_stored_format() noexcept {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < diag_count; j++) {
			cout << pMem[j][i] << ' ';
		}
		cout << endl;
	}
}