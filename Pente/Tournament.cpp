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

//Main game 
void Tournament::StartTournament()
{
	CreateNewGame();
	cout << "Starting Tournament!" << endl;

	do 
	{
		m_round.StartRound();

		//SCORE ROUND WHEN IT ENDS

		break;
	} while (true);		// SHOULD BE while(Continue())


}
