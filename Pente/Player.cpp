#include "Player.h"

//Default Constructor - If no color is provided, by default the color is set to white.
Player::Player() : m_color('W'), m_score(0), m_capturedPairs(0)
{
}

//Parametric Constructor
Player::Player(char a_color, unsigned int a_score, unsigned int a_capturedPairs) : m_color(a_color), m_score(a_score), m_capturedPairs(a_capturedPairs)
{
}

//Virtual function - It has its own definition in both the Human and Computer class.
void Player::MakePlay(Board& a_board)
{
}


