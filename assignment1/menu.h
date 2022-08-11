#ifndef MENU_H
#define MENU_H
#include "chess.h"


class menu
{
    public:
        Menu(){};
        void Run();

    private:
        int MenuPrint();
        void printElement();
        void putElement();
        void putVector();
        void printSize();
        void addChesses();
        void multiplyChesses();
        void print();
        void file();
        void addSecondChess();
        void multiplySecondChess();
        chess c;
};

#endif // MENU_H
