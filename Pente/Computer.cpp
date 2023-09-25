/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Computer class - implementation file.
* Date : 9/27/23
************************************************************/

#include "Computer.h"

/* *********************************************************************
Function Name: Computer - Default constructor
Purpose: To construct a Computer object.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Computer::Computer(): Player()
{
}

/* *********************************************************************
Function Name: MakePlay
Purpose: To let the computer player make its play.
Parameters:
			a_board, a Board object passed by reference. The board is passed by reference so it is updated with the computer's move.
Return Value: Whether the computer successfully made a move or the game was suspended to be saved, a boolean value.
Algorithm:
			1) Ask the user if they would like to let the computer place it's tile or save the game.
				1a) If they would like to save the game, return false. Otherwise continue.
			2) Determine the optimal play based on the OptimalPlay function in the Player class.
			3) Place the stone on the passed Board object.
			4) Display the reasoning for the computer's play.
			5) Remove any captured pairs from the board, if they occur, and add them to the computer's captured pair count.
Assistance Received: None
********************************************************************* */
bool Computer::MakePlay(Board& a_board)
{
	string decision = m_userInput.GetComputerDecision();

	//The user would like to save and exit the game before the computer places a tile.
	if (decision == "2") return false;

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

	return true;
}
