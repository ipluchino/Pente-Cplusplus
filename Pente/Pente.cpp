#include <iostream>
#include "Board.h"
#include "Human.h"

using namespace std;

int main()
{
    Human h;
    Board b;

    b.DisplayBoard();
    h.MakePlay(b);
    b.DisplayBoard();
    h.MakePlay(b);
    b.DisplayBoard();
    b.RemoveStone('B', 18);
    b.DisplayBoard();


}


