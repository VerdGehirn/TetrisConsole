#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <windows.h>
#include <vector>


class GameController
{
    public:
        GameController(int width, int height, int size);
        virtual ~GameController();

        void Run();
        void Set(short x, short y, short color = FOREGROUND_RED, short chr = 219);
        void Fill(short color = FOREGROUND_RED);
    protected:
        HANDLE m_handler;
        void Draw();
        virtual void Work();
        short width, height, size;
    private:
        COORD m_size;
        //std::unique_ptr<CHAR_INFO[]> m_info = nullptr;
        std::vector<CHAR_INFO> m_info;
};

#endif // GAMECONTROLLER_H
