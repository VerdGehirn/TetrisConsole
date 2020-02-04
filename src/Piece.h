#ifndef PIECE_H
#define PIECE_H
#include <array>
#include <string>
#include "GameController.h"
#include "TetrisArea.h"

enum
{
    ROT_TOP,
    ROT_LEFT,
    ROT_BOT,
    ROT_RIGHT
};

class Piece
{
    bool prevup = false;
    public:
        Piece(TetrisArea& _area);
        virtual ~Piece();
        void Draw(GameController& _controller);
        void Input(int width);
        short Index(int x, int y, int rotation);
        bool isCollision(int x, int y, int rotation);
        void Reset();
    private:
        std::array<std::string, 8> shapes;
        int sx, sy, timer;
        int current = 0;
        int rotation;
        int color;
        TetrisArea* area = nullptr;
};

#endif // PIECE_H
