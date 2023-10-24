#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Task16.h"
#include "Task34.h"

using namespace std;

void menu();

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SDL_Init(SDL_INIT_EVERYTHING);
	menu();

	return EXIT_SUCCESS;
}

void menu()
{
	int command;

	cout << "�������� ��������:" << endl;
	cout << "0. �����" << endl;
	cout << "1. �������� 16 �������" << endl;
	cout << "2. �������� 34 �������" << endl;
	cin >> command;
	system("cls");

	switch (command)
	{
	case 0:
		exit(0);

	case 1:
		task16();
		break;

	case 2:
		task34();
		break;

	default:
		cout << "����� ������� �� ���������� \n";
		Sleep(1000);
		system("cls");
		menu();
	}
}