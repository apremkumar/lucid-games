#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include "olcPixelGameEngine.h"

wstring tetromino[7];
int fieldWidth = 12, fieldHeight = 18;
unsigned char *pField = nullptr;

int screenWidth = 80, screenHeight = 30;

int rotate(int x, int y, int r)
{
    switch (r % 4)
    {
    case 0:
        return y * 4 + x;
    case 1:
        return 12 + y - (x * 4);
    case 2:
        return 15 - (y * 4) - x;
    case 3:
        return 3 - y + (x * 4);
    }
    return 0;
}

int main()
{
    // Create assets
    tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
    tetromino[1].append(L"..X..XX...X.....");
    tetromino[2].append(L".....XX..XX.....");
    tetromino[3].append(L"..X..XX..X......");
    tetromino[4].append(L".X...XX...X.....");
    tetromino[5].append(L".X...X...XX.....");
    tetromino[6].append(L"..X...X..XX.....");

    pField = new unsigned char[fieldWidth * fieldHeight];
    for (int x = 0; x < fieldWidth; x++)
        for (int y = 0; y < fieldHeight; y++)
            pField[y * fieldWidth + x] = (x == 0 || x == fieldWidth - 1 || x == fieldHeight - 1) ? 9 : 0;

    wchar_t *screen = new wchar_t[screenWidth * screenHeight];
    for (int i = 0; i < screenWidth * screenHeight; i++)
        screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    bool gameOver = false;

    while (!gameOver)
    {
        for (int x = 0; x < fieldWidth; x++)
            for (int y = 0; y < fieldHeight; y++)
                screen[(y + 2) * screenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * fieldWidth + x]];

        WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &dwBytesWritten);
    }

    return 0;
}