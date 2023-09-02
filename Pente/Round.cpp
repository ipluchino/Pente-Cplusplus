#include "Round.h"

//Default Constructor.
Round::Round()
{
}

//Parametric Constructor used for starting a new game.
Round::Round(char a_humanColor, char a_computerColor)
{
	m_playerList.push_back(new Human());
	m_playerList.push_back(new Computer());
}

//Destructor 
Round::~Round()
{
	for (int i = 0; i < m_playerList.size(); i++) 
	{
		delete m_playerList[i];
	}
}


