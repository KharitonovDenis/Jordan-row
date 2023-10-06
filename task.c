#include <math.h>

#include "task.h"

int InvertMatrix(int n, float* a, float* x, int* index )
{
	// index - перестановка столбцов index[i] - номер столбца, который стоит на месте i
	int i;
	int j;
	int k;
	int indMax;
	float tmp;
	float max;

	// создаем единичную матрицу х
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = (float)(i == j);

	for (i = 0; i < n; ++i)
		index[i] = i;

	for (i = 0; i < n; ++i)
	{
		// ищем максимальный по модулю элемент в i-й строке
		max = fabs(a[i * n + i]);
		indMax = i;

		for (j = i + 1; j < n; ++j)
			if (max < fabs(a[i * n + j]))
			{
				max = fabs(a[i * n + j]);
				indMax = j;
			}

		// меняем местами index[i] и index[indMax]
		k = index[i];
		index[i] = index[indMax];
		index[indMax] = k;

		//меняем местами i-й и indMax столбцы в а
		for (j = 0; j < n; ++j)
		{
			tmp = a[j * n + i];
			a[j * n + i] = a[j * n + indMax];
			a[j * n + indMax] = tmp;
		}

		// проверяем на невырожденность
		if (fabs(a[i * n + i]) < 1e-10)
			return -1;

		tmp = 1.0 / a[i * n + i]; // коэффициент для строки i
		for (j = i; j < n; ++j)
			a[i * n + j] *= tmp; // домножаем на коэффициент

		for (j = 0; j < n; ++j)
			x[i * n + j] *= tmp; // повторяем для х

		for (j = 0; j < i; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp; // делаем нули в i столбце над главной диагональю

			for (k = 0; k < n; ++k)
				x[j * n + k] -= x[i * n + k] * tmp; // повторяем для х
		}

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp; // вычитаем из нижних строчек текущую с коэффициентом, обнуляющим начало

			for (k = 0; k < n; ++k)
				x[j * n + k] -= x[i * n + k] * tmp; // повторяем для х
		}
	}
	// меняем местами строки в х
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			a[index[i] * n + j] = x[i * n + j];

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = a[i * n + j];

	return 0;
}

