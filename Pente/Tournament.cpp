#include "Tournament.h"

/* *********************************************************************
Function Name: Tournament - Default constructor
Purpose: To construct a tournament object.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Tournament::Tournament()
{
}

/* *********************************************************************
Function Name: LoadGame
Purpose: To load a tournament from a file.
Parameters: None
Return Value: Whether or not the tournament was successfully loaded from the file, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Tournament::LoadGame()
{
	bool successfullyLoaded = m_round.LoadGameData();
	return successfullyLoaded;
}

/* *********************************************************************
Function Name: StartTournament
Purpose: To start a Pente tournament
Parameters: None
Return Value: None
Algorithm:
			1) Ask the user if they would like to start a new tournament or load one from a file.
			2) Run a single round of the new or loaded tournament.
			3) On round completion, ask the user if they would like to continue playing the tournament. If yes, run another round.
			4) Display the winner of the tournament.
Assistance Received: None
********************************************************************* */
void Tournament::StartTournament()
{
	cout << "Welcome to Pente!" << endl;

	//If the user decides to load from a file, obtain the file name and load the game. Otherwise, start a new game.
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

	//Continue running rounds of the tournament until the user wishes to stop.
	do 
	{
		m_round.StartRound();

	} while (Continue());	

	//Display the winner.
	string winner = WhoWon();
	cout << winner << endl;
	cout << "Thanks for playing!" << endl;
}

/* *********************************************************************
Function Name: Continue
Purpose: To determine if the user would like to start another round of the tournament.
Parameters: None
Return Value: Whether or not the user would like to start another round, a boolean value.
Algorithm:
			1) Display the updated tournament scores of both the human and computer player.
			2) Ask the user if they would like to start another round of Pente.
Assistance Received: None
********************************************************************* */
bool Tournament::Continue()
{
	cout << "Human's Updated Tournament Score: " << m_round.GetHumanScore() << endl;
	cout << "Computer's Updated Tournament Score: " << m_round.GetComputerScore() << endl << endl;
	
	string choice = m_userInput.GetContinueDecision();

	if (choice == "Y")
	{
		return true;
	}
	else
	{	
		return false;
	}
}

/* *********************************************************************
Function Name: WhoWon
Purpose: To determine who won the tournament.
Parameters: None
Return Value: The winner of the tournament, a string.
Algorithm:
			1) Obtain the scores of both the human and computer player.
			2) Construct a string explaining the winner, and return it.
Assistance Received: None
********************************************************************* */
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
		winner = "The tournament has ended in a draw! Both players have the same amound of points.";
	}

	return winner;
}

