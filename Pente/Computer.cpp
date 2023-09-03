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
	//Obtain the optimal play given the current board. 
	//playInfo.first is the location of the play, while playInfo.second is the reasoning for that play. 
	pair<string, string> playInfo = OptimalPlay(a_board, m_color);
	string location = playInfo.first;
	string reasoning = playInfo.second;

	//Place the stone on the board.
	a_board.PlaceStone(location[0], stoi(location.substr(1, 2)), m_color);

	//Explain the play to the user.
	cout << reasoning << endl << endl;
}
