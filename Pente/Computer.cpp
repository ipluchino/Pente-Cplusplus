#include "Computer.h"

//Default Constructor
Computer::Computer()
{
}

//Parametric Constructor to start a new game
Computer::Computer(char a_computerColor) : Player()
{
}

void Computer::MakePlay(Board& a_board)
{
	cout << "The computer made a random play" << endl;
}
