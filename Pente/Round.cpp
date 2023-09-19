#include "Round.h"

//Default Constructor. m_nextPlayerIndex is initially set to '-1' to represent undefined.
Round::Round() : m_nextPlayerIndex(-1)
{
	m_playerList.push_back(new Human());
	m_playerList.push_back(new Computer());

	srand(time(NULL));
}

//Destructor
Round::~Round()
{
	for (int i = 0; i < m_playerList.size(); i++)
	{
		delete m_playerList[i];
	}

	//Make sure the file is closed.
	m_file.close();
}

bool Round::SetNextPlayerIndex(int a_index)
{
	if (a_index != 0 && a_index != 1) return false;

	m_nextPlayerIndex = a_index;

	return true;
}

bool Round::SetHumanScore(int a_score)
{
	if (!m_playerList[0]->SetScore(a_score))
	{
		return false;
	}
	
	return true;
}

bool Round::SetComputerScore(int a_score)
{
	if (!m_playerList[1]->SetScore(a_score))
	{
		return false;
	}

	return true;
}

bool Round::SetHumanColor(char a_color)
{
	if (!m_playerList[0]->SetColor(a_color))
	{
		return false;
	}

	return true;
}

bool Round::SetComputerColor(char a_color)
{
	if (!m_playerList[1]->SetColor(a_color))
	{
		return false;
	}

	return true;
}

bool Round::SetHumanCapturedPairs(int a_capturedPairs)
{
	if (!m_playerList[0]->SetCapturedPairs(a_capturedPairs))
	{
		return false;
	}

	return true;
}

bool Round::SetComputerCapturedPairs(int a_capturedPairs)
{
	if (!m_playerList[1]->SetCapturedPairs(a_capturedPairs))
	{
		return false;
	}

	return true;
}

//Runs through one round of Pente.
void Round::StartRound()
{
	//If the first player has not yet already been determined, decide who goes first.
	if (m_nextPlayerIndex == -1)
	{
		cout << "\nSince the round is just starting, the player who goes first must be determined." << endl;
		DetermineFirstPlayer();
	}

	//Display the board for the first time.
	DisplayGame();

	//Main round loop. Alternate turns between the human and the computer.
	while (!RoundOver())
	{
		bool playMade = m_playerList[m_nextPlayerIndex]->MakePlay(m_board);

		//If no play was made, the user wants to save and exit the game. The program is terminated after SaveGame() is called.
		if (playMade == false)
		{
			SaveGame();
		}

		//Make it the next player's turn after they have made a play.
		m_nextPlayerIndex = (m_nextPlayerIndex + 1) % NUM_PLAYERS;

		//Display the game information after each player's turn.
		DisplayGame();
	}

	//Display the scores earned for this current round.
	DisplayRoundScore();

	//Once the round ends, update the scores for each player.
	UpdateScores();

	//Reset the round so that the user can play again if they choose to continue playing.
	ResetRound();
}

//Determines the first player of the round, and sets the colors of the players.
void Round::DetermineFirstPlayer()
{
	//The player who has the higher score gets to play first for the round.
	//If the scores or tied, or a new tournament tournament is started, the first player is determined via coin toss.

	if (GetHumanScore() > GetComputerScore())
	{
		SetHumanColor('W');
		SetComputerColor('B');
		SetNextPlayerIndex(0);

		cout << "You will be going first since you have a higher score." << endl << endl;
	}
	else if (GetComputerScore() > GetHumanScore())
	{
		SetComputerColor('W');
		SetHumanColor('B');
		SetNextPlayerIndex(1);

		cout << "The computer will be going first because the computer has a higher score." << endl << endl;
	}
	else
	{
		bool correctCall = CoinToss();

		if (correctCall)
		{
			SetHumanColor('W');
			SetComputerColor('B');
			SetNextPlayerIndex(0);

			cout << " You will be going first because you called the coin toss correctly." << endl << endl;
		}
		else
		{
			SetComputerColor('W');
			SetHumanColor('B');
			SetNextPlayerIndex(1);

			cout << " The computer will be going first because you called the coin toss incorrectly." << endl << endl;
		}
	}
}

