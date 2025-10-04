// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;

  cout << "Тестирование ввода/вывода матрицы и операций с ними" << endl;
  TDynamicMatrix<int> m1(3), m2(3), m3(3);
  cin >> m1;
  cout << "Matrix m1:" << endl << m1;
  cin >> m2;
  cout << "Matrix m1:" << endl << m2;
  m3 = m1 * m2;
  cout << "Matrix m3 = m1 * m2:" << endl << m3;
}
//---------------------------------------------------------------------------
