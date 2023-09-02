#include "Round.h"

//Default Constructor.
Round::Round()
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
	//Determine first turn HERE. for now TEMPORARY COLORS.
	m_playerList[0]->SetColor('W');
	m_playerList[1]->SetColor('B');

	cout << "Round starting!" << endl;
	m_turn = 'H';

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

		}
		else
		{
			//Computer turn
			m_playerList[1]->MakePlay(m_board);

			m_turn = 'H';
			//continueRound = false;
		}

		m_board.DisplayBoard();

	} while (continueRound); //Should be while(!RoundOver())

}
