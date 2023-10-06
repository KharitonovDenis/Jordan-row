#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

/*
Считывает или генерирует матрицу
*/
int InputMatrix(int n, float * a, int inputMode, FILE* fin);

/*
Выводит матрицу
*/
void PrintMatrix(int n, float* a);

/* 
Вычисляет норму невязки 
*/
float SolutionError(int n, float* a, float* x);

#endif /* not __MATRIX_H_INCLUDED__ */

