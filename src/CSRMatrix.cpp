#include "CSRMatrix.h"

CSRMatrix::CSRMatrix(size_t r, size_t c) : rows(r), cols(c) {
	if (r == 0 || c == 0) {
		throw logic_error("Matrix should have positive number of rows or colons");
	}
	IndexPointers = new size_t[cols + 1]{0};
	elems = 0;
}
CSRMatrix::CSRMatrix(const CSRMatrix& m) : cols(m.cols), elems(m.elems) {
	if (m.IndexPointers == nullptr) {
		throw std::logic_error("Can't copy the matrix with null pointer");
	}
	if (rows != m.rows) {
		rows = m.rows;
		IndexPointers = new size_t[cols + 1];
	}
	for (size_t i = 0; i < rows + 1; i++) {
		IndexPointers[i] = m.IndexPointers[i];
	}
	if (m.Indices != nullptr) {
		Indices = new size_t[elems];
		for (size_t i; i < elems; i++) {
			Indices[i] = m.Indices[i];
		}
	}
	if (m.Data != nullptr) {
		Data = new double[elems];
		for (size_t i; i < elems; i++) {
			Data[i] = m.Data[i];
		}
	}
}
CSRMatrix::CSRMatrix(CSRMatrix&& m) noexcept : rows(m.rows), cols(m.cols), elems(m.elems), Data(m.Data), Indices(m.Indices), IndexPointers(m.IndexPointers) {
	m.Data = nullptr;
	m.Indices = nullptr;
	m.IndexPointers = nullptr;
	cols = 0;
	rows = 0;
	elems = 0;
}
CSRMatrix::CSRMatrix(const TDynamicMatrix<double>& m) : rows(m.size()), cols(rows) {
	elems = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rows; j++) {
			if (m[i][j] != 0) {
				elems++;
			}
		}
	}
	Data = new double[elems];
	Indices = new size_t[elems];
	IndexPointers = new size_t[cols + 1]{0};
	size_t k = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rows; j++) {
			if (m[i][j] != 0) {
				Data[k] = m[i][j];
				Indices[k] = j;
				IndexPointers[i + 1]++;
				k++;
			}
		}
		IndexPointers[i + 1] += IndexPointers[i];
	}
}
CSRMatrix::CSRMatrix(const LinearMatrix& m) {
	rows = m.GetRows();
	cols = m.GetCols();
	elems = 0;
	IndexPointers = new size_t[cols + 1];
	IndexPointers[0] = 0;
	size_t tmp = m.size();
	size_t k = 0, l = 1;
	for (size_t i = 0; i < tmp; i++) {
		if (m[i] != 0) {
			elems++;
		}
		k++;
		if (k == rows) {
			IndexPointers[l] = elems;
			l++;
			k = 0;
		}
	}
	Data = new double[elems];
	Indices = new size_t[elems];
	k = 0, l = 0;
	for (size_t i = 0; i < tmp; i++) {
		if (m[i] != 0) {
			Data[k] = m[i];
			Indices[k] = l;
			k++;
		}
		l++;
		if (l == rows) {
			l = 0;
		}
	}
}
CSRMatrix::~CSRMatrix() {
	delete[] IndexPointers;
	delete[] Data;
	delete[] Indices;
}
void swap(CSRMatrix&& lhs, CSRMatrix&& rhs) noexcept {
	swap(lhs.cols, rhs.cols);
	swap(lhs.rows, rhs.rows);
	swap(lhs.elems, rhs.elems);
	swap(lhs.Data, rhs.Data);
	swap(lhs.Indices, rhs.Indices);
	swap(lhs.IndexPointers, rhs.IndexPointers);
}
CSRMatrix& CSRMatrix::operator=(const CSRMatrix& m) {
	if (this != &m) {
		if (m.IndexPointers == nullptr) {
			throw std::logic_error("Can't copy the matrix with null pointer");
		}
		if (rows != m.rows) {
			rows = m.rows;
			IndexPointers = new size_t[cols + 1];
		}
		cols = m.cols;
		elems = m.elems;
		for (size_t i = 0; i < rows + 1; i++) {
			IndexPointers[i] = m.IndexPointers[i];
		}
		if (m.Indices != nullptr) {
			Indices = new size_t[elems];
			for (size_t i; i < elems; i++) {
				Indices[i] = m.Indices[i];
			}
		}
		if (m.Data != nullptr) {
			Data = new double[elems];
			for (size_t i; i < elems; i++) {
				Data[i] = m.Data[i];
			}
		}
	}
	return *this;
}
CSRMatrix& CSRMatrix::operator=(CSRMatrix&& m) noexcept {
	swap(*this, m);
	return *this;
}
CSRMatrix& CSRMatrix::operator=(const TDynamicMatrix<double>& m) {
	rows = m.size();
	cols = rows;
	elems = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rows; j++) {
			if (m[i][j] != 0) {
				elems++;
			}
		}
	}
	Data = new double[elems];
	Indices = new size_t[elems];
	IndexPointers = new size_t[cols + 1]{ 0 };
	size_t k = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rows; j++) {
			if (m[i][j] != 0) {
				Data[k] = m[i][j];
				Indices[k] = j;
				IndexPointers[i + 1]++;
				k++;
			}
		}
		IndexPointers[i + 1] += IndexPointers[i];
	}
	return *this;
}
CSRMatrix& CSRMatrix::operator=(const LinearMatrix& m) {
	rows = m.GetRows();
	cols = m.GetCols();
	elems = 0;
	delete[] IndexPointers;
	delete[] Data;
	delete[] Indices;
	IndexPointers = new size_t[rows + 1];
	IndexPointers[0] = 0;
	size_t tmp = m.size();
	size_t k = 0, l = 1;
	for (size_t i = 0; i < tmp; i++) {
		if (m[i] != 0) {
			elems++;
		}
		k++;
		if (k == rows) {
			IndexPointers[l] = elems;
			l++;
			k = 0;
		}
	}
	Data = new double[elems];
	Indices = new size_t[elems];
	k = 0, l = 0;
	for (size_t i = 0; i < tmp; i++) {
		if (m[i] != 0) {
			Data[k] = m[i];
			Indices[k] = l;
			k++;
		}
		l++;
		if (l == rows) {
			l = 0;
		}
	}
	return *this;
}
double& CSRMatrix::operator()(size_t ind1, size_t ind2) {
	if (IndexPointers[ind1 + 1] - IndexPointers[ind1] != 0) {
		for (size_t i = IndexPointers[ind1]; i < IndexPointers[ind1 + 1]; i++) {
			if (Indices[i] == ind2) {
				return Data[i];
			}
		}
	}
	double exc = 0;
	return exc;
}
const double& CSRMatrix::operator()(size_t ind1, size_t ind2) const {
	if (IndexPointers[ind1 + 1] - IndexPointers[ind1] != 0) {
		for (size_t i = IndexPointers[ind1]; i < IndexPointers[ind1 + 1]; i++) {
			if (Indices[i] == ind2) {
				return Data[i];
			}
		}
	}
	return 0;
}
double& CSRMatrix::at(size_t ind1, size_t ind2) {
	if (ind1 > rows || ind2 > cols) {
		throw out_of_range("The indices are out of range");
	}
	if (IndexPointers[ind1 + 1] - IndexPointers[ind1] != 0) {
		for (size_t i = IndexPointers[ind1]; i < IndexPointers[ind1 + 1]; i++) {
			if (Indices[i] == ind2) {
				return Data[i];
			}
		}
	}
	double exc = 0;
	return exc;
}
const double& CSRMatrix::at(size_t ind1, size_t ind2) const {
	if (ind1 > rows || ind2 > cols) {
		throw out_of_range("The indices are out of range");
	}
	if (IndexPointers[ind1 + 1] - IndexPointers[ind1] != 0) {
		for (size_t i = IndexPointers[ind1]; i < IndexPointers[ind1 + 1]; i++) {
			if (Indices[i] == ind2) {
				return Data[i];
			}
		}
	}
	return 0;
}
bool CSRMatrix::operator==(const CSRMatrix& m) noexcept {
	if (rows != m.rows || cols != m.cols != elems != m.elems) {
		return false;
	}
	for (size_t i = 0; i < elems; i++) {
		if (Indices[i] != m.Indices[i] || Data[i] != m.Data[i]) {
			return false;
		}
	}
	for (size_t i = 1; i < rows + 1; i++) {
		if (IndexPointers[i] != m.IndexPointers[i]) {
			return false;
		}
	}
	return true;
}
bool CSRMatrix::operator!=(const CSRMatrix& m) noexcept {
	return (*this != m);
}
CSRMatrix CSRMatrix::operator*(double val) {
	CSRMatrix res(*this);
	for (size_t i = 0; i < elems; i++) {
		res.Data[i] *= val;
	}
	return res;
}
istream& operator>>(istream& istr, CSRMatrix& m) {
	LinearMatrix tmp(m.cols, m.rows);
	cin >> tmp;
	m = tmp;
	return istr;
}
ostream& operator<<(ostream& ostr, const CSRMatrix& m) {
	for (size_t i = 0; i < m.cols; i++) {
		for (size_t j = 0; j < m.rows; j++) {
			ostr << m(i, j) << ' ';
		}
		ostr << endl;
	}
	return ostr;
}
void CSRMatrix::print_in_stored_format() noexcept {
	for (size_t i = 0; i < cols + 1; i++) {
		cout << IndexPointers[i] << ' ';
	}
	cout << '\n';
	for (size_t i = 0; i < elems; i++) {
		cout << Indices[i] << ' ';
	}
	cout << '\n';
	for (size_t i = 0; i < elems; i++) {
		cout << Data[i] << ' ';
	}
	cout << '\n';
}