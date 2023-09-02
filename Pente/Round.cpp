#include "Round.h"

//Default Constructor.
Round::Round()
{
}

//Parametric Constructor used for starting a new game.
Round::Round(char a_humanColor, char a_computerColor)
{
	m_playerList.push_back(new Human(a_humanColor));
	m_playerList.push_back(new Computer(a_computerColor));
}

//Copy Constructor
Round::Round(const Round& a_round)
{
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

//Destructor 
Round::~Round()
{
	for (int i = 0; i < m_playerList.size(); i++) 
	{
		delete m_playerList[i];
	}
}


