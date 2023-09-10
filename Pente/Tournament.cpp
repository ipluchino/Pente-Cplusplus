#include "Tournament.h"

//Default Constructor
Tournament::Tournament()
{
}

//Creates a new Tournament.
void Tournament::CreateNewGame()
{
	//Determine who is white/black.
	//m_round = Round('W', 'B');


}

//Loads the tournament from a file.
bool Tournament::LoadGame()
{
	bool successfullyLoaded = m_round.LoadGameData();
	return successfullyLoaded;
}

//Main game 
void Tournament::StartTournament()
{
	cout << "Welcome to Pente!" << endl;

	//If the user decides to load from a file, obtain the file name and load the game. Otherwise, start a new game.
	//Continue to ask the user what they would like to do until they either start a new game or successfully load a game from a file.
	bool success = false;
	while (!success)
	{
		string choice = m_userInput.GetTournamentChoice();

		if (choice == "2")
		{
			success = LoadGame();
		}
		else
		{
			//The user would like to start a new game.
			success = true;
		}
	}

	do 
	{
		m_round.StartRound();
		
		//SCORE ROUND WHEN IT ENDS
	} while (Continue());		// SHOULD BE while(Continue())
}

bool Tournament::Continue()
{
	string choice = m_userInput.GetContinueDecision();

	if (choice == "Y")
	{
		return true;
	}
	else
	{
		cout << "Thanks for playing!" << endl;
		return false;
	}
}