//Runs a coin toss to determine the first player. The human player is asked to call the toss.
bool Round::CoinToss()
{
	string choice = m_userInput.GetCoinTossCall();
	
	//Randomly generate either 1 or 2. 1 Represents heads, while 2 represents tails.
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
	cout << "Human - " << GetHumanColor() << ":" << endl;
	cout << "Captured Pairs: " << GetHumanCapturedPairs() << endl;
	cout << "Tournament Score: " << GetHumanScore() << endl << endl;

	//Display the Computer's information.
	cout << "Computer - " << GetComputerColor() << ":" << endl;
	cout << "Captured Pairs: " << GetComputerCapturedPairs() << endl;
	cout << "Tournament Score: " << GetComputerScore() << endl << endl;

	//Display who's turn it currently is.
	if (m_nextPlayerIndex == 0)
	{
		cout << "Next Turn: Human" << endl << endl;
	}
	else
	{
		cout << "Next Turn: Computer" << endl << endl;
	}
}

//Determines if the round is over.
bool Round::RoundOver()
{
	//If one of the players has achieved five consecutive pieces in any direction, the round is over.
	if (m_board.FiveConsecutive('W'))
	{
		if (GetHumanColor() == 'W')
		{
			cout << "The round has ended because the Human player has five consecutive pieces on the board." << endl << endl;
			return true;
		}
		else
		{
			cout << "The round has ended because the Computer player has five consecutive pieces on the board." << endl << endl;
			return true;
		}
	}
	else if (m_board.FiveConsecutive('B'))
	{
		if (GetHumanColor() == 'B')
		{
			cout << "The round has ended because the Human player has five consecutive pieces on the board." << endl << endl;
			return true;
		}
		else
		{
			cout << "The round has ended because the Computer player has five consecutive pieces on the board." << endl << endl;
			return true;
		}
	}
	//If one of the players has achieved at least 5 captured pairs, the round is over.
	else if (GetHumanCapturedPairs() >= 5)
	{
		cout << "The round has ended because the Human player has at least 5 captured pairs." << endl << endl;
		return true;
	}
	else if (GetComputerCapturedPairs() >= 5)
	{
		cout << "The round has ended because the Computer player has at least 5 captured pairs." << endl << endl;
		return true;
	}
	//If none of the above situations occured but the board is full, the round is over.
	else if (m_board.IsBoardFull()) 
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
	string fileName = m_userInput.GetFileNameSave();

	m_file.open(fileName, ios::out);

	//Write the board to the file.
	vector<vector<char>> board = m_board.GetBoard();
	
	m_file << "Board:\n";
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board.size(); col++)
		{
			if (board[row][col] == '-')
			{
				m_file << 'O';
			}
			else
			{
				m_file << board[row][col];
			}
		}

		m_file << "\n";
	}
	
	//Write the human's game information to the file.
	m_file << "\nHuman:\n";
	m_file << "Captured Pairs: " << GetHumanCapturedPairs() << "\n";
	m_file << "Score: " << GetHumanScore() << "\n\n";

	//Write the computer's game information to the file.
	m_file << "Computer:\n";
	m_file << "Captured Pairs: " << GetComputerCapturedPairs() << "\n";
	m_file << "Score: " << GetComputerScore() << "\n\n";

	//Write the next player's turn to the file.
	m_file << "Next Player: ";
	if (m_nextPlayerIndex == 0)
	{
		m_file << "Human - " << GetHumanColor();
	}
	else
	{
		m_file << "Computer - " << GetComputerColor();
	}

	m_file.close();

	cout << "Game successfully saved, thanks for playing!" << endl;

	//Exit the program, no need to ask anything else of the user.
	exit(0);
}

