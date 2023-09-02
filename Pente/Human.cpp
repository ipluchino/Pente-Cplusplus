#include "Human.h"

Human::Human()
{
}

void Human::MakePlay(Board& a_board)
{

	//TO DO: MOVE I/O TO USER I/O THEN PLACE WHAT IS RETURNED.
	char column;
	int row;
	
	cout << "Please enter a column to place a stone: ";
	cin >> column;

	cout << "Please enter the row to place the stone in: ";
	cin >> row;

	//MUST VALIDATE
	a_board.PlaceStone(column, row, m_color);
}
