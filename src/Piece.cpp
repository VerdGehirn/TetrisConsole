#include "Piece.h"
#include "GameController.h"
#include <time.h>

Piece::Piece(TetrisArea& _area)
{
    srand(time(0));
    Reset();
    area = &_area;
    timer = 0;
    shapes[0] = "";
    shapes[0] += "....";
    shapes[0] += "L...";
    shapes[0] += "LLLL";
    shapes[0] += "....";

    shapes[1] = "";
    shapes[1] += "....";
    shapes[1] += "LL..";
    shapes[1] += ".LL.";
    shapes[1] += "....";

    shapes[2] = "";
    shapes[2] += "....";
    shapes[2] += ".L..";
    shapes[2] += "LLL.";
    shapes[2] += "....";

    shapes[3] = "";
    shapes[3] += "....";
    shapes[3] += ".LL.";
    shapes[3] += ".LL.";
    shapes[3] += "....";

    shapes[4] = "";
    shapes[4] += "L...";
    shapes[4] += "L...";
    shapes[4] += "L...";
    shapes[4] += "L...";

    shapes[5] = "";
    shapes[5] += "....";
    shapes[5] += "...L";
    shapes[5] += "LLLL";
    shapes[5] += "....";
}

void Piece::Draw(GameController& _controller)
{
    int cx = sx;
    int cy = sy;
    while(!isCollision(cx, ++cy, rotation));
        cy--;
    for(int i = 0; i < 16; i++)
    {
        int x = i % 4;
        int y = i / 4;

        if(shapes[current][Index(x, y, rotation)] == 'L') _controller.Set(cx + x, cy + y, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    for(int i = 0; i < 16; i++)
    {
        int x = i % 4;
        int y = i / 4;

        if(shapes[current][Index(x, y, rotation)] == 'L') _controller.Set(sx + x, sy + y, color);
    }
}

void Piece::Reset()
{
    sy = 1;
    sx = rand()%6+2;
    current = rand() % 6;
    rotation = 0;
    switch(rand()%3)
    {
    case 0:
        color = FOREGROUND_BLUE;
        break;
    case 1:
        color = FOREGROUND_RED;
        break;
    case 2:
        color = FOREGROUND_GREEN;
        break;
    }
}

void Piece::Input(int width)
{
    auto reset = [&]()
    {
        area->setScore(0);
        for(int i = 0 ; i<area->getHeight()*area->getWidth();i++)
            area->setInfo(i%width, i/width, 0);
    };

    if(GetKeyState(VK_F2) & 0x8000)
    {
        Reset();
        area->Check();
        reset();
    }


    timer++;
    bool temp = timer%450==0;
    if(GetKeyState(VK_DOWN) & 0x8000)
        temp = timer%75==0;

    if(temp)
    {
        if(!isCollision(sx, sy+1, rotation))
            sy++;
        else
        {
            for(int i = 0; i < 16; i++)
            {
                int x = i % 4;
                int y = i / 4;

                if(shapes[current][Index(x, y, rotation)] == 'L')
                    area->setInfo(sx+x, sy+y, color);
            }
            Reset();
            area->Check();
            if(isCollision(sx, sy, rotation))
            {
                reset();
            }
        }
    }


    if(GetKeyState(VK_LEFT) & 0x8000)
        if(timer%75==0)
            if(!isCollision(sx-1, sy, rotation))
                sx--;
    if(GetKeyState(VK_RIGHT) & 0x8000)
        if(timer%75==0)
            if(!isCollision(sx+1, sy, rotation))
                sx++;


    if(GetAsyncKeyState(VK_UP) < 0)
    {
        if(!prevup)
            if(!isCollision(sx, sy, rotation+1))
            rotation++;
        rotation %= 4;
        prevup = true;
    }
    else
        prevup = false;
}

short Piece::Index(int x, int y, int rotation)
{
        int index = 0;
        switch(rotation%4)
        {
        case ROT_TOP:
                index = x + y*4;
            break;
        case ROT_LEFT:
                index = 12 + y - x*4;
            break;
        case ROT_BOT:
                index = 15-y*4-x;
            break;
        case ROT_RIGHT:
                index = 3-y+x*4;
            break;
        }
        return index;
}

bool Piece::isCollision(int x, int y, int rotation)
{
    for(int i = 0; i < 16; i++)
    {
        int _x = i % 4;
        int _y = i / 4;
        int globalx = x + _x;
        int globaly = y + _y;


        if(area->getInfo(globalx, globaly) || globalx <= 0 || globalx >= area->getWidth() -1 || globaly <= 0 || globaly >= area->getHeight()-1)
            if(shapes[current][Index(_x, _y, rotation)] == 'L')
                return true;

        //if(area->getInfo(x + tx, y + ty) && shapes[current][Index(_x, _y)] == 'L')
        //    return true;
    }
    return false;
}

Piece::~Piece()
{
    //dtor
}
