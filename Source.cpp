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

	cout << "Выберите действие:" << endl;
	cout << "0. Выход" << endl;
	cout << "1. Проверка 16 задания" << endl;
	cout << "2. Проверка 34 задания" << endl;
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
		cout << "Такой команды не существует \n";
		Sleep(1000);
		system("cls");
		menu();
	}
}