#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"

using namespace std;

class Round
{
public:
	//Constants
	const int NUM_PLAYERS = 2;

	//Default Constructor
	Round();

	//Copy Constructor
	Round(Round& a_otherRound);

	//Destructor
	~Round();

	//Selectors
	int GetHumanScore() const { return m_playerList[0]->GetScore(); }
	int GetComputerScore() const { return m_playerList[1]->GetScore(); }
	char GetHumanColor() const { return m_playerList[0]->GetColor(); }
	char GetComputerColor() const { return m_playerList[1]->GetColor(); }
	int GetHumanCapturedPairs() const { return m_playerList[0]->GetCapturedPairs(); }
	int GetComputerCapturedPairs() const { return m_playerList[1]->GetCapturedPairs(); }

	//Mutators
	bool SetNextPlayerIndex(int a_index);
	bool SetHumanScore(int a_score);
	bool SetComputerScore(int a_score);
	bool SetHumanColor(char a_color);
	bool SetComputerColor(char a_color);
	bool SetHumanCapturedPairs(int a_capturedPairs);
	bool SetComputerCapturedPairs(int a_capturedPairs);

	//Utility Functions
	void StartRound();
	void DetermineFirstPlayer();
	bool CoinToss();
	void DisplayGame();
	bool RoundOver();
	void SaveGame();
	bool LoadGameData();
	void UpdateScores();
	void ResetRound();
	void DisplayRoundScore();

private:
	//Holds a list of the players currently playing the game. In this case, there will be one human player and one computer player.
	//m_playerList[0] will be the human player.
	//m_playerList[1] will be the computer player.
	vector<Player*> m_playerList;

	//The board for the round.
	Board m_board;

	//The current player whos turn it is. Will be either 'H' for human or 'C' for computer.
	int m_nextPlayerIndex;

	//UserInput object used to obtain input from the human player.
	UserInput m_userInput;

	//Fstream file object used for saving and loading games.
	fstream m_file;
};

