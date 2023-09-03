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
	cout << "Must implement LoadGame()!" << endl;
	return true;
}

//Main game 
void Tournament::StartTournament()
{
	string choice = m_UserInput.GetTournamentChoice();

	//If the user decides to load from a file, obtain the file name and load the game.
	//Otherwise, start a new game. The default constructors for each class are used in this case.
	if (choice == "2")
	{
		LoadGame();
	}

	do 
	{
		m_round.StartRound();

		//SCORE ROUND WHEN IT ENDS

		break;
	} while (true);		// SHOULD BE while(Continue())


}
