#include <iostream>
#include "Tournament.h"

using namespace std;

int main()
{
    Tournament t;
    t.StartTournament();

    
    Board b;
    Human h;

    b.PlaceStone('C', 3, 'B');
    b.PlaceStone('C', 4, 'B');
    b.PlaceStone('C', 6, 'B');
    b.PlaceStone('D', 5, 'W');
    b.PlaceStone('E', 5, 'B');

    b.DisplayBoard();

    h.MakePlay(b);


}


