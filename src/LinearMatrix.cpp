#include "LinearMatrix.h"

LinearMatrix::LinearMatrix(size_t r, size_t c) : cols(c), rows(r) {
	if (c > MAX_MATRIX_SIZE || r > MAX_MATRIX_SIZE) {
		throw std::out_of_range("Rows or columns are too big");
	}
	pMem = new double[cols * rows] {0};
}
LinearMatrix::LinearMatrix(double* arr, size_t r, size_t c) : cols(c), rows(r) {
	if (arr == nullptr) {
		throw std::logic_error("Can't copy the matrix with null pointer");
	}
	if (c > MAX_MATRIX_SIZE || r > MAX_MATRIX_SIZE) {
		throw std::out_of_range("Rows or columns are too big");
	}
	size_t size = cols * rows;
	pMem = new double[size];
	for (size_t i = 0; i < size; i++) {
		pMem[i] = arr[i];
	}
}
LinearMatrix::LinearMatrix(const LinearMatrix& m) : rows(m.rows), cols(m.cols) {
	if (m.pMem == nullptr) {
		throw std::logic_error("Can't copy the matrix with null pointer");
	}
	size_t size = cols * rows;
	pMem = new double[size];
	for (size_t i = 0; i < size; i++) {
		pMem[i] = m.pMem[i];
	}
}
LinearMatrix::LinearMatrix(LinearMatrix&& m) noexcept : cols(m.cols), rows(m.rows), pMem(m.pMem) {
	m.cols = 0;
	m.rows = 0;
	m.pMem = nullptr;
}
LinearMatrix::LinearMatrix(const TDynamicMatrix<double>& m) {
	size_t size = m.size() * m.size();
	pMem = new double[size];
	cols = m.size();
	rows = cols;
	size_t k = 0;
	for (size_t i = 0; i < cols; i++) {
		for (size_t j = 0; j < cols; j++) {
			pMem[k] = m[i][j];
			k++;
		}
	}
}
LinearMatrix::~LinearMatrix() {
	if (pMem != NULL) {
		delete[] pMem;
	}
}
size_t LinearMatrix::size() const noexcept{
	return cols * rows;
}
void swap(LinearMatrix& lhs, LinearMatrix& rhs) noexcept{
	std::swap(lhs.pMem, rhs.pMem);
	std::swap(lhs.cols, rhs.cols);
	std::swap(lhs.rows, rhs.rows);
}
double LinearMatrix::GetCols() const {
	return this->cols;
}
double LinearMatrix::GetRows() const {
	return this->rows;
}
LinearMatrix& LinearMatrix::operator=(const LinearMatrix& m) {
	if (this != &m) {
		size_t size = m.size();
		if ((cols != m.cols) || (rows != m.rows)) {
			delete[] pMem;
			pMem = new double[size];
			cols = m.cols;
			rows = m.rows;
		}
		for (size_t i = 0; i < size; i++) {
			pMem[i] = m.pMem[i];
		}
	}
	return *this;
}
LinearMatrix& LinearMatrix::operator=(LinearMatrix&& m) noexcept{
	swap(*this, m);
	return *this;
}
LinearMatrix& LinearMatrix::operator=(const TDynamicMatrix<double>& m) {
	size_t size = m.size() * m.size();
	if (this->size() != size) {
		delete[] pMem;
		pMem = new double[size];
		cols = m.size();
		rows = cols;
	}
	size_t k = 0;
	for (size_t i = 0; i < cols; i++) {
		for (size_t j = 0; j < cols; j++) {
			pMem[k] = m[i][j];
			k++;
		}
	}
	return *this;
}
double& LinearMatrix::operator()(size_t ind1, size_t ind2) {
	return pMem[ind2 + ind1 * cols];
}
const double& LinearMatrix::operator()(size_t ind1, size_t ind2) const {
	return pMem[ind2 + ind1 * cols];
}
double& LinearMatrix::at(size_t ind1, size_t ind2) {
	if (ind1 >= rows || ind2 >= cols) {
		throw std::out_of_range("The index is out of range");
	}
	return pMem[ind2 + ind1 * cols];
}
const double& LinearMatrix::at(size_t ind1, size_t ind2) const {
	if (ind1 >= rows || ind2 >= cols) {
		throw std::out_of_range("The index is out of range");
	}
	return pMem[ind2 + ind1 * cols];
}
double& LinearMatrix::operator[](size_t ind) {
	return pMem[ind];
}
const double& LinearMatrix::operator[](size_t ind) const{
	return pMem[ind];
}
bool LinearMatrix::operator==(const LinearMatrix& m) const noexcept {
	if ((cols != m.cols) || (rows != m.rows)) {
		return false;
	}
	if (pMem == nullptr && m.pMem == nullptr) {
		return true;
	}
	if (pMem == nullptr || m.pMem == nullptr) {
		return false;
	}
	size_t size = this->size();
	for (size_t i = 0; i < size; i++) {
		if (pMem[i] != m.pMem[i]) {
			return false;
		}
	}
	return true;
}
bool LinearMatrix::operator!=(const LinearMatrix& m) const noexcept {
	return !(*this == m);
}
LinearMatrix LinearMatrix::operator*(const double val) {
	size_t size = this->size();
	LinearMatrix res(size);
	for (size_t i = 0; i < size; i++) {
		res.pMem[i] = pMem[i] * val;
	}
	return res;
}
LinearMatrix LinearMatrix::operator+(const LinearMatrix& m) {
	if ((cols != m.cols) || (rows != m.rows)) {
		throw invalid_argument("Can't add matrices of different size");
	}
	size_t size = this->size();
	LinearMatrix res(m.rows, m.cols);
	for (size_t i = 0; i < size; i++) {
		res.pMem[i] = pMem[i] + m.pMem[i];
	}
	return res;
}
LinearMatrix LinearMatrix::operator-(const LinearMatrix& m) {
	if ((cols != m.cols) || (rows != m.rows)) {
		throw invalid_argument("Can't substract matrices of different size");
	}
	size_t size = this->size();
	LinearMatrix res(m.rows, m.cols);
	for (size_t i = 0; i < size; i++) {
		res.pMem[i] = pMem[i] - m.pMem[i];
	}
	return res;
}
LinearMatrix LinearMatrix::operator*(const LinearMatrix& m) {
	if (cols != m.rows) {
		throw invalid_argument("Can't multiply matrices of these sizes");
	}
	double tmp = 0;
	LinearMatrix res(rows, m.cols);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < m.cols; j++) {
			tmp = 0;
			for (size_t k = 0; k < cols; k++) {
				tmp += (this->at(i, k) * m(k, j));
			}
			res(i, j) = tmp;
		}
	}
	return res;
}
istream& operator>>(istream& istr, LinearMatrix& m) {
	size_t size = m.size();
	for (size_t i = 0; i < size; i++) {
		istr >> m.pMem[i];
	}
	return istr;
}
ostream& operator<<(ostream& ostr, const LinearMatrix& m) {
	size_t size1 = m.rows;
	size_t size2 = m.cols;
	for (size_t i = 0; i < size1; i++) {
		for (size_t j = 0; j < size2; j++) {
			ostr << m(i, j) << ' ';
		}
		ostr << endl;
	}
	return ostr;
}