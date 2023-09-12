#include "Tournament.h"

//Default Constructor
Tournament::Tournament()
{
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

	} while (Continue());		
}

bool Tournament::Continue()
{
	cout << "Human's new Tournament Score: " << m_round.GetHumanScore() << endl;
	cout << "Computer's new Tournament Score: " << m_round.GetComputerScore() << endl << endl;
	
	string choice = m_userInput.GetContinueDecision();

	if (choice == "Y")
	{
		return true;
	}
	else
	{
		string winner = WhoWon();
		
		cout << winner << endl;
		cout << "Thanks for playing!" << endl;
		
		return false;
	}
}

string Tournament::WhoWon()
{
	int humanScore = m_round.GetHumanScore();
	int computerScore = m_round.GetComputerScore();

	string winner;

	if (humanScore > computerScore)
	{
		winner = "You have won the tournament with a score of " + to_string(humanScore) + " to " + to_string(computerScore) + ".";
	}
	else if (computerScore > humanScore)
	{
		winner = "The computer has won the tournament with a score of " + to_string(computerScore) + " to " + to_string(humanScore) + ".";
	}
	else
	{
		winner = "The game has ended in a draw! Both players have the same amound of points";
	}

	return winner;
}

