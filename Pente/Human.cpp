#include "Human.h"

/* *********************************************************************
Function Name: Human - Default constructor
Purpose: To construct a Human object.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Human::Human(): Player()
{
}

/* *********************************************************************
Function Name: MakePlay
Purpose: To let the human player make its play.
Parameters:
			a_board, a Board object passed by reference. The board is passed by reference so it is updated with the human's move.
Return Value: Whether the human successfully made a move or the game was suspended to be saved, a boolean value.
Algorithm:
			1) Ask the user if what they would like to place a tile, ask for help, or save and exit the game.
				1a) If they request help, display the optimal play and its explanation using the OptimalPlay function in the Player class.
				1b) If they want to save and exit the game, return false.
			2) If the human is making the first move of the game, place the stone on J10.
			3) Otherwise, place the stone on the passed Board object.
			4) Remove any captured pairs from the board, if they occur, and add them to the human's captured pair count.
Assistance Received: None
********************************************************************* */
bool Human::MakePlay(Board& a_board)
{
	string decision;
	string location;

	do 
	{
		decision = m_userInput.GetHumanDecision();

		if (decision == "1")
		{
			//If the board is empty, you can only play on J10 so no human input is required.
			if (a_board.IsEmptyBoard())
			{
				a_board.PlaceStone('J', 10, m_color);
				cout << "You placed your stone on J10 because the player that goes first must place it here." << endl << endl;
				return true;
			}

			//Obtain the location the human player wants to place the stone.
			location = m_userInput.GetPlayLocation(a_board);

			//Place the stone on the board. location[0] represents the column and location.substr(1, 2) represents the row.
			a_board.PlaceStone(location[0], stoi(location.substr(1, 2)), m_color);
		}
		else if (decision == "2")
		{
			string help = AskForHelp(a_board);
			cout << help << endl << endl;
		}
		else
		{
			//The user wants to save and exit the game.
			return false;
		}

	} while (decision != "1");
	
	//Clear any captures and update the player's capture count, if any occur.
	int captures = a_board.ClearCaptures(location[0], stoi(location.substr(1, 2)), m_color);
	m_capturedPairs += captures;

	return true;
}

//Returns the most optimal play to the user.
//Assistance: https://cplusplus.com/reference/string/string/replace/
string Human::AskForHelp(Board a_board)
{
	pair<string, string> playInfo = OptimalPlay(a_board, m_color);
	string explanation = playInfo.second;
	
	//Alter the output of the explanation to present it as a suggestion.
	string toFind = "placed";

	explanation.replace(explanation.find(toFind), toFind.length(), "recommends you place");
	return explanation;
}
