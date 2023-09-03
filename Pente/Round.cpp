#include "Round.h"

//Default Constructor. m_turn is initially set to 'U' to represent undefined.
Round::Round(): m_turn('U')
{
	m_playerList.push_back(new Human());
	m_playerList.push_back(new Computer());
}

/*
//Parametric Constructor used for starting a new game.
Round::Round(char a_humanColor, char a_computerColor)
{
	m_playerList.push_back(new Human(a_humanColor));
	m_playerList.push_back(new Computer(a_computerColor));
}

//Copy Assignment
Round& Round::operator=(const Round& a_round)
{
	//Make sure to avoid self assignment.
	if (&a_round != this)
	{
		m_playerList = a_round.m_playerList;
		m_board = a_round.m_board;
		m_turn = a_round.m_turn;
		m_UserInput = a_round.m_UserInput;	//Is this necessary?
	}

	return *this;
}
*/


//Destructor
Round::~Round()
{
	for (int i = 0; i < m_playerList.size(); i++)
	{
		delete m_playerList[i];
	}
}

//Runs through one round of Pente.
void Round::StartRound()
{
	//Before the round starts, the first player and respective colors must be determined.
	//NOTE IF YOU LOAD THE GAME YOU SHOULD NOT CALL THIS. MUST CHECK IF BOARD IS EMPTY BEFORE AND M_TURN HASNT BEEN DECIDED!!!
	cout << "\nRound starting! Since the round is just starting, the player who goes first must be determined." << endl;
	DetermineFirstPlayer();

	//Display the board for the first time if the human is going first?
	m_board.DisplayBoard();

	bool continueRound = true;
	//Round robin turns until the game ends
	do 
	{
		if (m_turn == 'H')
		{
			//Human turn
			m_playerList[0]->MakePlay(m_board);
			m_turn = 'C';

			//Ask the user to save and exit?
		}
		else
		{
			//Computer turn
			m_playerList[1]->MakePlay(m_board);

			m_turn = 'H';
			//continueRound = false;

			//Ask the user to save and exit?
		}

		m_board.DisplayBoard();

	} while (continueRound); //Should be while(!RoundOver())

}

//Determines the first player of the round, and sets the colors of the players.
void Round::DetermineFirstPlayer()
{
	//The player who has the higher score gets to play first for the round.
	//If the scores or tied, or a new tournament tournament is started, the first player is determined via coin toss.

	if (m_playerList[0]->GetScore() > m_playerList[1]->GetScore())
	{
		m_playerList[0]->SetColor('W');
		m_playerList[1]->SetColor('B');
		m_turn = 'H';

		cout << "You will be going first since you have a higher score." << endl;
	}
	else if (m_playerList[1]->GetScore() > m_playerList[0]->GetScore())
	{
		m_playerList[1]->SetColor('W');
		m_playerList[0]->SetColor('B');
		m_turn = 'C';

		cout << "The computer will be going first because the computer has a higher score." << endl;
	}
	else
	{
		bool correctCall = CoinToss();

		if (correctCall)
		{
			m_playerList[0]->SetColor('W');
			m_playerList[1]->SetColor('B');
			m_turn = 'H';

			cout << " You will be going first because you called the coin toss correctly." << endl << endl;
		}
		else
		{
			m_playerList[1]->SetColor('W');
			m_playerList[0]->SetColor('B');
			m_turn = 'C';

			cout << " The computer will be going first because you called the coin toss incorrectly." << endl << endl;
		}
	}
}

//Runs a coin toss to determine the first player. The human player is asked to call the toss.
bool Round::CoinToss()
{
	string choice = m_UserInput.GetCoinTossCall();
	
	//Randomly generate either 1 or 2. 1 Represents heads, while 2 represents tails.
	srand((unsigned)time(NULL));
	int coin = 1 + (rand() % 2);

	//Output the coin toss result to the screen so the user can see if it was heads or tails.
	if (coin == 1)
	{
		cout << "The result of the coin toss was Heads!";
	}
	else
	{
		cout << "The result of the coin toss was Tails!";
	}

	//If the user correctly called the toss, return true, otherwise return false.
	if ((choice == "H" && coin == 1) || (choice == "T" && coin == 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