//Loads game data from a file into the current round.
bool Round::LoadGameData()
{
	string fileName = m_userInput.GetFileNameLoad();
	
	m_file.open(fileName, ios::in);

	if (!m_file.is_open()) {
		cout << "Error! Couldn't locate the file provided!" << endl << endl;
		return false;
	}

	vector<vector<char>> board = {};

	int humanCaptured = 0, computerCaptured = 0, humanScore = 0, computerScore = 0, nextPlayerIndex = 0, pos = 0;
	char humanColor = ' ', computerColor = ' ';

	string line;
	while (getline(m_file, line))
	{
		//First read in the board.
		if (line.find("Board:") != string::npos)
		{
			for (int i = 0; i < 19; i++)
			{
				getline(m_file, line);

				vector<char> row = {};

				//Loop through the entire line except the end, to ignore the \n character.
				for (int j = 0; j < line.length(); j++)
				{
					if (line[j] == 'O')
					{
						row.push_back('-');
					}
					else
					{
						row.push_back(line[j]);
					}

				}

				board.push_back(row);
			}
		}

		//Next read in the human information
		if (line.find("Human:") != string::npos)
		{
			getline(m_file, line);

			//Obtaining the number of captures for the human player.
			pos = line.find(":") + 1;
			humanCaptured = stoi(line.substr(pos));

			//Obtaining the score for the human player.
			getline(m_file, line);
			pos = line.find(":") + 1;
			humanScore = stoi(line.substr(pos));
		}

		//Next read in the computer information
		if (line.find("Computer:") != string::npos)
		{
			getline(m_file, line);

			//Obtaining the number of captures for the human player.
			pos = line.find(":") + 1;
			computerCaptured = stoi(line.substr(pos));

			//Obtaining the score for the human player.
			getline(m_file, line);
			pos = line.find(":") + 1;
			computerScore = stoi(line.substr(pos));
		}

		//Last, read in the next player information.
		if (line.find("Next Player:") != string::npos)
		{
			if (line.find("Human") != string::npos)
			{
				//Human plays next
				nextPlayerIndex = 0;

				char nextPlayerColor = line[line.size() - 1];

				if (nextPlayerColor == 'B')
				{
					humanColor = 'B';
					computerColor = 'W';
				}
				else
				{
					humanColor = 'W';
					computerColor = 'B';
				}

			}
			else
			{
				//Computer plays next
				nextPlayerIndex = 1;

				char nextPlayerColor = line[line.size() - 1];

				if (nextPlayerColor == 'B')
				{
					computerColor = 'B';
					humanColor = 'W';
				}
				else {
					computerColor = 'W';
					humanColor = 'B';
				}
			}
		}
	}

	//Set the round's data to the variables read in.
	if (!m_board.SetBoard(board))
	{
		cout << "Could not correctly load board from the file!" << endl << endl; 
		return false;
	}

	if (!SetHumanCapturedPairs(humanCaptured) || !SetHumanScore(humanScore) || !SetHumanColor(humanColor))
	{
		cout << "Could not correctly load the human's information from the file!" << endl << endl;
		return false;
	}

	if (!SetComputerCapturedPairs(computerCaptured) || !SetComputerScore(computerScore) || !SetComputerColor(computerColor))
	{
		cout << "Could not correctly load the computer's information from the file!" << endl << endl;
		return false;
	}

	if (!SetNextPlayerIndex(nextPlayerIndex))
	{
		cout << "Could not correctly load the next player from the file!" << endl << endl;
		return false;
	}

	m_file.close();

	return true;
}

//Updates the scores after a round concludes.
void Round::UpdateScores()
{
	m_playerList[0]->SetScore(GetHumanScore() + m_board.ScoreBoard(GetHumanColor(), GetHumanCapturedPairs()));
	m_playerList[1]->SetScore(GetComputerScore() + m_board.ScoreBoard(GetComputerColor(), GetComputerCapturedPairs()));
}

//Resets the round so another can be played.
void Round::ResetRound()
{
	m_board.ClearBoard();
	m_playerList[0]->SetCapturedPairs(0);
	m_playerList[1]->SetCapturedPairs(0);
	m_nextPlayerIndex = -1;
}

void Round::DisplayRoundScore()
{
	int humanRoundScore = m_board.ScoreBoard(GetHumanColor(), GetHumanCapturedPairs());
	int computerRoundScore = m_board.ScoreBoard(GetComputerColor(), GetComputerCapturedPairs());
	
	cout << "Points scored by the Human this round: " << humanRoundScore << endl;
	cout << "Points scored by the Computer this round: " << computerRoundScore << endl << endl;
}
