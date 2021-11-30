#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int amount;
	double common_sum = 0.0;
	double coeff_sum = 0.0;

	// ввод количества критериев
	while (true)
	{
		cout << "Введите количество критериев (ЦЕЛОЕ число от 2 до 7): ";
		cin >> amount;
		
		// обработка ввода неверного типа данных
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			cout << "Неверный тип данных.\n" << "Повторите попытку." << endl;
			cout << endl;
		}

		// обработка ввода числа, выходящего за пределы диапазона
		else if (amount < 2 || amount > 7)
		{
			cout << endl;
			cout << "Количество критериев должно быть числом в диапазоне 2-7.\n" << "Повторите попытку." << endl;
			cout << endl;
		}

		else
		{
			break;
		}
	
	}

	double** array = new double* [amount];
	double* sum_s = new double [amount];
	double* coeff = new double[amount];

	// создание двумерного массива
	for (int i = 0; i < amount; i++)
	{
		array[i] = new double [amount];
	}

	// заполнение массива
	for (int i = 0; i < amount; i++)
	{
		cout << endl;
		for (int j = 0; j < amount; j++)
		{
			// при сравнении критерия с самим собой
			if (i == j)
			{
				array[i][j] = 1;
			}

			// заполнение верхнего треугольника матрицы
			else if (i < j)
			{
				while (true)
				{
					cout << "Критерий " << i + 1 << " важнее Критерия " << j + 1 << " на (число от 0.11 до 9): ";
					cin >> array[i][j];


					// обработка ввода неверного типа данных
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << endl;
						cout << "Неверный тип данных.\n" << "Повторите попытку." << endl;
						cout << endl;
					}

					// обработка ввода числа, выходящего за пределы диапазона
					else if (array[i][j] < 0.11 || array[i][j] > 9)
					{
						cout << endl;
						cout << "Введено число, которое не входит в заданный диапазон.\n" << "Повторите попытку." << endl;
						cout << endl;
					}

					else
					{
						break;
					}
				}
				// расчет нижнего треугольника матрицы
				array[j][i] = 1 / array[i][j];
			}
			
		}
	}

	// суммы строк массива и сумма всех его элементов
	for (int i = 0; i < amount; i++)
	{
		double sum = 0.0;

		for (int j = 0; j < amount; j++)
		{
			sum += array[i][j];
			common_sum += array[i][j];
		}
		sum_s[i] = sum;
	}

	// коэффициенты и их сумма
	for (int i = 0; i < amount; i++)
	{
		coeff[i] = round(100 * sum_s[i] / common_sum) / 100;
		coeff_sum += coeff[i];
	}

	// если сумма коэффициентов не равна 1
	if (coeff_sum < 1.0 || coeff_sum > 1.0)
	{
		// поиск максимума
		int max = 0;
		for (int i = 0; i < amount; i++)
		{
			if (coeff[i] > coeff[max])
			{
				max = i;
			}
		}

		// исправление ошибок округления
		coeff[max] += 1.0 - coeff_sum;
	}

	// вывод весовых коэффициентов
	cout << "Весовые коэффициенты: " << endl;
	for (int i = 0; i < amount; i++)
	{
		cout << fixed;
		cout << "Критерий " << i + 1 << ": " << setprecision(2) << coeff[i] << endl;
	}

	for (int i = 0; i < amount; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	delete[] sum_s;
	delete[] coeff;

	cout << endl;
	system("pause");
	return 0;
}
