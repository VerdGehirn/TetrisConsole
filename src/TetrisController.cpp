#include "TetrisController.h"

TetrisController::TetrisController(int width, int height, int size) :
    GameController(width, height, size), m_area(width, height), m_piece(m_area)
{
}

TetrisController::~TetrisController()
{

}

void TetrisController::Work()
{
    Fill(0);
    Input();
    m_area.Draw(*this);
    m_piece.Draw(*this);
    Logic();
}


void TetrisController::Input()
{
    m_piece.Input(width);
}

void TetrisController::Logic()
{
    std::string str = std::to_string(m_area.getScore());
    SetConsoleTitle(str.c_str());
}
