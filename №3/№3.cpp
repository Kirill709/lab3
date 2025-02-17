// №3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

// string в double(отправлять только числа)
double StrtoInt(string line)
{
	double a = 0.0;
	int k = 0, l = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (k > 0)
			k++;
		if (line[i] == '-')
			l++;
		else if (line[i] == '.')
			k++;
		else
		{
			a = a + (line[i] & 0x0F);
			a = a * 10.0;
		}
	}
	for (int i = 1; i < k; i++)
		a = a * 0.1;
	a = a / 10.0;
	if (l == 1)
		return a * (-1.0);
	else
		return a;
}
//Подсчет факториала
int factor(int n)
{
	int k = 1;
	for (int i = 2; i <= n; i++) k *= i;
	return k;
}
// Формула для подсчета конечной Разности
// из i вычитаем j
double delta(double i, double j, int n, double* y)
{
	if (n == 0) return i - j;
	else if (n == 1) return (y[(int)i] - y[(int)j]);
	else return delta(delta(i + 1, j + 1, n - 1, y), delta(i, j, n - 1, y), 0, y);
}
//Перемножение матриц с d - строки и столбцы 1-й матрицы, f - 2-й столбец
void multiply(double** A, double* B, double* C, int c, int d)
{
	for (int i = 0; i <=c; i++)
	{
		for (int r = 0; r <=d; r++)
		{
			C[i] += A[i][r] * B[r]; 
			cout << C[i] << "\t";
		}
		cout << endl;

	}
}

double Lagrange_poly(double x, double temp_arr[])
{
	double fx, sum = 0.0;
	ofstream node;
	node.open("Nodes1.txt");
	for (int i = 0; i <= 11; i++)
	{
		fx = 1;
		for (int j = 0; j <= 11; j++)
		{
			if (i != j)
				fx *= (x - (double)j) / ((double)i - (double)j);
		}
		fx *= temp_arr[i];
		sum += fx;
	}
	for (int i = 0; i <= 11; i++)
		node << i + 1 << " " << temp_arr[i] << endl;
	node.close();
	return sum;
}

double Newton_first_form(double x, double temp_arr[])
{
	double sum = 0.0;
	double fx = 0.0;
	ofstream node;
	node.open("Nodes2.txt");
	for (int i = 0; i <= 5; i++)
	{
		if (i == 0) { sum += temp_arr[0]; }
		else
		{
			fx = 1;
			for (int j = 0; j < i; j++) fx *= (x - (double)j);

			fx /= factor(i);
			fx *= delta(1, 0, i, temp_arr);
		}
		sum += fx;
	}
	for (int i = 0; i <= 5; i++)
		node << i + 1 << " " << temp_arr[i] << endl;
	node.close();

	return sum;
}

double Newton_second_form(double x, double temp_arr[])
{
	double sum = 0.0;
	double fx;
	ofstream node;
	node.open("Nodes3.txt");
	for (int i = 0; i <= 5; i++)
	{
		fx = 1;
		if (i == 0) { sum += temp_arr[5]; }
		else {
			for (int j = 5; j >= 5 - i + 1; j--)  fx *= (x - (double)j);
			fx /= factor(i);
			fx *= delta(5 - i + 1, 5 - i, i, temp_arr);
			sum += fx;
		}
	}
	for (int i = 0; i < 6; i++)
		node << i + 1 << " " << temp_arr[i] << endl;
	node.close();
	return sum;
}

double Steppolinom(double x, int s, double* koef)
{
	double y = 0.0;
	for (int i = 0; i <= s; i++)
		y += koef[i] * pow(x, i);
	return y;
}
//------------------------------------------------------------------------------
// Декларация скрипта. Чтобы не путать, он внизу.
void invert(double** A, int n);
template <typename T> void FreeMem(T **matr, int n);
template <typename T> void PrintMtx(T **matr, int n);
template <typename T> void TransponMtx(T **matr, T **tMatr, int n);
void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol);
int Det(int **matr, int n);
//------------------------------------------------------------------------------


