#include "Human.h"

//Default Constructor
Human::Human(): Player()
{
}

void Human::MakePlay(Board& a_board)
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
				return;
			}

			//Obtain the location the human player wants to place the stone.
			location = m_userInput.GetPlayLocation(a_board);

			//Place the stone on the board. location[0] represents the column and location.substr(1, 2) represents the row.
			a_board.PlaceStone(location[0], stoi(location.substr(1, 2)), m_color);
		}
		else
		{
			cout << "Implement request help!" << endl;
		}

	} while (decision != "1");
	
	//Clear any captures and update the player's capture count, if any occur.
	int captures = a_board.ClearCaptures(location[0], stoi(location.substr(1, 2)), m_color);
	m_capturedPairs += captures;
}
