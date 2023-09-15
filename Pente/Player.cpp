#include "Player.h"

//Default Constructor - If no color is provided, by default the color is set to white.
Player::Player() : m_color('W'), m_score(0), m_capturedPairs(0)
{
	srand(unsigned(time(NULL)));
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
bool Player::MakePlay(Board& a_board)
{
	return true;
}

//Determines the optimal play and returns its location as well as the reasoning why it is the optimal play.
//Assistance Received: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
pair<string, string> Player::OptimalPlay(Board a_board, char a_color)
{
	//Location represents the location on the board of the most optimal play, while reasoning represents the explanation why it is the most optimal.
	string location, reasoning;
	vector<int> possiblePlay;

	//If the board is empty, the only play is the center position, J10. 
	if (a_board.IsEmptyBoard())
	{
		location = "J10";
		reasoning = "The computer placed a stone on " + location + " because the first stone must be placed there.";

		return pair<string, string>(location, reasoning);
	}

	//Attempt to win the game, if possible.
	possiblePlay = MakeWinningMove(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		int row = a_board.ConvertRowIndex(possiblePlay[0]);
		char col = a_board.IntToCharacter(possiblePlay[1]);

		location = col + to_string(row);
		reasoning = "The computer placed a stone on " + location + " to win the round!";
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

	//Attempt to build initiative with 3 pieces already placed.
	possiblePlay = BuildInitiative(a_board, 3, a_color);
	if (possiblePlay.size() != 0)
	{
		int row = a_board.ConvertRowIndex(possiblePlay[0]);
		char col = a_board.IntToCharacter(possiblePlay[1]);

		location = col + to_string(row);
		reasoning = "The computer placed a stone on " + location + " to build initiative and have 4 pieces in an open 5.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build initiative with 2 pieces already placed.
	possiblePlay = BuildInitiative(a_board, 2, a_color);
	if (possiblePlay.size() != 0)
	{
		int row = a_board.ConvertRowIndex(possiblePlay[0]);
		char col = a_board.IntToCharacter(possiblePlay[1]);

		location = col + to_string(row);
		reasoning = "The computer placed a stone on " + location + " to build initiative and have 3 pieces in an open 5.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build initiative with 1 piece already placed.
	possiblePlay = BuildInitiative(a_board, 1, a_color);
	if (possiblePlay.size() != 0)
	{
		int row = a_board.ConvertRowIndex(possiblePlay[0]);
		char col = a_board.IntToCharacter(possiblePlay[1]);

		location = col + to_string(row);
		reasoning = "The computer placed a stone on " + location + " to build initiative and have 2 pieces in an open 5.";
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
	return allPossibleCaptures[0];
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

//Finds all possible set of 5 locations that has numPlaced stones of the provided color placed, and 5-numPlaced empty locations.
//Returns a vector<vector<vector<int>>> in the format {{{1,2}, {1,3}, {1,4}, {1,5}, {1,6}}, ...}
vector<vector<vector<int>>> Player::FindAllMoves(Board a_board, int a_numPlaced, char a_color)
{
	//A copy of the board's data.
	vector<vector<char>> board = a_board.GetBoard();

	//Will hold all possible sets of consecutive 5s that has a_numPlaced pieces of the specified color, and 5-numPlaced empty locations.
	vector<vector<vector<int>>> result;

	//To be apart of a possible winning consecutive 5 in the future, there must be at least 5-a_numPlaced empty spaces.
	int emptyRequired = StrategyConstants::CONSECUTIVE_5_DISTANCE - a_numPlaced;

	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			//Only need to search the horizontals, verticals, main diagonals, and anti-diagonals to cover all possible sets of 5.
			for (int direction = 0; direction < StrategyConstants::NUM_DIRECTIONS; direction += StrategyConstants::DIRECTIONAL_OFFSET)
			{
				int pieceCounter = 0;
				int emptyCounter = 0;

				vector<vector<int>> locations = {};

				for (int distance = 0; distance < StrategyConstants::CONSECUTIVE_5_DISTANCE; distance++)
				{
					int newRow = row + StrategyConstants::DIRECTIONS[direction][0] * distance;
					int newCol = col + StrategyConstants::DIRECTIONS[direction][1] * distance;

					//No need to keep searching the current set of 5 if one of the locations go out of bounds.
					if (!a_board.IsValidIndices(newRow, newCol)) break;

					if (board[newRow][newCol] == a_color)
					{
						pieceCounter++;
					}
					else if (board[newRow][newCol] == '-')
					{
						emptyCounter++;
					}

					locations.push_back({ newRow, newCol });
				}

				if (pieceCounter == a_numPlaced && emptyCounter == emptyRequired)
				{
					result.push_back(locations);
				}
			}
		}
	}

	return result;
}

//Given a set of 5 locations, returns the indices of the empty locations. This will be used later in determining the optimal placements.
vector<int> Player::FindEmptyIndices(Board a_board, vector<vector<int>> a_locations)
{
	vector<vector<char>> board = a_board.GetBoard();
	vector<int> emptyIndices;

	//Search through the set of 5 locations and mark the empty indices.
	for (int i = 0; i < a_locations.size(); i++)
	{
		int row = a_locations[i][0];
		int col = a_locations[i][1];

		if (board[row][col] == '-')
		{
			emptyIndices.push_back(i);
		}
	}

	return emptyIndices;
}

//Given a possible set of 5, finds the number of consecutive pieces that would be achievevd if placed in the empty index.
int Player::FindConsecutiveIfPlaced(Board a_board, vector<vector<int>> a_locations, int emptyIndex)
{
	vector<vector<char>> board = a_board.GetBoard();

	int beforeTotal = 0;
	int afterTotal = 0;

	//Find the number of consecutive pieces before emptyIndex in a_locations.
	int index = emptyIndex;
	while (--index >= 0)
	{
		int row = a_locations[index][0];
		int col = a_locations[index][1];

		if (board[row][col] != '-')
		{
			beforeTotal++;
		}
		else {
			break;
		}
	}

	//Find the number of consecutive pieces after emptyIndex in a_locations.
	index = emptyIndex;
	while (++index < a_locations.size())
	{
		int row = a_locations[index][0];
		int col = a_locations[index][1];

		if (board[row][col] != '-')
		{
			afterTotal++;
		}
		else {
			break;
		}
	}

	//The number of consecutive pieces if placed in the emptyIndex is the number of consecutive pieces before it, plus the number of pieces after it, plus itself.
	return beforeTotal + afterTotal + 1;
}

//Returns the most optimal play when building initiative that already has a_numPlaced pieces of a_color placed.
vector<int> Player::BuildInitiative(Board a_board, int a_numPlaced, char a_color)
{
	vector<vector<char>> board = a_board.GetBoard();
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, a_numPlaced, a_color);

	//If there are no possible moves that satisfy the conditions passed, simply return.
	if (possibleMoves.size() == 0) return {};

	if (a_numPlaced == 1)
	{
		vector<vector<int>> playLocations;

		for (int i = 0; i < possibleMoves.size(); i++)
		{
			//There are 5 locations within each list of possiblemoves
			//The indices 0 and 4 represents the ends of the set of 5 - Ex: * - - - *
			int firstRow = possibleMoves[i][0][0];
			int firstCol = possibleMoves[i][0][1];
			int lastRow = possibleMoves[i][4][0];
			int lastCol = possibleMoves[i][4][1];

			//Find the possible set of 5 where the piece found one one of the ends to make it easier to find the middle.
			//Ex: W - - - - OR - - - - W
			if (board[firstRow][firstCol] != '-' || board[lastRow][lastCol] != '-')
			{
				//possibleMoves[i][2] represents the middle of the set of 5 locations. Ex: W - * - W where * represents the middle.
				//This ensures the new pieces is placed one away from the placed piece and not at risk of capture. 

				//Check if neighbors == 0!!!
				playLocations.push_back(possibleMoves[i][2]);
			}
		}

		//Possibly shuffle this to get a random direction?
		random_shuffle(playLocations.begin(), playLocations.end());
		return playLocations[0];
	}
	else if (a_numPlaced == 2)
	{
		//Search for possible 3 in a rows. If there is one, that is the most optimal play.
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive == 3)
				{
					return possibleMoves[i][emptyIndices[j]];
				}
			}
		}

		//If you can't make a 3 in a row, prefer to place the piece with the least neighbors to avoid being captured. Ex: W - * - W
		int leastCaptures = INT_MAX;
		int leastIndex = INT_MAX;
		int locationIndex = 0;
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive < leastCaptures) {
					leastCaptures = possibleConsectutive;
					leastIndex = emptyIndices[j];
					locationIndex = i;
				}
			}
		}

		return possibleMoves[locationIndex][leastIndex];
	}
	else if (a_numPlaced == 3)
	{
		//Search for possible 4 in a rows. If there is one, that is the most optimal play.
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive == 4)
				{
					return possibleMoves[i][emptyIndices[j]];
				}
			}
		}

		//If there are no possible 4 in a rows, prefer to make 3 in a row (always possible given 3 of a player's piece and 2 empty spots and there is no 4 in a row).
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive == 3)
				{
					return possibleMoves[i][emptyIndices[j]];
				}
			}
		}
	}
	else
	{
		return {};
	}
}

//Checks if it is possible to win, given the current board circumstances.
vector<int> Player::MakeWinningMove(Board a_board, char a_color)
{
	//First check if there are any moves that allow for 5 in a row.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 4, a_color);

	if (possibleMoves.size() > 1)
	{
		//Delay win if multiple win moves to score more points? 
		cout << "Multiple! Delay?" << endl;
	}
	
	if (possibleMoves.size() > 0)
	{
		//If there's only one possible move that creates a 5 in a row, make it.
		vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[0]);
		return possibleMoves[0][emptyIndices[0]];
	}

	//Next, check if you can make a capture to end the game.
	//Note: potentialCaptures is in the form {row, col, numCaptures}
	vector<int> potentialCaptures = MakeCapture(a_board, a_color);

	if (potentialCaptures.size() > 0)
	{
		int numCaptures = potentialCaptures[2];

		if (numCaptures + m_capturedPairs >= 5)
		{
			return potentialCaptures;
		}
	}

	return {};
}


