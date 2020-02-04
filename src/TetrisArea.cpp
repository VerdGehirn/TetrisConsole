#include "TetrisArea.h"

TetrisArea::TetrisArea(int _width, int _height):
    width(_width), height(_height)
{
    score = 0;
    m_area.resize(width*height, 0);
}

TetrisArea::~TetrisArea()
{
    //dtor
}

void TetrisArea::Draw(GameController& _controler)
{
    for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
    {
        if(getInfo(i, j))
            _controler.Set(i, j, getInfo(i, j));
    }
    int color = FOREGROUND_RED | FOREGROUND_BLUE;
    for(int i = 0; i <height; i++)
        _controler.Set(0,       i, color),
        _controler.Set(width-1, i, color);

    for(int i = 0; i < width; i++)
        _controler.Set(i, 0        , color),
        _controler.Set(i, height-1 , color);
}

short TetrisArea::getInfo(int x, int y)
{
    return m_area[x + y*width];
}

void TetrisArea::setInfo(int x, int y, short info)
{
    m_area[x + y*width] = info;
}

void TetrisArea::Check()
{
    for(int y = height; y != 1;)
    {
        bool good = 1;
        for(int x = 1; x < width-1; x++)
            if(getInfo(x, y) == 0)
            {
                good = 0;
                break;
            }
        if(good)
        {
            for(int yy = y; yy != 1; yy--)
                for(int x = 1; x < width-1; x++)
                    setInfo(x, yy, getInfo(x, yy-1));

            score++;
        }
        else
            y--;
    }
}

int TetrisArea::getWidth()
{
    return width;
}

int TetrisArea::getHeight()
{
    return height;
}

void TetrisArea::setScore(int _score)
{
    score = _score;
}

int& TetrisArea::getScore()
{
    return score;
}
