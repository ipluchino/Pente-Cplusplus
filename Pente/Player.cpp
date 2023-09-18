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

//Converts a row and col in integer form into its respective board intersection as a string.
string Player::ExtractLocation(int row, int col, Board a_board)
{
	int boardRow = a_board.ConvertRowIndex(row);
	char boardCol = a_board.IntToCharacter(col);

	string location = boardCol + to_string(boardRow);
	return location;
}

//Converts a direction index into the direction it represents: horizontal, vertical, main diagonal, and anti diagonal.
string Player::GetDirection(int a_directionIndex)
{
	if (a_directionIndex == 0 || a_directionIndex == 1)
	{
		return "horizontal";
	}
	else if (a_directionIndex == 2 || a_directionIndex == 3)
	{
		return "vertical";
	}
	else if (a_directionIndex == 4 || a_directionIndex == 5)
	{
		return "main-diagonal";
	}
	else if (a_directionIndex == 6 || a_directionIndex == 7)
	{
		return "anti-diagonal";
	}
	else
	{
		return "unknown direction";
	}
}

//Determines the optimal play and returns its location as well as the reasoning why it is the optimal play.
//Assistance Received: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
pair<string, string> Player::OptimalPlay(Board a_board, char a_color)
{
	//Location represents the location on the board of the most optimal play, while reasoning represents the explanation why it is the most optimal.
	string location, reasoning = "The computer placed a stone on ";
	vector<int> possiblePlay;

	//If the board is empty, the only play is the center position, J10. 
	if (a_board.IsEmptyBoard())
	{
		location = "J10";
		reasoning += location + " because the first stone must be placed there.";

		return pair<string, string>(location, reasoning);
	}

	//Attempt to win the game, if possible.
	possiblePlay = MakeWinningMove(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to win the round!";
		return pair<string, string>(location, reasoning);
	}

	//Prevent the opponent from winning the game, if possible.
	possiblePlay = PreventWinningMove(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to prevent the opponent from winning.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to make the most possible captures, if possible.
	possiblePlay = MakeCapture(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to capture the opponent's pieces.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to block the most possible captures, if possible.
	possiblePlay = PreventCapture(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to prevent the opponent from making a capture.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build initiative with 3 pieces already placed.
	possiblePlay = BuildInitiative(a_board, 3, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build initiative and have 4 pieces in an open 5 in the " + GetDirection(possiblePlay[2]) + " direction.";

		return pair<string, string>(location, reasoning);
	}

	//Attempt to counter initiative if the opponent has 3 pieces already placed.
	possiblePlay = CounterInitiative(a_board, 3, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to block the opponent from getting 4 pieces in an open 5 in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build initiative with 2 pieces already placed.
	possiblePlay = BuildInitiative(a_board, 2, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build initiative and have 3 pieces in an open 5 in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to initiate a flank.
	possiblePlay = CounterInitiative(a_board, 2, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to counter initiative and initiate a flank in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build initiative with 1 piece already placed.
	possiblePlay = BuildInitiative(a_board, 1, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build initiative and have 2 pieces in an open 5 in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Play randomly if none of the above applies. Will be changed in the future.
	do {
		int row = 1 + (rand() % 19);
		char col = 'A' + (rand() % 19);

		location = col + to_string(row);

	} while (!a_board.IsEmptyLocation(location[0], stoi(location.substr(1, 2))));

	reasoning += location + " because it played randomly.";

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
vector<vector<vector<int>>> Player::FindAllMoves(Board a_board, int a_numPlaced, char a_color, int a_distance)
{
	//A copy of the board's data.
	vector<vector<char>> board = a_board.GetBoard();

	//Will hold all possible sets of consecutive 5s that has a_numPlaced pieces of the specified color, and 5-numPlaced empty locations.
	vector<vector<vector<int>>> result;

	//To be apart of a possible winning consecutive 5 in the future, there must be at least 5-a_numPlaced empty spaces.
	int emptyRequired = a_distance - a_numPlaced;

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

				for (int distance = 0; distance < a_distance; distance++)
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

					locations.push_back({ newRow, newCol, direction });
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
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, a_numPlaced, a_color, StrategyConstants::CONSECUTIVE_5_DISTANCE);

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
			if ((board[firstRow][firstCol] != '-' || board[lastRow][lastCol] != '-') && !InDangerOfCapture(a_board, possibleMoves[i][2], a_color))
			{
				//possibleMoves[i][2] represents the middle of the set of 5 locations. Ex: W - * - W where * represents the middle.
				//This ensures the new pieces is placed one away from the placed piece and not at risk of capture. 

				//Check if neighbors == 0!!!
				playLocations.push_back(possibleMoves[i][2]);
			}
		}

		//Possibly shuffle this to get a random direction?
		if (playLocations.size() > 0)
		{
			random_shuffle(playLocations.begin(), playLocations.end());
			return playLocations[0];
		}
		else
		{
			return {};
		}
	}
	else if (a_numPlaced == 2)
	{
		//Search for possible 3 in a rows. If there is one, that is the most optimal play.
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive == 3 && !InDangerOfCapture(a_board, possibleMoves[i][emptyIndices[j]], a_color))
				{
					return possibleMoves[i][emptyIndices[j]];
				}
			}
		}

		//If you can't make a 3 in a row, prefer to place the piece with the least neighbors to avoid being captured. Ex: W - * - W
		int leastConsecutive = INT_MAX;
		int leastIndex = INT_MAX;
		int locationIndex = -1;
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive < leastConsecutive && !InDangerOfCapture(a_board, possibleMoves[i][emptyIndices[j]], a_color)) {
					leastConsecutive = possibleConsectutive;
					leastIndex = emptyIndices[j];
					locationIndex = i;
				}
			}
		}

		if (locationIndex != -1)
		{
			return possibleMoves[locationIndex][leastIndex];
		}
		else
		{
			return {};
		}
	}
	else if (a_numPlaced == 3)
	{
		//Search for possible 4 in a rows. If there is one, that is the most optimal play.
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive == 4 && !InDangerOfCapture(a_board, possibleMoves[i][emptyIndices[j]], a_color))
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
				if (possibleConsectutive == 3 && !InDangerOfCapture(a_board, possibleMoves[i][emptyIndices[j]], a_color))
				{
					return possibleMoves[i][emptyIndices[j]];
				}
			}
		}

		//If there aren't any possible places that don't result in capture, return nothing.
		return {};
	}
	else
	{
		return {};
	}
}