int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream main_file;
	ofstream temp_file;
	int k_count = 0, l_count = 0, mounth, one_off = 1;
	double z;
	double intel[192][14], temp1[12];
	string line, big_line, small_line;

	//Считывание данных:
	main_file.open("Yakutsk.csv");
	do
	{
		if (one_off == 1)
		{
			getline(main_file, line);
			one_off = 0;
		}
		else
		{
			getline(main_file, line);
			big_line = big_line + line + ",";
		}
	} while (!main_file.eof());
	for (int i = 0; i < big_line.length(); i++)
	{
		if (big_line[i] != ',')
		{
			small_line += big_line[i];
		}
		else
		{
			intel[l_count][k_count] = StrtoInt(small_line);
			small_line.clear();
			k_count++;
		}
		if (k_count == 14)
		{
			l_count++;
			k_count = 0;
		}
	}

	//Вывод считанных данных
	cout << "Год\t|янв\t|фев\t|мар\t|апр\t|май\t|июн\t|июл\t|авг\t|сен\t|окт\t|ноя\t|дек\t|средняя|";
	cout << "\n-----------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < 191; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (intel[i][j] == 999.9)
			{
				cout << "-" << "\t|";
			}
			else
				cout << intel[i][j] << "\t|";
		}
		cout << "\n-----------------------------------------------------------------------------------------------------------------\n";
	}
	line.clear(); big_line.clear();

	//Подбор 12 элементов подхожящих условию:
	cout << "Enter mounth[1-12] or average[13]: ";
	cin >> mounth;
	cout << "Enter line[1-173]: ";
	cin >> k_count;
	l_count = 0;
	do
	{
		if (intel[k_count][mounth] != 999.9)
		{
			temp1[l_count] = intel[k_count][mounth];
			l_count++;
		}
		k_count++;
	} while (l_count != 12);

	//Интерполяционный полином Лагранжа:
	temp_file.open("Lagrange_Data.txt");
	for (double i = 0; i <= 11; i += 0.1)
	{
		z = Lagrange_poly(i, temp1);
		temp_file << i + 1 << "\t " << z << endl;
	}
	temp_file.close();

	//Первая интерполяционная формула Ньютона:
	temp_file.open("FirstNewton_Data.txt");
	for (double i = 0; i <= 5; i += 0.1)
	{
		z = Newton_first_form(i, temp1);
		temp_file << i + 1 << "\t " << z << endl;
	}
	temp_file.close();

	//Вторая интерполяционная формула Ньютона:
	temp_file.open("SecondNewton_Data.txt");
	for (double i = 0; i <= 5; i += 0.1)
	{
		z = Newton_second_form(i, temp1);
		temp_file << i + 1 << "\t " << z << endl;
	}
	temp_file.close();

	///Степенной полином:
	temp_file.open("Steppolinom.txt");
	cout << "Enter pow of polinom you want to have[1-5]: ";
	int grade;
	cin >> grade;
	cout << "Enter month you want to see[1-12]: ";
	int month;
	cin >> month;

	vector<double>  temperature;
	vector<double> stroki;
	double nstrok = 0.0;
	for (int i = 0; i < 191; i++)
		if (intel[i][month] != 999.9)
		{
			temperature.push_back(intel[i][month]);
			nstrok++;
			stroki.push_back(nstrok);
		}

	cout << "Amount of right degrees: " << temperature.size() << endl;

	int n1 = stroki.size(); /// количество переменных

//Создадём матрицу для значений y(температур) || Правая часть уравнения
	double* secondmat = new double[grade];
	for (int i = 0; i <= grade; i++)
		secondmat[i] = 0.0;
	for (int i = 0; i <= grade; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			secondmat[i] += temperature[j] * pow(stroki[j], i); 			
		}
	}
// Создадим матрицу сумм произведений х в разных степенях|| Самая большая матрица в уравнении
	double** firstmat = new double*[grade];
	for (int i = 0; i <= grade; i++)
		firstmat[i] = new double[grade];
