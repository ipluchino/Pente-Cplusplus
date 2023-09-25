/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Round class - implementation file.
* Date : 9/27/23
************************************************************/

#include "Round.h"

/* *********************************************************************
Function Name: Round - Default constructor
Purpose: To construct a Round object.
Parameters: None
Return Value: None
Algorithm:
			1) Construct a Human object and Computer object, and add them to the Round's player list.
			2) Generate a random seed for anything that requires the generation of random numbers.
Assistance Received: None
********************************************************************* */
Round::Round() : m_nextPlayerIndex(-1)
{
	m_playerList.push_back(new Human());
	m_playerList.push_back(new Computer());

	srand(time(NULL));
}

/* *********************************************************************
Function Name: Round - Copy constructor
Purpose: To construct a Round object from an existing Round object.
Parameters: None
Return Value: None
Algorithm:
			1) Construct a Human object and Computer object, and add them to the Round's player list.
			2) Copy the other Round's Board object into the new Round's board object.
			3) Copy the other Round's human information into the new Round's human information.
			4) Copy the other Round's computer information in the new Round's computer information.
Assistance Received: None
********************************************************************* */
Round::Round(Round& a_otherRound) : m_nextPlayerIndex(a_otherRound.m_nextPlayerIndex)
{
	//Create the Human and Computer objects.
	m_playerList.push_back(new Human());
	m_playerList.push_back(new Computer());
	
	//Copy the board.
	m_board = a_otherRound.m_board;

	//Copy the Human information.
	SetHumanColor(a_otherRound.GetHumanColor());
	SetHumanScore(a_otherRound.GetHumanScore());
	SetHumanCapturedPairs(a_otherRound.GetHumanCapturedPairs());

	//Copy the Computer information.
	SetComputerColor(a_otherRound.GetComputerColor());
	SetComputerScore(a_otherRound.GetComputerScore());
	SetComputerCapturedPairs(a_otherRound.GetComputerCapturedPairs());
}

/* *********************************************************************
Function Name: ~Round - Destructor
Purpose: To destruct a Round object.
Parameters: None
Return Value: None
Algorithm:
			1) Delete the memory allocated for the Human and Computer objects.
			2) Ensure the Round's file object is closed.
Assistance Received: None
********************************************************************* */
Round::~Round()
{
	for (int i = 0; i < m_playerList.size(); i++)
	{
		delete m_playerList[i];
	}

	//Make sure the file is closed.
	m_file.close();
}

