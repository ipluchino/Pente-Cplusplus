#include <iostream>
#include "Board.h"
#include "Human.h"
#include "UserInput.h"

using namespace std;

int main()
{
    Human h;
    Board b;
    UserInput u;

   
    b.DisplayBoard();
    h.MakePlay(b);
    b.DisplayBoard();
    h.MakePlay(b);
    b.DisplayBoard();
    h.MakePlay(b);
    b.DisplayBoard();



}


