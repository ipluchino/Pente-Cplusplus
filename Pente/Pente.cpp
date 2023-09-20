#include <iostream>
#include "Tournament.h"

using namespace std;

int main()
{
    Tournament t;
    t.StartTournament();


    Board b;
    Human h;

    b.PlaceStone('C', 3, 'W');
    b.PlaceStone('E', 4, 'W');
    b.PlaceStone('C', 6, 'W');
    b.PlaceStone('D', 5, 'W');
    b.PlaceStone('E', 5, 'W');

    b.PlaceStone('N', 19, 'W');
    b.PlaceStone('N', 18, 'W');
    b.PlaceStone('N', 16, 'W');

    b.DisplayBoard();

    h.MakePlay(b);

}


