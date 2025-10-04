// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (size == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (size > MAX_VECTOR_SIZE) {
            throw out_of_range("The size is too big");
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        if (s > MAX_VECTOR_SIZE) {
            throw out_of_range("The size is too big");
        }
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz) {
        if (v.pMem == nullptr) {
            throw logic_error("Can't copy the vector with null pointer");
        }
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        if (pMem != NULL) {
            delete[] pMem;
        }
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
            for (int i = 0; i < sz; i++) {
                pMem[i] = v.pMem[i];
            }
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.pMem = nullptr;
            v.sz = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind >= sz) {
            throw out_of_range("Index is out of range");
        }
        if (pMem == nullptr) {
            throw logic_error("Can't find that vector");
        }
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind >= sz) {
            throw out_of_range("Index is out of range");
        }
        if (pMem == nullptr) {
            throw logic_error("Can't find that vector");
        }
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz) {
            throw out_of_range("Index is out of range");
        }
        if (pMem == nullptr) {
            throw logic_error("Can't find that vector");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz) {
            throw out_of_range("Index is out of range");
        }
        if (pMem == nullptr) {
            throw logic_error("Can't find that vector");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) {
            return false;
        }
        if (pMem == nullptr && v.pMem == nullptr) {
            return true;
        }
        if (pMem == nullptr || v.pMem == nullptr) {
            return false;
        }
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(this == &v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> v(sz);
        for (size_t i = 0; i < sz; i++) {
            v.pMem[i] = pMem[i] + val;
        }
        return v;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector<T> v(sz);
        for (size_t i = 0; i < sz; i++) {
            v.pMem[i] = pMem[i] - val;
        }
        return v;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector<T> v(sz);
        for (size_t i = 0; i < sz; i++) {
            v.pMem[i] = pMem[i] * val;
        }
        return v;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw invalid_argument("Can't add vectors of different size");
        }
        TDynamicVector<T> v1(sz);
        for (size_t i = 0; i < sz; i++) {
            v1.pMem[i] = pMem[i] + v.pMem[i];
        }
        return v1;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw invalid_argument("Can't substract vectors of different size");
        }
        TDynamicVector<T> v1(sz);
        for (size_t i = 0; i < sz; i++) {
            v1.pMem[i] = pMem[i] - v.pMem[i];
        }
        return v1;
    }
    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw invalid_argument("Can't multiply vectors of different size");  
        }
        T res = 0;
        T tmp = 0;
        for (size_t i = 0; i < sz; i++) {
            tmp = pMem[i] * v.pMem[i];
            res = res + tmp;
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE) {
            throw out_of_range("The size is too big");
        }
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    size_t size() const noexcept { return sz; }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) {
            return false;
        }
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                if (pMem[i][j] != m.pMem[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix M(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                M[i][j] = this[i][j] * val;
            }
        }
        return M;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) {
            throw invalid_argument("Given vector has different size");
        }
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            T tmp = 0;
            for (size_t j = 0; j < sz; j++) {
                tmp += v[j] * pMem[i][j];
            }
            res[i] = tmp;
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.size()) {
            throw invalid_argument("Given matrix has different size");
        }
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i][j] = pMem[i][j] + m[i][j];
            }
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.size()) {
            throw invalid_argument("Given matrix has different size");
        }
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i][j] = pMem[i][j] - m[i][j];
            }
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        TDynamicMatrix C(1);
        return C;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        T size = v.sz;
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++) {
                istr >> v.pMem[i][j];
            }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        
        T size = v.sz;
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                ostr << v[i][j] << ' ';
            }
            ostr << endl;
        }
        return ostr;
    }
};

#endif
