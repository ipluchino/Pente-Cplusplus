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
	srand((unsigned)time(NULL));

	string location;
	do {
		int row = 1 +(rand() % 19);
		char col = 'A' + rand() % 19;

		location = col + to_string(row);

	} while (!a_board.IsEmpty(location[0], stoi(location.substr(1, 2))));

	string reasoning = "The computer placed a stone on " + location + " because it played randomly.";

	return pair<string, string>(location, reasoning);
}


