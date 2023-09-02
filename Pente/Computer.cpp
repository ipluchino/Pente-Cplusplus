#include "Computer.h"

//Default Constructor
Computer::Computer()
{
}

//Parametric Constructor to start a new game
Computer::Computer(char a_computerColor) : Player(a_computerColor, 0, 0)
{
}

void Computer::MakePlay(Board& a_board)
{

}
