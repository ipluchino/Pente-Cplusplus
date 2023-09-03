#include "Human.h"

//Default Constructor
Human::Human(): Player()
{

}

/*
//Parametric Constructor to start a new game
Human::Human(char a_humanColor): Player()
{
}
*/

void Human::MakePlay(Board& a_board)
{
	//If the board is empty, you can only play on J10 so no human input is required.
	if (a_board.IsEmptyBoard())
	{
		a_board.PlaceStone('J', 10, m_color);
		cout << "You placed your stone on J10 because the player that goes first must place it here." << endl << endl;
		return;
	}
	
	//Obtain the location the human player wants to place the stone.
	string location = m_UserInput.GetPlayLocation(a_board);

	//Place the stone on the board.
	a_board.PlaceStone(location[0], stoi(location.substr(1,2)), m_color);
}
