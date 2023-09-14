#include <iostream>
#include "Tournament.h"

using namespace std;

int main()
{
    Tournament t;
    t.StartTournament();

    /*
    Board b;
    Player p;

    b.PlaceStone('C', 6, 'B');
   //b.PlaceStone('D', 7, 'B');
    b.PlaceStone('E', 8, 'B');
    b.PlaceStone('F', 9, 'B');

    b.PlaceStone('A', 1, 'B');
    b.PlaceStone('A', 2, 'B');
    b.PlaceStone('A', 3, 'B');

    b.PlaceStone('P', 19, 'B');
    b.PlaceStone('Q', 19, 'B');
    b.PlaceStone('R', 19, 'B');

    b.DisplayBoard();

    auto res = p.FindAllMoves(b, 3, 'B');

    for (auto a : res)
    {
        for (auto c : a)
        {
            cout << b.IntToCharacter(c[1]) << " " << b.ConvertRowIndex(c[0]) << endl;
        }
        cout << endl;
    }

    for (auto a : res)
    {
        auto empty = p.FindEmptyIndices(b, a);

        for (auto b : empty)
        {
            cout << b << " ";
        }

        cout << endl;
    }

    cout << endl;

    for (auto a : res)
    {
        auto empty = p.FindEmptyIndices(b, a);

        for (auto c : empty)
        {
            int adjacent = p.FindConsecutiveIfPlaced(b, a, c);
            cout << adjacent << " ";
        }

        cout << endl;
    }

    cout << endl << endl;
    cout << "PLACEMENTS" << endl;
    for (int i = 0; i < 10; i++)
    {
        vector<int> q = p.BuildInitiative(b, 1, 'B');
        cout << b.IntToCharacter(q[1]) << " " << b.ConvertRowIndex(q[0]) << endl;
    }
    */
}


