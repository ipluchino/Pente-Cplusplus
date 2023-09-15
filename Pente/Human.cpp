#include "Human.h"

//Default Constructor
Human::Human(): Player()
{
}

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
