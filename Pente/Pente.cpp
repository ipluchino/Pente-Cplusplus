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

    b.PlaceStone('A', 14, 'B');
    b.PlaceStone('C', 9, 'B');
    b.PlaceStone('J', 1, 'B');
    b.PlaceStone('Q', 7, 'B');
    b.DisplayBoard();

    string location = u.GetPlayLocation(b);
    cout << "Valid location: " << location << endl;


}


