#include <iostream>
#include <SDL.h>
#include "windows.h"
#include "Task34.h"

using namespace std;

void draw(int* arr, int SIZE_M, int SIZE_N);

void task34()
{
    system("cls");
    setlocale(LC_ALL, "Russian");

    int command;
    int lastOnePos;
    int firstOnePos;
    int SIZE_N, SIZE_M;

    int sum = 0;
    int end = 0;
    int cnt = 0;
    int oneFinded = 0;

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
        cout << "Введите размер комнаты M: " << endl;
        cin >> SIZE_M;
        cout << "Введите размер комнаты N: " << endl;
        cin >> SIZE_N;
        if (SIZE_N > 1000 || SIZE_M > 1000)
        {
            cout << "Ошибка. Введите число меньше 1000";
            Sleep(1000);
            system("cls");
            task34();
        }
        break;

    case 2:
        SIZE_M = rand() % 1000;
        SIZE_N = rand() % 1000;
        break;

    default:
        cout << "Такой команды не существует \n";
        Sleep(1000);
        system("cls");
        task34();
    }

    int size = SIZE_M + SIZE_N - 2;
    int* arr = new int[size];

    for (int n = 0; n < SIZE_N - 1; n++)
    {
        arr[n] = 0;
    }
    for (int m = 0; m < SIZE_M - 1; m++)
    {
        arr[SIZE_N - 1 + m] = 1;
    }

    draw(arr, SIZE_M, SIZE_N);

    while (end == 0)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (oneFinded == 0 && arr[i] == 1)
            {
                firstOnePos = i;
                oneFinded = 1;
            }

            if (oneFinded == 1 && arr[i] == 1)
                lastOnePos = i;

            if (arr[i] == 1 && arr[i - 1] == 0)
            {
                arr[i - 1] = 1;
                arr[i] = 0;

                oneFinded = 0;

                for (int j = lastOnePos; j <= firstOnePos; j++)
                    arr[j] = 0;

                for (int j = 0; j < firstOnePos - lastOnePos; j++)
                    arr[size - j - 1] = 1;

                break;
            }

            for (int j = 0; j < SIZE_M - 1; j++)
                if (arr[j] == 1)
                    cnt++;

            if (cnt == SIZE_M - 1)
                end = 1;

            cnt = 0;
        }
        sum++;
        draw(arr, SIZE_M, SIZE_N);
    }
    cout << endl << "Количество маршрутов до выхода из замка: " << sum << endl;
    delete[] arr;
}

void draw(int* arr, int SIZE_M, int SIZE_N)
{
    int width = 1000;
    int height = 500;
    SDL_Rect rect;
    SDL_Renderer* ren = NULL;
    SDL_Window* window = SDL_CreateWindow("graphic", 0, 0, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);

    for (int x = 0; x < SIZE_M; x++)
    {
        for (int y = 0; y < SIZE_N; y++)
        {
            rect = { width / SIZE_M * x, height / SIZE_N * y, width / SIZE_M, height / SIZE_N };
            SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderFillRect(ren, &rect);
            SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderDrawRect(ren, &rect);
        }
    }
    SDL_RenderPresent(ren);
    SDL_Delay(500);

    int x = 0;
    int y = 0;

    rect = { x, y, width / SIZE_M, height / SIZE_N };
    SDL_SetRenderDrawColor(ren, 89, 22, 166, 0xFF);
    SDL_RenderFillRect(ren, &rect);

    for (int p = 0; p < SIZE_M + SIZE_N - 2; p++)
    {
        if (arr[p] == 1)
        {
            x += width / SIZE_M;
            rect = { x, y, width / SIZE_M, height / SIZE_N };
            SDL_RenderFillRect(ren, &rect);
        }
        if (arr[p] == 0)
        {
            y += height / SIZE_N;
            rect = { x, y, width / SIZE_M, height / SIZE_N };
            SDL_RenderFillRect(ren, &rect);
        }
    }
    SDL_RenderPresent(ren);
    SDL_Delay(300);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
}