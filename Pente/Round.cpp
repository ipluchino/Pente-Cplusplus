#include "Round.h"

//Default Constructor. m_nextPlayerIndex is initially set to '-1' to represent undefined.
Round::Round() : m_nextPlayerIndex(-1)
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
	//Before the round starts, the first player and respective colors must be determined.
	//NOTE IF YOU LOAD THE GAME YOU SHOULD NOT CALL THIS. MUST CHECK IF BOARD IS EMPTY BEFORE AND M_TURN HASNT BEEN DECIDED!!!
	cout << "\nRound starting! Since the round is just starting, the player who goes first must be determined." << endl;
	DetermineFirstPlayer();

	//Display the board for the first time if the human is going first?
	DisplayGame();

	while (!RoundOver())
	{
		m_playerList[m_nextPlayerIndex]->MakePlay(m_board);
		m_nextPlayerIndex = (m_nextPlayerIndex + 1) % NUM_PLAYERS;

		//Display the game after each player's turn.
		DisplayGame();

		//Ask the user to save and exit after each player's turn?
		string saveDecision = m_UserInput.GetSaveDecision();

		if (saveDecision == "Y")
		{
			SaveGame();
		}
	}

	//Once the round ends, update the scores for each player.
	m_playerList[0]->SetScore(m_board.ScoreBoard(m_playerList[0]->GetColor(), m_playerList[0]->GetCapturedPairs()));
	m_playerList[1]->SetScore(m_board.ScoreBoard(m_playerList[1]->GetColor(), m_playerList[1]->GetCapturedPairs()));

	//Clear the board and reset the number of captured pairs for each player in case the user wishes to play another.
	m_board.ClearBoard();
	m_playerList[0]->SetCapturedPairs(0);
	m_playerList[1]->SetCapturedPairs(0);
}

//Determines the first player of the round, and sets the colors of the players.
void Round::DetermineFirstPlayer()
{
	//The player who has the higher score gets to play first for the round.
	//If the scores or tied, or a new tournament tournament is started, the first player is determined via coin toss.

	if (m_playerList[0]->GetScore() > m_playerList[1]->GetScore())
	{
		m_playerList[0]->SetColor('W');
		m_playerList[1]->SetColor('B');
		m_nextPlayerIndex = 0;

		cout << "You will be going first since you have a higher score." << endl << endl;
	}
	else if (m_playerList[1]->GetScore() > m_playerList[0]->GetScore())
	{
		m_playerList[1]->SetColor('W');
		m_playerList[0]->SetColor('B');
		m_nextPlayerIndex = 1;

		cout << "The computer will be going first because the computer has a higher score." << endl << endl;
	}
	else
	{
		bool correctCall = CoinToss();

		if (correctCall)
		{
			m_playerList[0]->SetColor('W');
			m_playerList[1]->SetColor('B');
			m_nextPlayerIndex = 0;

			cout << " You will be going first because you called the coin toss correctly." << endl << endl;
		}
		else
		{
			m_playerList[1]->SetColor('W');
			m_playerList[0]->SetColor('B');
			m_nextPlayerIndex = 1;

			cout << " The computer will be going first because you called the coin toss incorrectly." << endl << endl;
		}
	}
}

//Runs a coin toss to determine the first player. The human player is asked to call the toss.
bool Round::CoinToss()
{
	string choice = m_UserInput.GetCoinTossCall();
	
	//Randomly generate either 1 or 2. 1 Represents heads, while 2 represents tails.
	srand(time(NULL));
	int coin = 1 + (rand() % 2);

	//Output the coin toss result to the screen so the user can see if it was heads or tails.
	if (coin == 1)
	{
		cout << "The result of the coin toss was Heads!";
	}
	else
	{
		cout << "The result of the coin toss was Tails!";
	}

	//If the user correctly called the toss, return true, otherwise return false.
	if ((choice == "H" && coin == 1) || (choice == "T" && coin == 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Displays the Information on the current round, including the board, player scores, player captures, and player colors.
void Round::DisplayGame()
{
	//Display the board first.
	m_board.DisplayBoard();

	//Dislpay the Human's information.
	cout << "Human:" << endl;
	cout << "Captured Pairs: " << m_playerList[0]->GetCapturedPairs() << endl;
	cout << "Tournament Score: " << m_playerList[0]->GetScore() << endl << endl;

	//Display the Computer's information.
	cout << "Computer:" << endl;
	cout << "Captured Pairs: " << m_playerList[1]->GetCapturedPairs() << endl;
	cout << "Tournament Score: " << m_playerList[1]->GetScore() << endl << endl;
}

//Determines if the round is over.
bool Round::RoundOver()
{
	//If one of the players has achieved five consecutive pieces in any direction, the round is over.
	if (m_board.FiveConsecutive())
	{
		cout << "The round has ended because a player has placed five consecutive stones." << endl << endl;
		return true;
	}

	//If one of the players has achieved at least 5 captured pairs, the round is over.
	if (m_playerList[0]->GetCapturedPairs() >= 5 || m_playerList[1]->GetCapturedPairs() >= 5)
	{
		cout << "The round has ended because a player has at least 5 captured pairs." << endl << endl;
		return true;
	}

	//If none of the above situations occured but the board is full, the round is over.
	if (m_board.IsBoardFull()) 
	{
		cout << "The round has ended because the board is full." << endl << endl;
		return true;
	}
	
	//Otherwise, the round can continue.
	return false;
}

//Saves the game to a file, and closes the program.
void Round::SaveGame()
{
	string fileName;
	fstream file;

	cout << "Enter the name of the file you want the game saved to (without the .txt): ";
	cin >> fileName;
	fileName += ".txt";

	file.open(fileName, std::ios::out);

	//Write the board to the file.
	vector<vector<char>> board = m_board.GetBoard();
	
	file << "Board:\n";
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board.size(); j++)
		{
			if (board[i][j] == '-')
			{
				file << 'O';
			}
			else
			{
				file << board[i][j];
			}
		}

		file << "\n";
	}
	
	//Write the human's game information to the file.
	file << "\nHuman:\n";
	file << "Captured Pairs: " << m_playerList[0]->GetCapturedPairs() << "\n";
	file << "Score: " << m_playerList[0]->GetScore() << "\n\n";

	//Write the computer's game information to the file.
	file << "Computer:\n";
	file << "Captured Pairs: " << m_playerList[1]->GetCapturedPairs() << "\n";
	file << "Score: " << m_playerList[1]->GetScore() << "\n\n";

	//Write the next player's turn to the file.
	file << "Next Player: ";
	if (m_nextPlayerIndex == 0)
	{
		file << "Human - " << m_playerList[0]->GetColor();
	}
	else
	{
		file << "Computer - " << m_playerList[1]->GetColor();
	}

	file.close();

	cout << "Game successfully saved, thanks for playing!" << endl;

	//Exit the program, no need to ask anything else of the user.
	exit(0);
}