/* *********************************************************************
Function Name: SetNextPlayerIndex
Purpose: To set the Round's next player index.
Parameters:
			a_index, an integer representing the next player index to be set.
Return Value: Whether or not the next player index was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetNextPlayerIndex(int a_index)
{
	if (a_index != -1 && a_index != 0 && a_index != 1) return false;

	m_nextPlayerIndex = a_index;

	return true;
}

/* *********************************************************************
Function Name: SetHumanScore
Purpose: To set the Round's human's score.
Parameters:
			a_score, an integer representing the human's score to be set.
Return Value: Whether or not the human's score was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetHumanScore(int a_score)
{
	if (!m_playerList[0]->SetScore(a_score))
	{
		return false;
	}
	
	return true;
}

/* *********************************************************************
Function Name: SetComputerScore
Purpose: To set the Round's computer's score.
Parameters:
			a_score, an integer representing the computer's score to be set.
Return Value: Whether or not the computers's score was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetComputerScore(int a_score)
{
	if (!m_playerList[1]->SetScore(a_score))
	{
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: SetHumanColor
Purpose: To set the Round's human's board piece color.
Parameters:
			a_color, a character representing the human's board piece color to be set.
Return Value: Whether or not the human's color was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetHumanColor(char a_color)
{
	if (!m_playerList[0]->SetColor(a_color))
	{
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: SetComputerColor
Purpose: To set the Round's computer's board piece color.
Parameters:
			a_color, a character representing the computer's board piece color to be set.
Return Value: Whether or not the computer's score was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetComputerColor(char a_color)
{
	if (!m_playerList[1]->SetColor(a_color))
	{
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: SetHumanCapturedPairs
Purpose: To set the Round's human's captured pair count.
Parameters:
			a_capturedPairs, an integer representing the human's captured pair count to be set.
Return Value: Whether or not the human's captured pair count was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetHumanCapturedPairs(int a_capturedPairs)
{
	if (!m_playerList[0]->SetCapturedPairs(a_capturedPairs))
	{
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: SetComputerCapturedPairs
Purpose: To set the Round's computer's captured pair count.
Parameters:
			a_capturedPairs, an integer representing the computer's captured pair count to be set.
Return Value: Whether or not the computer's captured pair count was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Round::SetComputerCapturedPairs(int a_capturedPairs)
{
	if (!m_playerList[1]->SetCapturedPairs(a_capturedPairs))
	{
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: StartRound
Purpose: To start and run through one round of Pente.
Parameters: None
Return Value: None
Algorithm:
			1) Determine who will be playing first, and who will be playing second.
			2) Display the initial board and round information.
			3) While the round has not ended, the human and computer players alternate turns.
			4) One the round ends, display the score earned by the human and computer for the round.
			5) Update the tournament score of each player based on the scores earned for the current round.
			6) Reset the round so that it is ready in case the user wishes to play another round.
Assistance Received: None
********************************************************************* */
void Round::StartRound()
{
	//If the first player has not yet already been determined, decide who goes first.
	if (m_nextPlayerIndex == -1)
	{
		cout << "\nSince the round is just starting, the player who goes first must be determined." << endl;
		DetermineFirstPlayer();
	}

	//Display the round information for the first time.
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

/* *********************************************************************
Function Name: DetermineFirstPlayer
Purpose: To determine the first player of the round, and sets the board piece colors of the players.
Parameters: None
Return Value: None
Algorithm:
			1) Determine which player will be going first, and which player will be going second.
				1a) If the human has a higher score, the human plays first.
				1b) If the computer has a higher score, the computer plays first.
				1c) If the scores are tied, the first player is decided by coin toss.
			2) Set the colors of both players.
				2a) The player going first will be playing with white stones.
				2b) The player going second will be playing with black stones.
			3) Display who is going first and why to explain it to the user.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name: CoinToss
Purpose: To toss a coin toss to determine the first player. 
Parameters: None
Return Value: Whether or not the human called the coin toss correctly, a boolean value.
Algorithm:
			1) Ask the user to call the toss.
			2) Generate a random number, either 1 (Heads) or 2 (Tails).
			3) Display the result of the coin toss.
			4) Determine if the player called the toss correctly and return the result.
Assistance Received: https://cplusplus.com/reference/cstdlib/rand/
********************************************************************* */
bool Round::CoinToss()
{
	string choice = m_userInput.GetCoinTossCall();
	
	//Randomly generate either 1 or 2. 1 Represents heads, while 2 represents tails.
	int coin = 1 + (rand() % 2);

	//Output the coin toss result to the screen so the user can see if it was heads or tails.
	if (coin == HEADS)
	{
		cout << "The result of the coin toss was Heads!";
	}
	else
	{
		cout << "The result of the coin toss was Tails!";
	}

	//If the user correctly called the toss, return true, otherwise return false.
	if ((choice == "H" && coin == HEADS) || (choice == "T" && coin == TAILS))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* *********************************************************************
Function Name: DisplayGame
Purpose: To display all information regarding the current round.
Parameters: None
Return Value: None
Algorithm:
			1) Display the board.
			2) Display the human's information.
			3) Display the computer's information.
			4) Display who will be playing next.
Assistance Received: None
********************************************************************* */
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

	//Display who will be playing next.
	if (m_nextPlayerIndex == 0)
	{
		cout << "Next Turn: Human - "; 

		if (GetHumanColor() == 'W')
		{
			cout << "White" << endl << endl;
		}
		else
		{
			cout << "Black" << endl << endl;
		}
	}
	else
	{
		cout << "Next Turn: Computer - ";
		
		if (GetComputerColor() == 'W')
		{
			cout << "White" << endl << endl;
		}
		else
		{
			cout << "Black" << endl << endl;
		}
	}
}

