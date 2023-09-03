#include "Player.h"

//Default Constructor - If no color is provided, by default the color is set to white.
Player::Player() : m_color('W'), m_score(0), m_capturedPairs(0)
{
}

/*
//Parametric Constructor
Player::Player(char a_color, unsigned int a_score, unsigned int a_capturedPairs) : m_color(a_color), m_score(a_score), m_capturedPairs(a_capturedPairs)
{
}
*/

//Virtual function - It has its own definition in both the Human and Computer class.
void Player::MakePlay(Board& a_board)
{
}

//Determines the optimal play and returns its location as well as the reasoning why it is the optimal play.
//Assistance Received: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
pair<string, string> Player::OptimalPlay(Board a_board, char a_color)
{
	//ALL STRATEGY WILL GO HERE, FOR NOW COMPUTER PLAYS RANDOMLY
	srand(time(NULL));
	
	//Location represents the location on the board of the most optimal play, while reasoning represents the explanation why it is the most optimal.
	string location, reasoning;
	
	//If the board is empty, the only play is the center position, J10. 
	if (a_board.IsEmptyBoard())
	{
		location = "J10";
		reasoning = "The computer placed a stone on " + location + " because it is going first and the first play must be on J10.";

		return pair<string, string>(location, reasoning);
	}

	//If it is the second turn of the first player, you can only play within 3 intersections of the center piece (j10).
	if (a_board.CountPieces('W') == 1 && a_board.CountPieces('B') == 1)
	{
		do {
			int row = 7 + (rand() % 7);
			char col = 'G' + (rand() % 7);

			location = col + to_string(row);

		} while (!a_board.IsEmptyLocation(location[0], stoi(location.substr(1, 2))));
	}
	else
	{
		do {
			int row = 1 + (rand() % 19);
			char col = 'A' + (rand() % 19);

			location = col + to_string(row);

		} while (!a_board.IsEmptyLocation(location[0], stoi(location.substr(1, 2))));
	}

	reasoning = "The computer placed a stone on " + location + " because it played randomly.";

	return pair<string, string>(location, reasoning);
}