vector<int> Player::CounterInitiative(Board a_board, int a_numPlaced, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);

	if (a_numPlaced == 2)
	{
		vector<int> possibleFlank = FindFlanks(a_board, a_color);
		
		if (possibleFlank.size() > 0)
		{
			return possibleFlank;
		}
		else
		{
			return {};
		}

	}
	else if (a_numPlaced == 3)
	{
		//Blocking a potential 4 in a row, or 4 pieces in an open 5. The best place to block is where the opponent wants to go next.
		vector<int> counterLocation = BuildInitiative(a_board, a_numPlaced, opponentColor);

		if (counterLocation.size() > 0)
		{
			return counterLocation;
		}
		else
		{
			return {};
		}
	}

	//The computer will only consider countering initiaitve to start a flank on an opponent or two block the opponent from getting 4 in a row/4 in an open 5.
	//PreventWinningMove() handles blocking potential win moves.
	return {};
}

//Checks if it is possible to win, given the current board circumstances.
vector<int> Player::MakeWinningMove(Board a_board, char a_color)
{
	//First check if there are any moves that allow for 5 in a row.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 4, a_color, StrategyConstants::CONSECUTIVE_5_DISTANCE);

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

vector<int> Player::PreventWinningMove(Board a_board, char a_color)
{
	//If the opponent has any winning moves they can do on their next turn, this is the location that you should block.
	char opponentColor = a_board.OpponentColor(a_color);
	vector<int> preventWin = MakeWinningMove(a_board, opponentColor);

	if (preventWin.size() > 0)
	{
		return preventWin;
	}
	else
	{
		return {};
	}
}

//Returns true if placing a piece in a_location will put the player at risk of being captured.
bool Player::InDangerOfCapture(Board a_board, vector<int> a_location, char a_color)
{
	vector<vector<char>> board = a_board.GetBoard();
	
	int row = a_location[0];
	int col = a_location[1];
	
	char opponentColor = a_board.OpponentColor(a_color);

	//To determine if playing a piece will put the player at risk of being captured, locations will need to be checked in opposite directions.
	vector<int> currentDirection;
	vector<int> oppositeDirection;
	for (int direction = 0; direction < StrategyConstants::NUM_DIRECTIONS; direction++)
	{
		//Multiplying the row instruction and the column instruction by -1 results in the instructions for the opposite direction.
		currentDirection = StrategyConstants::DIRECTIONS[direction];
		oppositeDirection = { StrategyConstants::DIRECTIONS[direction][0] * -1, StrategyConstants::DIRECTIONS[direction][1] * -1 };

		//To be in danger of being captured there must be this pattern: - * P O
		// - is an empty space, * is the current location being evaluated, P is the current players piece, and O is the opponents piece.
		//The empty location should be one in the opposite direction that is currently being evaluated.
		int emptyRow = row + oppositeDirection[0];
		int emptyCol = col + oppositeDirection[1];

		//Your piece should be a distance of 1 away in the current direction.
		int yourPieceRow = row + currentDirection[0];
		int yourPieceCol = col + currentDirection[1];

		//The opponent's piece should be a distance of 2 away in the current direction.
		int opponentPieceRow = row + currentDirection[0] * 2;
		int opponentPieceCol = col + currentDirection[1] * 2;

		if (a_board.IsValidIndices(emptyRow, emptyCol) && a_board.IsValidIndices(yourPieceRow, yourPieceCol) && a_board.IsValidIndices(opponentPieceRow, opponentPieceCol))
		{
			if (board[emptyRow][emptyCol] == '-' && board[yourPieceRow][yourPieceCol] == a_color && board[opponentPieceRow][opponentPieceCol] == opponentColor)
			{
				return true;
			}
		}
	}

	return false;
}

//Finds potential flanks where you can initiate a capture. Searches for the pattern: * W W * on the board.
vector<int> Player::FindFlanks(Board a_board, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);

	//Search all possible sets of 4 locations that have two opponent's stones and 2 empty locations.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 2, opponentColor, 4);

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

		//Search for sets of 4 locations that are in the pattern: * W W * where * are empty locations and W is the opponent's pieces. This is where a flank can be initiated.
		if (emptyIndices[0] == 0 && emptyIndices[1] == 3)
		{
			if (!InDangerOfCapture(a_board, possibleMoves[i][0], a_color))
			{
				return possibleMoves[i][0];
			}
			else if (!InDangerOfCapture(a_board, possibleMoves[i][3], a_color))
			{
				return possibleMoves[i][1];
			}
		}
	}

	return {};
	return vector<int>();
}


