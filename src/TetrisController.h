#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H
#include <GameController.h>
#include "TetrisArea.h"
#include "Piece.h"

class TetrisController : public GameController
{
    public:
        TetrisController(int width, int height, int size);
        virtual ~TetrisController();
    protected:
        Piece m_piece;
        TetrisArea m_area;
        void Work() override;
    private:
        void Input();
        void Logic();
};

#endif // TETRISCONTROLLER_H
