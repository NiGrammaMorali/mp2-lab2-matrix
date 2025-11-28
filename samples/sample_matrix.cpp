// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "LinearMatrix.h"
#include "BandMatrix.h"
#include "CSRMatrix.h"
//---------------------------------------------------------------------------

void main()
{
  TDynamicMatrix<double> a(5), b(5), c(5);
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
  //LinearMatrix m1(2, 3), m2(3, 2);
  LinearMatrix m(3, 2);
  cin >> m;
  cout << "Matrix m:" << endl << m;
  CSRMatrix R(m);
  cout << "Matrix R = c:" << endl << R;
  R.print_in_stored_format();
}
//---------------------------------------------------------------------------