//Зануление
	for (int i = 0; i <= grade; i++)
	{
		for (int j = 0; j <= grade; j++)
		{
				firstmat[i][j] = 0.0;
		}		
	}
	
	for (int i = 0; i <= grade; i++)
	{
		for (int j = 0; j <= grade; j++)
		{
			if ((i == 0) && (j == 0))
				firstmat[i][j] = n1;
			else
			{
				for (int k = 0; k < n1; k++)
					firstmat[i][j] += pow(stroki[k], i + j);
			}
		}
	}

//Создадим матрицу коэффициентов || то, что ищем
	double *koef = new double[grade];
	for (int i = 0; i <= grade; i++)
		koef[i] = 1.0;

	invert(firstmat, grade);

	multiply(firstmat, secondmat, koef, grade, grade);
	/*cout << "Matryx factor: " << endl;
	for (int i = 0; i <= grade; i++)
	{
		cout << i << "\t |";
		cout << koef[i] << "\t |";
		cout << endl;
	}
	cout << endl;
*/
	int h = stroki[n1-1];
	for (double i = 0; i < h; i += 0.1)
		temp_file << i << "\t  " << Steppolinom(i, grade, koef) << endl;

	temp_file.close();
	main_file.close();
	system("pause");
	return 0;
}

//==============================================================================================================
//                              Скрипт инверсии матрицы
//==============================================================================================================
// main скрипта
void invert(double** A, int n)
{
	int det;
	int **matr = new int *[n];
	double **obr_matr = new double *[n];
	double **tobr_matr = new double *[n];
	for (int i = 0; i < n; i++) {
		matr[i] = new int[n];
		obr_matr[i] = new double[n];
		tobr_matr[i] = new double[n];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matr[i][j] = A[i][j];
	det = Det(matr, n);
	cout << "Det = " << det << endl;
	if (det) {
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++) 
			{
				int m = n - 1;
				int **temp_matr = new int *[m];
				for (int k = 0; k < m; k++)
					temp_matr[k] = new int[m];
				Get_matr(matr, n, temp_matr, i, j);
				obr_matr[i][j] = pow(-1.0, i + j + 2) * Det(temp_matr, m) / det;
				FreeMem(temp_matr, m);
			}
		}
	}
	else
		cout << "Det = 0,\nDet not exist!!!" << endl;
	//Транспонирование матрицы
	TransponMtx(obr_matr, tobr_matr, n);
	//Печать обратной матрицы после транспонирования
	//PrintMtx(tobr_matr, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j]=matr[i][j];
	FreeMem(tobr_matr, n);
	FreeMem(matr, n);
	FreeMem(obr_matr, n);
}
//Функция транспонирования матрицы
template <typename T> void TransponMtx(T **matr, T **tMatr, int n) 
{//
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tMatr[j][i] = matr[i][j];
}
//Функция освобождения памяти
template <typename T> void FreeMem(T **matr, int n)
{
	for (int i = 0; i < n; i++)
		delete[] matr[i];
	delete[] matr;
}
//Функция печати матрицы(для фикса, вызывать в "void invert(double** A, int n)" )
template <typename T> void PrintMtx(T **matr, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matr[i][j] << " ";
		cout << endl;
	}
}
//Функция вычеркивания строки и столбца
void Get_matr(int **matr, int n, int **temp_matr, int indRow, int indCol)
{
	int ki = 0;
	for (int i = 0; i < n; i++) {
		if (i != indRow) {
			for (int j = 0, kj = 0; j < n; j++) {
				if (j != indCol) {
					temp_matr[ki][kj] = matr[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
}
//Функция вычисления определителя матрицы
int Det(int **matr, int n)
{
	int temp = 0;   //временная переменная для хранения определителя
	int k = 1;      //степень
	if (n < 1) {
		//cout << "Не верный размер матрицы!!!" << endl;
		return 0;
	}
	else if (n == 1)
		temp = matr[0][0];
	else if (n == 2)
		temp = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
	else {
		for (int i = 0; i < n; i++) {
			int m = n - 1;
			int **temp_matr = new int *[m];
			for (int j = 0; j < m; j++)
				temp_matr[j] = new int[m];
			Get_matr(matr, n, temp_matr, 0, i);
			temp = temp + k * matr[0][i] * Det(temp_matr, m);
			k = -k;
			FreeMem(temp_matr, m);
		}
	}
	return temp;
}















