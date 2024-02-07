#ifndef GAUSS_JORDAN
#define GAUSS_JORDAN

#include "matrix.h"

void gauss_jordan(Matrix &a,
                  Matrix &b); // Retorna la inversa en a y la sol en b;
// void gauss_jordan(Matrix &a, NumericalVector &b);
// void gauss_jordan(Matrix &a, valarray<double> &b);
void gauss_jordan(Matrix &a); // Solo retorna la inversa
// void gauss(Matrix a, Matrix &b); //solo retorna la solucion del sistema de
// ecuaciones en b menos operaciones que gauss jordan

#endif // GAUSS_JORDAN