/* *********************************************************************
Function Name: RoundOver
Purpose: To determine if the current round is over.
Parameters: None
Return Value: Whether the round has ended or not, a boolean value.
Algorithm:
			1) Determine if a player has achieved five consecutive pieces in any direction.
			2) Determine if a player has at least five captured pairs.
			3) Determine if the board is completely full.
			4) If any of the above are true, output the reason why the round has ended, and return true. Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Round::RoundOver()
{
	//If one of the players has achieved five consecutive pieces in any direction, the round is over.
	if (m_board.FiveConsecutive('W'))
	{
		if (GetHumanColor() == 'W')
		{
			cout << "The round has ended because the Human player has five consecutive stones on the board." << endl << endl;
			return true;
		}
		else
		{
			cout << "The round has ended because the Computer player has five consecutive stones on the board." << endl << endl;
			return true;
		}
	}
	else if (m_board.FiveConsecutive('B'))
	{
		if (GetHumanColor() == 'B')
		{
			cout << "The round has ended because the Human player has five consecutive stones on the board." << endl << endl;
			return true;
		}
		else
		{
			cout << "The round has ended because the Computer player has five consecutive stones on the board." << endl << endl;
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

/* *********************************************************************
Function Name: SaveGame
Purpose: To save the game to a file.
Parameters: None
Return Value: None
Algorithm:
			1) Obtain the file name the user wishes to save the game to.
			2) Validate that the file was successfully created.
			3) Write the board's information to the file.
			4) Write the human's information to the file.
			5) Write the computer's information to the file.
			6) Write who's turn is next to the file.
			7) Close the file, and terminate the program.
Assistance Received: https://cplusplus.com/reference/fstream/fstream/
********************************************************************* */
void Round::SaveGame()
{
	string fileName = m_userInput.GetFileNameSave();

	m_file.open(fileName, ios::out);

	//Validate that the file was successfully created.
	while (!m_file.is_open())
	{
		cout << "Invalid file name, please enter a valid file name to save the game to." << endl;
		fileName = m_userInput.GetFileNameSave();
		m_file.open(fileName, ios::out);
	}

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
		m_file << "Human - "; 
		if (GetHumanColor() == 'W')
		{
			m_file << "White";
		}
		else
		{
			m_file << "Black";
		}
		
	}
	else
	{
		m_file << "Computer - ";
		if (GetComputerColor() == 'W')
		{
			m_file << "White";
		}
		else
		{
			m_file << "Black";
		}
	}

	m_file.close();

	cout << "Game successfully saved, thanks for playing!" << endl;

	//Exit the program, no need to ask anything else of the user.
	exit(0);
}

/* *********************************************************************
Function Name: LoadGameData
Purpose: To load game data from a file into the current round.
Parameters: None
Return Value: Whether or not the game was successfully loaded from a file.
Algorithm:
			1) Ask the user the name of the file to be loaded in from.
				1a) If the file cannot be located, return false.
			2) Read in the board from the file.
			3) Read in the human's information from the file.
			4) Read in the computer's information from the file.
			5) Read in who is playing next from the file.
			6) Set all the information read in into the Round's member variables.
Assistance Received: https://cplusplus.com/reference/fstream/fstream/
********************************************************************* */
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

				//Determine the colors of the players.
				if (line.find("White") != string::npos)
				{
					humanColor = 'W';
					computerColor = 'B';
				}
				else
				{
					humanColor = 'B';
					computerColor = 'W';
				}
			}
			else
			{
				//Computer plays next
				nextPlayerIndex = 1;

				//Determine the colors of the players.
				if (line.find("White") != string::npos)
				{
					computerColor = 'W';
					humanColor = 'B';
				}
				else
				{
					computerColor = 'B';
					humanColor = 'W';
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

/* *********************************************************************
Function Name: UpdateScores
Purpose: To update the scores after a round concludes.
Parameters: None
Return Value: None
Algorithm:
			1) Update the human's score by adding their score earned from the round to their running total.
			2) Update the computer's score by adding their score earned from the round to their running total.
Assistance Received: None
********************************************************************* */
void Round::UpdateScores()
{
	SetHumanScore(GetHumanScore() + m_board.ScoreBoard(GetHumanColor(), GetHumanCapturedPairs()));
	SetComputerScore(GetComputerScore() + m_board.ScoreBoard(GetComputerColor(), GetComputerCapturedPairs()));
}

/* *********************************************************************
Function Name: ResetRound
Purpose: To reset the round so another can be played.
Parameters: None
Return Value: None
Algorithm:
			1) Clear the board.
			2) Reset the captured pair counts of each player to zero.
			3) Reset the next player index so it can be determined again at the start of a new round.
Assistance Received: None
********************************************************************* */
void Round::ResetRound()
{
	m_board.ClearBoard();
	SetHumanCapturedPairs(0);
	SetComputerCapturedPairs(0);
	SetNextPlayerIndex(-1);
}

/* *********************************************************************
Function Name: DisplayRoundScore
Purpose: To display the number of points earned by each player at the end of the current round.
Parameters: None
Return Value: None
Algorithm:
			1) Tally the human's score for the round.
			2) Tally the computer's score for the round.
			3) Display both player's scores.
Assistance Received: None
********************************************************************* */
void Round::DisplayRoundScore()
{
	int humanRoundScore = m_board.ScoreBoard(GetHumanColor(), GetHumanCapturedPairs());
	int computerRoundScore = m_board.ScoreBoard(GetComputerColor(), GetComputerCapturedPairs());
	
	cout << "Points scored by the Human this round: " << humanRoundScore << endl;
	cout << "Points scored by the Computer this round: " << computerRoundScore << endl << endl;
}
