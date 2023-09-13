#include "Player.h"

//Default Constructor - If no color is provided, by default the color is set to white.
Player::Player() : m_color('W'), m_score(0), m_capturedPairs(0)
{
}

bool Player::SetColor(char a_color)
{
	if (a_color != 'W' && a_color != 'B') return false;

	m_color = a_color;

	return true;
}

bool Player::SetScore(int a_score)
{
	if (a_score < 0) return false;

	m_score = a_score;
	
	return true;
}

bool Player::SetCapturedPairs(int a_capturedPairs)
{
	if (a_capturedPairs < 0) return false;

	m_capturedPairs = a_capturedPairs;

	return true;
}

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

	//possiblePlay is the potential {row, col} pair returned by the strategy functions.
	vector<int> possiblePlay;

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

		reasoning = "The computer placed a stone on " + location + " because it played randomly within the handicap.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to make the most possible captures, if possible.
	possiblePlay = MakeCapture(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		int row = a_board.ConvertRowIndex(possiblePlay[0]);
		char col = a_board.IntToCharacter(possiblePlay[1]);

		location = col + to_string(row);
		reasoning = "The computer placed a stone on " + location + " to capture the opponent's pieces.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to block the most possible captures, if possible.
	possiblePlay = PreventCapture(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		int row = a_board.ConvertRowIndex(possiblePlay[0]);
		char col = a_board.IntToCharacter(possiblePlay[1]);

		location = col + to_string(row);
		reasoning = "The computer placed a stone on " + location + " to prevent the opponent from making a capture.";
		return pair<string, string>(location, reasoning);
	}

	//Play randomly if none of the above applies. Will be changed in the future.
	do {
		int row = 1 + (rand() % 19);
		char col = 'A' + (rand() % 19);

		location = col + to_string(row);

	} while (!a_board.IsEmptyLocation(location[0], stoi(location.substr(1, 2))));

	reasoning = "The computer placed a stone on " + location + " because it played randomly.";

	return pair<string, string>(location, reasoning);
}

//Returns a vector<int> that contains {row, col} of best possible location to place your piece to make the most captures.
//Returns an empty vector if there are no potential captures to be made.
vector<int> Player::MakeCapture(Board a_board, char a_color)
{
	vector<vector<char>> board = a_board.GetBoard();

	vector<vector<int>> allPossibleCaptures;

	//Search the entire board for empty spaces.
	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			if (board[row][col] == '-')
			{
				//If the space is empty, determine the number of captures that would occur if you were to place your piece here.
				int numCaptures = CanCaptureIfPlaced(a_board, a_color, row, col);
				if (numCaptures > 0)
				{
					//If you can make a capture at this location, log it in the form {row, col, number of captures} 
					vector<int> captureInfo = { row, col, numCaptures };
					allPossibleCaptures.push_back(captureInfo);
				}
			}
		}
	}

	//If there are no possible captures, simply return an empty vector.
	if (allPossibleCaptures.size() == 0)
	{
		return {};
	}

	//If there are multiple possible capture locations, the one that captures the most pieces should be prioritized.
	//To accomplish this, a lambda function is used to sort by capture number for each possible play.
	sort(allPossibleCaptures.begin(), allPossibleCaptures.end(), [](vector<int> a, vector<int> b) {
		return a[2] > b[2];
	});

	//Return the play that captures the most possible pieces in one play. Since the vector is sorted by capture number,
	//the first play is considered the most optimized.
	return { allPossibleCaptures[0][0], allPossibleCaptures[0][1] };
}

//Given a board and location, determines the number of captures that would happen if you place it here.
int Player::CanCaptureIfPlaced(Board a_board, char a_color, int a_row, int a_col)
{
	vector<vector<char>> board = a_board.GetBoard();
	
	char opponentColor = a_board.OpponentColor(a_color);
	int numCaptures = 0;

	//Loop through all 8 of the possible directions starting from 
	for (int direction = 0; direction < StrategyConstants::NUM_DIRECTIONS; direction++)
	{
		vector<vector<int>> newLocations = {};

		//To see if a capture exists, you must go three spaces out in each direction and store them.
		for (int distance = 1; distance <= StrategyConstants::CAPTURE_DISTANCE; distance++)
		{
			int newRow = a_row + (StrategyConstants::DIRECTIONS[direction][0] * distance);
			int newCol = a_col + (StrategyConstants::DIRECTIONS[direction][1] * distance);

			if (a_board.IsValidIndices(newRow, newCol)) newLocations.push_back({ newRow, newCol });
		}

		if (newLocations.size() == StrategyConstants::CAPTURE_DISTANCE)
		{
			//A capture is possible if the three valid locations are in the pattern: * O O P where * represents an empty space,
			//O is the opponent's pieces, and P is the player's piece.
			if (board[newLocations[0][0]][newLocations[0][1]] == opponentColor &&
				board[newLocations[1][0]][newLocations[1][1]] == opponentColor &&
				board[newLocations[2][0]][newLocations[2][1]] == a_color)
			{
				numCaptures++;
			}
		}
	}

	return numCaptures;
}

//Returns a vector<int> in the form {row, col} if a potential block is available.
vector<int> Player::PreventCapture(Board a_board, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);

	//If the opponent has the ability to make a capture, or multiple, on their next turn, it should be blocked.
	vector<int> possiblePreventCapture = MakeCapture(a_board, opponentColor);
	
	return possiblePreventCapture;
}


