#include "GameController.h"
#include <stdio.h>

GameController::GameController(int width, int height, int size) :
    width(width), height(height), size(size)
{
    m_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    m_info.resize(width*height);
    m_size = {width, height};
}

GameController::~GameController()
{
    //dtor
}

void GameController::Run()
{
    while(69)
    {
        Work();
        Draw();
    }
}

void GameController::Work()
{

}

void GameController::Draw()
{
    SMALL_RECT rect = {0, 0, m_size.X*size, m_size.Y*size};
    COORD t_size = {m_size.X*size, m_size.Y*size};

    CHAR_INFO temp[width*height*size*size] = {};

    for(int i = 0; i < width*height; i++)
    {
        int x = i % width*size;
        int y = i / width*size;

        //temp[x + y*width*size] = m_info[i];

        for(int k = 0; k < size; k++) for(int l = 0; l < size; l++) temp[x+k + (l+y)*width*size] = m_info[i];
    }

    WriteConsoleOutput(m_handler, temp, t_size, {0, 0}, &rect);

}

void GameController::Set(short x, short y, short color, short chr)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
    {
        //printf("Out X:%i Y:%i W:%i H:%i\n", x, y, height, width);
        return;
    }

    int index = x + y*m_size.X;
    m_info[index].Char.AsciiChar = chr;
    m_info[index].Attributes = color;
}

void GameController::Fill(short color)
{
    for(int i = 0; i < width*height; i++)
        Set(i%width, i/width, color);
}
