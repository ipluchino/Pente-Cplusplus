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

	//Place the stone on the board. location[0] represents the column and location.substr(1, 2) represents the row.
	a_board.PlaceStone(location[0], stoi(location.substr(1, 2)), m_color);

	//Explain the play to the user.
	cout << reasoning << endl << endl;

	//Clear any captures and update the player's capture count, if any occur.
	int captures = a_board.ClearCaptures(location[0], stoi(location.substr(1, 2)), m_color);
	m_capturedPairs += captures;
}
