#ifndef TETRISAREA_H
#define TETRISAREA_H
#include <vector>
#include "GameController.h"

#define TETRIS_W 10
#define TETRIS_H 20


class TetrisArea
{
    int width, height;
    std::vector<short> m_area;
    int score;
    public:
        TetrisArea(int _width, int _height);
        virtual ~TetrisArea();
        void Draw(GameController& _controler);
        void setScore(int _score);
        void Check();
        int& getScore();
        short getInfo(int x, int y);
        void setInfo(int x, int y, short info);
        int getWidth();
        int getHeight();
};

#endif // TETRISAREA_H
