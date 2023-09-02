#include "Human.h"

//Default Constructor
Human::Human()
{

}

//Parametric Constructor to start a new game
Human::Human(char a_humanColor): Player(a_humanColor, 0, 0)
{
}

void Human::MakePlay(Board& a_board)
{
	//Obtain the location the human player wants to place the stone.
	string location = m_UserInput.GetPlayLocation(a_board);

	//Place the stone on the board.
	a_board.PlaceStone(location[0], stoi(location.substr(1,2)), m_color);
}
