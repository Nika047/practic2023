#include <iostream>
#include <fstream>
#include <ctime>
#include "windows.h"
#include "Task16.h"

using namespace std;

int p, q;
int k = 0;

void task16()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int N, pr, len;
	int command = 0;

	cout << "Выберите способ задания размера матрицы" << endl;
	cout << "0. Выход" << endl;
	cout << "1. С помощью клавиатуры" << endl;
	cout << "2. Задается случайное число" << endl;
	cin >> command;
	system("cls");

	switch (command)
	{
	case 0:
		exit(0);

	case 1:
		cout << "Введите размер матрицы: ";
		cin >> N;
		if (N > 200)
		{
			cout << "Ошибка. Введите число меньше 200";
			Sleep(1000);
			system("cls");
			task16();
		}
		system("cls");
		break;

	case 2:
		N = rand() % 200;
		break;

	default:
		cout << "Такой команды не существует \n";
		Sleep(1000);
		system("cls");
		task16();
	}

	clock_t startClock = clock();

	int** arrIn = new int* [N];
	for (int i = 0; i < N; i++)
		arrIn[i] = new int[N];

	int** arrOut = new int* [N];
	for (int i = 0; i < N; i++)
		arrOut[i] = new int[N];

	fstream file;

	file.open("neamum.in", ios_base::out);
	file << N << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			pr = rand() % 10;
			arrIn[i][j] = (pr < 5) ? 0 : rand() % 1000000;
			file << arrIn[i][j] << " ";
			cout.width(7);
			cout << arrIn[i][j] << " || ";
		}
		file << endl;
		cout << endl;
	}
	file.close();

	file.open("neamum.in", ios_base::in);

	file >> N;
	while (!file.eof())
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				file >> arrIn[i][j];
	file.close();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (arrIn[i][j] != 0)
				arrOut[i][j] = arrIn[i][j];

			else
			{
				int d = 1;
				verticalHorizontal(arrIn, i, j, N, d);
				arrOut[i][j] = (k == 1) ? arrIn[p][q] : -k;
			}
			k = 0;
		}
	}

	ofstream fout("nearnum.оut", ios::out);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fout.width(7);
			fout << arrOut[i][j] << " || ";
		}
		fout << endl;
	}

	fout.close();
	file.close();

	for (int i = 0; i < N; i++)
		delete[] arrOut[i];
	delete[] arrOut;

	for (int i = 0; i < N; i++)
		delete[] arrIn[i];
	delete[] arrIn;

	clock_t stopClock = clock();
	cout << "Время работы программы = " << (stopClock - startClock) / 1000.0 << " секунды" << endl;
}

void verticalHorizontal(int** arrIn, int i, int j, int N, int d)
{
	if ((i < N - d) && (arrIn[i + d][j] != 0))
	{
		k += 1;
		p = i + d;
		q = j;
	}
	if ((i >= d) && (arrIn[i - d][j] != 0))
	{
		k += 1;
		p = i - d;
		q = j;
	}
	if ((j < N - d) && (arrIn[i][j + d] != 0))
	{
		k += 1;
		p = i;
		q = j + d;
	}
	if ((j >= d) && (arrIn[i][j - d] != 0))
	{
		k += 1;
		p = i;
		q = j - d;
	}

	if (k == 0)
		diagonal(arrIn, i, j, N, d);
}

void diagonal(int** arrIn, int i, int j, int N, int d)
{
	if ((i < N - d) && (j < N - d) && (arrIn[i + d][j + d] != 0))
	{
		k += 1;
		p = i + d;
		q = j + d;
	}
	if ((i < N - d) && (j >= d) && (arrIn[i + d][j - d] != 0))
	{
		k += 1;
		p = i + d;
		q = j - d;
	}
	if ((i >= d) && (j < N - d) && (arrIn[i - d][j + d] != 0))
	{
		k += 1;
		p = i - d;
		q = j + d;
	}
	if ((i >= d) && (j >= d) && (arrIn[i - d][j - d] != 0))
	{
		k += 1;
		p = i - d;
		q = j - d;
	}

	if (k == 0)
	{
		d++;
		if (d = 2 * (N - 1))
			return;
		verticalHorizontal(arrIn, i, j, N, d);
	}
}