/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Player class - implementation file.
* Date : 9/27/23
************************************************************/

#include "Player.h"

/* *********************************************************************
Function Name: Player - Default constructor
Purpose: To construct a Player object.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Player::Player() : m_color('W'), m_score(0), m_capturedPairs(0)
{
	srand(unsigned(time(NULL)));
}

/* *********************************************************************
Function Name: SetColor
Purpose: To set the color of a Player.
Parameters:
			a_color, a character representing the color to set the Player's color to.
Return Value: Whether or not the color was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::SetColor(char a_color)
{
	if (a_color != 'W' && a_color != 'B') return false;

	m_color = a_color;

	return true;
}

/* *********************************************************************
Function Name: SetScore
Purpose: To set the score of a Player.
Parameters:
			a_score, an integer representing the score to set the Player's score to.
Return Value: Whether or not the score was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::SetScore(int a_score)
{
	if (a_score < 0) return false;

	m_score = a_score;
	
	return true;
}

/* *********************************************************************
Function Name: SetCapturedPairs
Purpose: To set the captured pair count of a Player.
Parameters:
			a_capturedPairs, an integer representing the captured pair count to set the Player's captured pair count to.
Return Value: Whether or not the captured pair count was successfully set, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::SetCapturedPairs(int a_capturedPairs)
{
	if (a_capturedPairs < 0) return false;

	m_capturedPairs = a_capturedPairs;

	return true;
}

/* *********************************************************************
Function Name: MakePlay
Purpose: Virtual function that is redefined in the Human and Computer class. This function does nothing.
Parameters:
			a_board, a reference to a Board object. It is a reference and not a copy since pieces will be placed on the board.  
Return Value: Whether or not the player has successfully placed a stone, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Player::MakePlay(Board& a_board)
{
	return true;
}

/* *********************************************************************
Function Name: ExtractLocation
Purpose: To convert a vector index row/col to a board view representation in the format: "J10".
Parameters:
			a_row, an integer representing the vector index of a row.
			a_col, an integer representing the vector index of a column.
			a_board, a Board object representing the current board of the round.
Return Value: The board view representation of the provided location, a string.
Algorithm:
			1) Convert the vector index of the row to its board view represenation.
			2) Convert the vector index of the column to its board view representation as a character.
			3) Concatenate the values from step 1 and 2 into a string, and return it. 
Assistance Received: None
********************************************************************* */
string Player::ExtractLocation(int a_row, int a_col, Board a_board)
{
	int boardRow = a_board.ConvertRowIndex(a_row);
	char boardCol = a_board.IntToCharacter(a_col);

	string location = boardCol + to_string(boardRow);
	return location;
}

/* *********************************************************************
Function Name: GetDirection
Purpose: To convert a directional index into its string representation.
Parameters:
			a_directionIndex, an integer representing 
Return Value: The name of the direction, as a string.
Algorithm: None
Assistance Received: None
********************************************************************* */
string Player::GetDirection(int a_directionIndex)
{
	return StrategyConstants::DIRECTION_NAMES[a_directionIndex];
}

//Determines the optimal play and returns its location as well as the reasoning why it is the optimal play.
/* *********************************************************************
Function Name: OptimalPlay
Purpose: To determine 
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the player's stone color.
Return Value: A pair<string, string> where the first string is the location of the most optimal play, and the second string is the reasoning behind the play.
Algorithm: Several functions are used to determine the most optimal play. The priorities are as follows:
			1) If the board is empty, the only possible move is the center of the board, or J10.
			2) If it's possible to win the round with the player's next move, by either making five consecutive stones or by capture, win the round.
				2a) If it's possible to delay the win the earn more points, the win will be delayed (see MakeWinningMove function).
			3) If the opponent is about to win the round by making five consecutive pieces on their following turn, prevent it.
			4) If it's possible to build a deadly tessera, build one.
			5) If the opponent can build a deadly tessera on their next turn, block it.
			6) If the player can make a capture, make the move that results in the most captured pairs.
			7) If the opponent can make a capture on their following turn, make the move that prevents the most captured pairs.
			8) If the player can build initiative with three of their stones already placed, do it.  
			9) If the opponent can build initiative with three of their stones already placed on their following turn, block it.
			10) If the player can build initiative with two of their stones already placed, do it.
			11) If the opponent has placed two consecutive stones that can be captured, initiate a flank.
			12) If the player can build initiative with two of their stones already placed, do it.
			13) If the opponent can build initiative with two of their stones already placed on their following turn, block it.
				13a) This also is used to begin a player's initiative when they do not have any stones placed on the board.
			14) As a failsafe, return any empty location on the board. This is only used when the board is nearly full and none of the above moves apply.

Assistance Received: https://cplusplus.com/reference/algorithm/random_shuffle/
********************************************************************* */
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
	string winReason = "";
	possiblePlay = MakeWinningMove(a_board, a_color, winReason);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + winReason;
		return pair<string, string>(location, reasoning);
	}

	//Prevent the opponent from winning the game, if possible.
	possiblePlay = PreventWinningMove(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to block the opponent from getting five consecutive stones in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build a deadly tessera, aka four consecutive stones with an empty location on either side.
	possiblePlay = FindDeadlyTessera(a_board, a_color, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build a deadly tessera in the " + GetDirection(possiblePlay[2]) + " direction.";

		return pair<string, string>(location, reasoning);
	}

	//Attempt to block a deadly tessera from forming.
	possiblePlay = FindDeadlyTessera(a_board, a_board.OpponentColor(a_color), a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to block deadly tessera from forming in the " + GetDirection(possiblePlay[2]) + " direction.";

		return pair<string, string>(location, reasoning);
	}

	//Attempt to make the most possible captures, if possible.
	possiblePlay = MakeCapture(a_board, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to capture the opponent's stones.";
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

	//Attempt to build initiative with 3 stones already placed.
	possiblePlay = BuildInitiative(a_board, 3, a_color, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build initiative and have 4 stones in an open consecutive 5 in the " + GetDirection(possiblePlay[2]) + " direction.";

		return pair<string, string>(location, reasoning);
	}

	//Attempt to counter initiative if the opponent has 3 stones already placed.
	possiblePlay = CounterInitiative(a_board, 3, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to block the opponent from getting 4 stones in an open consecutive 5 in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to build initiative with 2 stones already placed.
	possiblePlay = BuildInitiative(a_board, 2, a_color, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build initiative and have 3 stones in an open consecutive 5 in the " + GetDirection(possiblePlay[2]) + " direction.";
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

	//Attempt to build initiative with 1 stone already placed.
	possiblePlay = BuildInitiative(a_board, 1, a_color, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to build initiative and have 2 stones in an open consecutive 5 in the " + GetDirection(possiblePlay[2]) + " direction.";
		return pair<string, string>(location, reasoning);
	}

	//Attempt to counter initiative with stone piece already placed - used for the first move when going second.
	possiblePlay = CounterInitiative(a_board, 1, a_color);
	if (possiblePlay.size() != 0)
	{
		location = ExtractLocation(possiblePlay[0], possiblePlay[1], a_board);
		reasoning += location + " to counter the opponent's initiative and start building initiative.";
		return pair<string, string>(location, reasoning);
	}

	//If no other strategies can be used, find an open spot on the board and place it there. This is a failsafe for the edge case where the board is near full.
	do {
		int row = 1 + (rand() % 19);
		char col = 'A' + (rand() % 19);

		location = col + to_string(row);

	} while (!a_board.IsEmptyLocation(location[0], stoi(location.substr(1, 2))));

	reasoning += location + " because there is no other optimal move.";
	return pair<string, string>(location, reasoning);
}

//Returns a vector<int> that contains {row, col} of best possible location to place your piece to make the most captures.
//Returns an empty vector if there are no potential captures to be made.
/* *********************************************************************
Function Name: MakeCapture
Purpose: To find a location on the board that results in the most captures possible, if any exist.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the player's stone color.
Return Value: A vector<int> containing the row and column of the best possible location that results in the most captures.
Algorithm:
			1) Loop through every possible location on the board.
			2) If the location is empty, obtain the number of captures that would occur if the player places their stone here. 
				2a) This number is calculated through the CanCaptureIfPlaced function.
			3) If the number of captures possible when placing a stone at the location being evaluated is greater than zero,
			   log its information to a result vector, including the number of captures that will occur.
			4) After all the possible capture locations are found and saved, sort the result vector by its capture count.
			5) Return the first vector within the result vector, since it will be the location that captures the most stones at one time.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name: CanCaptureIfPlaced
Purpose: To determine the number of captures that would occur if 
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the player's stone color.
			a_row, an integer representing a row for a player to place their stone.
			a_col, an integer representing a column for a player to place their stone.
Return Value: The number of captured pairs that would occur if a player plays their stone at a specified location, an integer.
Algorithm:
			1) Determine the opponent's stone color.
			2) Loop through all eight possible directions.
			3) For each direction, store the locations of three spaces out in the current direction. 
			4) If all location are valid, check to see if a capture can be made. For example, if the color passed was white, a capture follows 
			   the pattern * B B W where * is the location passed to this function.
			5) If there is a capture that has been made in the direction being evaluated, increment a capture counter.
			6) Return the total number of captures that can be made if a player's stone is placed at the location passed to this function.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name: PreventCapture
Purpose: To find a location on the board that prevents the opponent from making a capture on their following turn.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the player's stone color.
Return Value: A vector<int> containing the row and column of the location that blocks the opponent from making a capture on their next turn.
Algorithm:
			1) Find the opponent's stone color. 
			2) Determine if the opponent can make any captures based on the current board (using the MakeCapture function).
			3) Return the location that prevents the most possible captures, if any exists.
Assistance Received: None
********************************************************************* */
vector<int> Player::PreventCapture(Board a_board, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);

	//If the opponent has the ability to make a capture, or multiple, on their next turn, it should be blocked.
	vector<int> possiblePreventCapture = MakeCapture(a_board, opponentColor);
	
	return possiblePreventCapture;
}

/* *********************************************************************
Function Name: FindAllMoves
Purpose: To find all possible sets of locations given constraints regarding the stone color, stone count, and a number of consecutive locations.
		 This function is used to search for a variety of different situations and is used in several different functions.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_numPlaced, an integer representing the number of a player's stone to search for.
			a_color, a character representing the player's stone color to search for.
			a_distance, an integer representing the number of consecutives locations to be included in the search.
Return Value: A vector<vector<vector<int>>> possible sets of consecutive a_distance locations that has a_numPlaced pieces of the specified color, 
			  and a_distance - a_numPlaced empty locations. 
Algorithm:
			1) Loop through every possible location on the board.
			2) For each location on the board, loop through each of the main directions: horizontals, verticals, and diagonals.
			3) Search and store a_distance locations in the current direction being evaluated.
				3a) If any of the locations are invalid in terms of board size constraints, stop searching and skip to the next direction.
			4) If all of the locations are valid, tally up the number of empty locations and the number of locations that have a stone of the specified color placed.
			5) If the number of empty locations is equal to a_distance - a_numPlaced and the number of placed stones of a_color is equal to a_numPlaced,
			   add this set of locations to the final result vector.
			6) After searching through every location on the board and every location, return the final result vector.
Assistance Received: None
********************************************************************* */
vector<vector<vector<int>>> Player::FindAllMoves(Board a_board, int a_numPlaced, char a_color, int a_distance)
{
	//A copy of the board's data.
	vector<vector<char>> board = a_board.GetBoard();

	//Will hold all possible sets of consecutive a_distance locations that has a_numPlaced pieces of the specified color, and a_distance - a_numPlaced empty locations.
	vector<vector<vector<int>>> result;

	//The empty locations required to be valid is a_distance - a_numPlaced. 
	int emptyRequired = a_distance - a_numPlaced;

	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			//Only need to search the main directions: horizontals, verticals, main diagonals, and anti-diagonals.
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

				//If the number of pieces and empty locations satisfy their conditions, record this set of locations to the result vector.
				if (pieceCounter == a_numPlaced && emptyCounter == emptyRequired)
				{
					result.push_back(locations);
				}
			}
		}
	}

	return result;
}

/* *********************************************************************
Function Name: FindEmptyIndices
Purpose: To find all of the indices that are empty, given a set of locations.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_locations, a vector<vector<int>> representing a set of locations on the board.
Return Value: A vector<int> containing the indices of a_locations that are empty locations on the board.
Algorithm:
			1) Loop through each location in a_locations. 
			2) If the location is empty, log the index of a_locations being evaluated.
			3) After looping through each location, return the vector containing all the empty indices.
Assistance Received: None
********************************************************************* */
vector<int> Player::FindEmptyIndices(Board a_board, vector<vector<int>> a_locations)
{
	vector<vector<char>> board = a_board.GetBoard();
	vector<int> emptyIndices;

	//Search through the set of locations and mark the empty indices.
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

/* *********************************************************************
Function Name: FindConsecutiveIfPlaced
Purpose: To find the number of consecutive pieces that would be placed on the board given a set of locations and an index to place the stone.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_locations, a vector<vector<int>> representing a set of locations on the board.
			a_emptyIndex, an integer representing the index in a_locations that is empty on the board.
Return Value: The number of consecutive pieces that will occur if a stone is placed a_locations[emptyIndex], an integer.
Algorithm:
			1) From the empty index, count the number of consecutive pieces that come immediately before the empty index.
			2) From the empty index, count the number of consecutive pieces that come immediately after the empty index.
			3) Sum the two numbers from steps 1 and 2, and add one to the sum to represent the piece being placed. Return this sum.
Assistance Received: None
********************************************************************* */
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
/* *********************************************************************
Function Name: BuildInitiative
Purpose: To find a location on the board that builds initiative for the player.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_numPlaced, an integer representing the amount of stones placed by the player in an open five consecutive locations.
			a_color, a character representing the player's stone color.
			a_dangerColor, a character representing the stone color to check if placing it at a location would put it at risk of being captured.
Return Value:  A vector<int> containing the row, column, and direction being built in of the best location to build initiative, if any exist.	
Algorithm:
			1) Find all possible moves consecutive five locations that satisfy the conditions passed to this function (using the FindAllMoves function).
				1a) If there are no possible moves given the search parameters, simply return an empty vector.
			2) If a_numPlaced is equal to 1:
				2a) Loop through each possible set of five consecutive locations.
				2b) For each possible set of locations, find the sets where the single placed stone is on one of the ends. Ex: B - - - - OR - - - - B
				2c) Store the middle location in a vector, to ensure the stone is placed a distance of one away of the current stone. Ex: B - * - - OR - - * - - B
					Only locations that do not put the player in danger of being captured is stored.
				2d) After finding all potential build locations, shuffle the result vector to build in a new location each time. 
					This is so the player builds in all directions and not only one specific direction each time.
				2e) Return the 
			3) If a_numPlaced is equal to 2:
				3a) Search for possible locations that would form three consecutive stones placed and does not put the player in danger of being captured. 
					If one exists, return this location.
				3b) If it isn't possible to get three consecutive stones placed, prefer to place the stone in a location that results in the least consecutive pieces. 
					1. Loop through each possible set of five consecutive locations found in step 1.
					2. For each set of locations, find the indices of the empty locations.
					3. For each location that is empty, find the number of consecutive pieces that would occur if the player places their stone there. 
					4. If the number of consecutive pieces is the least seen so far and does not put the player at risk of being captured, log it.
					5. After looping through all possible sets of locations and repeating the above steps, return the location that results in the least consecutive pieces.
					   This puts the player in the least risk of getting captured in the future. Ex: B - * - B
			4) If a_numPlaced is equal to 3:
				4a) Search for possible locations that will form four consecutive pieces and does not put the player in danger of being captured. 
					If one exists, return this location. Ex : B B B * - 
				4b) Search for possible locations that will form three consecutive pieces and does not put the player in danger of being captured. 
					If one exists, return this location. Ex: B * B - B
Assistance Received: None
********************************************************************* */
vector<int> Player::BuildInitiative(Board a_board, int a_numPlaced, char a_color, char a_dangerColor)
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

			//Find the possible set of 5 where the piece found one one of the ends to make it easier to find the middle. Ex: W - - - - OR - - - - W
			if ((board[firstRow][firstCol] != '-' || board[lastRow][lastCol] != '-') && !InDangerOfCapture(a_board, possibleMoves[i][2], a_dangerColor))
			{
				//possibleMoves[i][2] represents the middle of the set of 5 locations. Ex: W - * - W where * represents the middle.
				//This ensures the new pieces is placed one away from the placed piece and not at risk of capture. 
				playLocations.push_back(possibleMoves[i][2]);
			}
		}

		//Shuffle the possible locations (there will often be many) so that the computer builds in different directions, not only the first direction it finds.
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
		vector<int> possibleThreeConsecutive = FindThreeConsecutive(a_board, possibleMoves, a_dangerColor);

		if (possibleThreeConsecutive.size() != 0)
		{
			return possibleThreeConsecutive;
		}

		//If you can't make a 3 in a row, prefer to place the piece with the least neighbors to avoid being captured. Ex: W - * - W
		int leastConsecutive = INT_MAX;
		int leastIndex = INT_MAX;
		int locationIndex = -1;
		for (int i = 0; i < possibleMoves.size(); i++) {
			vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

			for (int j = 0; j < emptyIndices.size(); j++) {
				int possibleConsectutive = FindConsecutiveIfPlaced(a_board, possibleMoves[i], emptyIndices[j]);
				if (possibleConsectutive < leastConsecutive && !InDangerOfCapture(a_board, possibleMoves[i][emptyIndices[j]], a_dangerColor)) {
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
		vector<int> possibleFourConsecutive = FindFourConsecutive(a_board, possibleMoves, a_dangerColor);
		if (possibleFourConsecutive.size() != 0)
		{
			return possibleFourConsecutive;
		}

		//Search for possible 3 in a rows. If there is one, that is the most optimal play.
		vector<int> possibleThreeConsecutive = FindThreeConsecutive(a_board, possibleMoves, a_dangerColor);
		if (possibleThreeConsecutive.size() != 0)
		{
			return possibleThreeConsecutive;
		}

		return {};
	}
	else
	{
		return {};
	}
}

/* *********************************************************************
Function Name: CounterInitiative
Purpose: To find a location on the board that counters the initiative of the opponent.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_numPlaced, an integer representing the amount of stones placed by the opponent in an open five consecutive locations.
			a_color, a character representing the player's stone color.
Return Value: A vector<int> containing the row, column, and direction being blocked of the best location to counter initiative, if any exist.
Algorithm:
			1) Determine the opponent's stone color.
			2) IF a_numPlaced is equal to 2:
				2a) Find any locations on the board that would initiate a flank. For example, if the opponent has two consecutive stones placed that have
				    an empty location on either side, an attempt to capture them over two turns can occur.
				2b) If any location exists on the board that can initiate a flank, return it.
			3) IF a_numPlaced is equal to 1 OR 3:
				3a) Call the BuildInitiative function with the opponent's color to find the opponent's next best possible move when building initiative.
				3b) If a location is returned from the function above, return this location as it is the most optimal location to block.
Assistance Received: None
********************************************************************* */
vector<int> Player::CounterInitiative(Board a_board, int a_numPlaced, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);

	if (a_numPlaced == 2)
	{
		//Finding any potential flanks.
		vector<int> possibleFlank = FindFlanks(a_board, a_color);
		
		if (possibleFlank.size() > 0)
		{
			return possibleFlank;
		}
		
		return {};

	}
	else if (a_numPlaced == 1 || a_numPlaced == 3)
	{
		//When blocking, the most optimal placement to block is where your opponent wants to place their stone on their following turn.
		vector<int> counterLocation = BuildInitiative(a_board, a_numPlaced, opponentColor, a_color);

		if (counterLocation.size() > 0)
		{
			return counterLocation;
		}
		
		return {};
	}

	return {};
}

//Checks if it is possible to win, given the current board circumstances.
/* *********************************************************************
Function Name: MakeWinningMove
Purpose: To find a location on the board that would cause the player to win the round.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the player's stone color.
			a_winReason, a string passed by reference to explain the reasoning of the win, or if the win is being delayed, since there are multiple ways to win.
Return Value: A vector<int> containing the row and column of the location that would result in the player winning the game.
Algorithm: 
			1) Find all consecutive five locations that have four of the player's stone already placed, and one empty location.
			2) If there are multiple sets of five locations, the win may be delayed to earn additional points.
				2a) If the player is not in danger of being captured on their following turn, and they can capture the opponents pieces,
					opt to capture the most opponent's stones possible to earn additional points.
			3) If there is only one location that would result in five consecutive stones and win the round for the player, return this location.
			4) If it isn't possible to make five consecutive stones, check to see if its possible to win by obtaining at least five captured pairs.
				4a) If the number of captured pairs already obtained plus the maximum number of captured pairs that can be acquired is at least five,
					make the capture(s) to win the round.
			5) If there are no winning moves, return an empty vector.
Assistance Received: None
********************************************************************* */
vector<int> Player::MakeWinningMove(Board a_board, char a_color, string& a_winReason)
{
	//First check if there are any moves that allow for five consecutive pieces.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 4, a_color, StrategyConstants::CONSECUTIVE_5_DISTANCE);

	if (possibleMoves.size() > 1)
	{
		//If there are multiple win moves, see if the win can be delayed to earn additional points.
		//The win will only be delayed if the player is not in danger of getting captured and giving more points to the opponent.
		vector<int> opponentCaptures = PreventCapture(a_board, a_color);
		if (opponentCaptures.size() == 0)
		{
			//Check if any captures can be made to score additional points.
			vector<int> potentialCaptures = MakeCapture(a_board, a_color);

			if (potentialCaptures.size() > 0)
			{
				a_winReason = " to capture the opponent's stones. The win is being delayed to score additional points.";
				return potentialCaptures;
			}
		}

	}
	
	if (possibleMoves.size() > 0)
	{
		//If there's only one possible move that creates five consecutive pieces, make it and win the round.
		vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[0]);

		//Note: The vector containing the empty location is in the format {row, col, directionIndex},
		a_winReason = " to make five consecutive piece in the " + GetDirection(possibleMoves[0][emptyIndices[0]][2]) + " direction and win the round.";
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
			a_winReason = " to capture the opponent's pieces and have at least five captured pairs to win the round.";
			return potentialCaptures;
		}
	}

	return {};
}

/* *********************************************************************
Function Name: PreventWinningMove
Purpose: To find a location on the board that prevents the opponent from winning the round.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the player's stone color.
Return Value: A vector<int> containing the row and column of the location that would result in the player preventing the opponent from winning the game.
Algorithm:
			1) Determine the opponent's stone color.
			2) Find all possible sets of five consecutive locations in which the opponent has four stones placed and one empty location.
			3) If any of these sets of locations exist, find the index of the empty location.
			4) Return the empty location, since this location must be blocked or the opponent can win on their following turn.
Assistance Received: None
********************************************************************* */
vector<int> Player::PreventWinningMove(Board a_board, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);
	
	//If the opponent has any winning moves they can do on their next turn, this is the location that you should block.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 4, opponentColor, StrategyConstants::CONSECUTIVE_5_DISTANCE);

	if (possibleMoves.size() > 0)
	{
		//If there's a move that creates a 5 in a row for the opponent, you must block it.
		vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[0]);
		return possibleMoves[0][emptyIndices[0]];
	}
	else
	{
		return {};
	}
}

/* *********************************************************************
Function Name: InDangerOfCapture
Purpose: To determine if placing a stone in a specified location would put the player in danger of being captured on the following turn.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_location, a vector<int> representing the row and column being checked.
			a_color, a character representing the stone color of the player placing the stone at a_location.
Return Value: Whether or not the player is at risk of being captured the following turn, a boolean value.
Algorithm:
			1) Find the stone color of the opponent.
			2) Loop through all eight possible directions.
			3) For each direction, find the opposite direction by multiplying the direction instructions by -1. Ex: up's opposite direction is down.
			4) Search two spaces out in the current direction and one space in the opposite direction.
			5) If all locations in the previous step are valid, evaluate if the opponent can make a capture if the player places their stone at a_location.
				5a) If the stones are in the pattern: - * P O, where * represents a_location, P is the player's stone, O is the opponent's stone, 
					and - is an empty location, the player is in danger of being captured if they place their stone at a_location. Return true.
				5b) If the stones are in the pattern: - P * O where * represents a_location, P is the player's stone, O is the opponent's stone, 
					and - is an empty location, the player is in danger of being captured if they place their stone at a_location. Return true.
			6) Otherwise, return false if the player is not in danger of being captured on their following turn if they place their stone at a_location.
Assistance Received: None
********************************************************************* */
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

		//To be in danger of being captured there must be this pattern: - * P O OR this pattern: - P * O
		// - is an empty space, * is the current location being evaluated, P is the current players piece, and O is the opponents piece.
		
		//The row, col pair that is a distance of one away in the opposite direction being evaluated.
		int oppositeDirRow = row + oppositeDirection[0];
		int oppositeDirCol = col + oppositeDirection[1];

		//The row, col pair that is a distance of one away in the current direction being evaluated.
		int currentDirOneAwayRow = row + currentDirection[0];
		int currentDirOneAwayCol = col + currentDirection[1];

		//The row, col pair that is a distance of two away in the current direction being evaluated.
		int currentDirTwoAwayRow = row + currentDirection[0] * 2;
		int currentDirTwoAwayCol = col + currentDirection[1] * 2;

		if (a_board.IsValidIndices(oppositeDirRow, oppositeDirCol) && a_board.IsValidIndices(currentDirOneAwayRow, currentDirOneAwayCol) && a_board.IsValidIndices(currentDirTwoAwayRow, currentDirTwoAwayCol))
		{
			//Handling the pattern: - * P O
			if (board[oppositeDirRow][oppositeDirCol] == '-' && board[currentDirOneAwayRow][currentDirOneAwayCol] == a_color && board[currentDirTwoAwayRow][currentDirTwoAwayCol] == opponentColor)
			{
				return true;
			}

			//Handling the pattern: - P * O
			if (board[oppositeDirRow][oppositeDirCol] == opponentColor && board[currentDirOneAwayRow][currentDirOneAwayCol] == a_color && board[currentDirTwoAwayRow][currentDirTwoAwayCol] == '-')
			{
				return true;
			}
		}

	}

	return false;
}

//Finds potential flanks where you can initiate a capture. Searches for the pattern: * W W * on the board.
/* *********************************************************************
Function Name: FindFlanks
Purpose: To find a location on the board that will initiate a flank.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the stone color to search for flanks.
Return Value: A vector<int> containing the row, column, and direction being built in, if it exists.
Algorithm:
			1) Find the stone color of the opponent.
			2) Find all valid consecutive four locations that have two of the opponent's stone color and two empty locations.
			3) Loop through each of the possible sets of four locations.
			4) For each set of locations, find the indices of the empty locations.
			5) If the empty indices are 0 and 3, representing the ends of the consecutive four locations, a flank can be initiated.
			   Return one of these empty locations if they do not put the player in danger of being captured.
			6) Otherwise, return an empty vector if nothing was found.
Assistance Received: None
********************************************************************* */
vector<int> Player::FindFlanks(Board a_board, char a_color)
{
	char opponentColor = a_board.OpponentColor(a_color);

	//Search all possible sets of 4 locations that have two opponent's stones and 2 empty locations.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 2, opponentColor, 4);

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

		//If the empty indices are 0 and 3, they are on the ends of the consecutive 4 locations (* W W *), and it means that a flank can be initiated.
		if (emptyIndices[0] == 0 && emptyIndices[1] == 3)
		{
			if (!InDangerOfCapture(a_board, possibleMoves[i][0], a_color))
			{
				return possibleMoves[i][emptyIndices[0]];
			}
			else if (!InDangerOfCapture(a_board, possibleMoves[i][3], a_color))
			{
				return possibleMoves[i][emptyIndices[1]];
			}
		}
	}

	return {};
}

/* *********************************************************************
Function Name: FindDeadlyTessera
Purpose: To find a location on the board that would create a deadly tessera (four consecutive pieces with an empty location on either side).
Parameters:
			a_board, a Board object representing the current board of the round.
			a_color, a character representing the stone color to search for deadly tesseras.
			a_dangerColor, a character representing the stone color to check if it is in danger of being captured.
Return Value: A vector<int> containing the row, column, and direction being built in, if it exists.
Algorithm:
			1) Find all valid consecutive six locations that have three of the specified piece color and three empty locations.
			2) Loop through each of the possible sets of six locations.
			3) For each set of locations, find the indices of the empty locations.
			4) If two of the three empty indices are 0 and 5, representing the ends of the consecutive six locations, a deadly tessera can be built.
			5) Store the empty location that is NOT on either of the ends of the consecutive six locations so it can be used later.
			6) Loop through all possible placements (if any exist) and search if any do not put the player at risk of capture. If any do not, return this location.
			7) If all result in capture, return any of the possible placements regardless as deadly tesseras are still worth building. 
			5) Otherwise, if there are no deadly tesseras to be built, return an empty vector if nothing was found.
Assistance Received: None
********************************************************************* */
vector<int> Player::FindDeadlyTessera(Board a_board, char a_color, char a_dangerColor)
{
	//Search for all valid consecutive 6 locations that have 3 of the specified piece color and 3 empty locations.
	//Deadly tesseras are in the form: - B B * B - , where both ends of the set of six are empty.
	vector<vector<vector<int>>> possibleMoves = FindAllMoves(a_board, 3, a_color, 6);

	vector<vector<int>> possiblePlacements;

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		vector<int> emptyIndices = FindEmptyIndices(a_board, possibleMoves[i]);

		//If both ends of the set of 6 locations are empty (the empty indices are 0 and 5), this means that a deadly tessera can be formed.
		if (emptyIndices[0] == 0 && emptyIndices[2] == 5)
		{
			//emptyIndices[1] is the empty location that is NOT on one of the ends. 
			//This creates four consecutive stones with two open ends when a stone is placed there. Store it for later.
			possiblePlacements.push_back(possibleMoves[i][emptyIndices[1]]);
		}
	}

	if (possiblePlacements.size() > 0)
	{
		//Return the location that does NOT put the player in danger of getting captured.
		for (int i = 0; i < possiblePlacements.size(); i++)
		{
			if (!InDangerOfCapture(a_board, possiblePlacements[i], a_dangerColor))
			{
				return possiblePlacements[i];
			}
		}

		//If all possible locations result in capture, deadly tesseras should still be built/blocked as it likely results in a win in the following turns.
		return possiblePlacements[0];
	}
	else
	{
		return {};
	}

}

/* *********************************************************************
Function Name: FindThreeConsecutive
Purpose: To find a location on the board that would create three consecutive pieces, if any are possible, given multiple sets of possible locations to build on.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_possibleMoves, a vector<vector<vector<int>>> containing sets of locations. Example: {{{row1, col1, direction}, {row2, col2, direction}}, {{}}, ...}}}
			a_dangerColor, a character representing the stone color to check if it is in danger of being captured.
Return Value: A vector<int> containing the row, column, and direction being built in, if it exists.
Algorithm:
			1) Loop through every set of possible locations within a_possibleMoves.
			2) For each set, find the indices of the empty locations.
			3) For each empty index, find the number of consecutive pieces that would occur if a stone was placed there.
			4) If the number of consecutive pieces that would occur is three, return this location if it does not put the player in danger of being captured.
			5) Otherwise, return an empty vector if nothing was found.
Assistance Received: None
********************************************************************* */
vector<int> Player::FindThreeConsecutive(Board a_board, vector<vector<vector<int>>> a_possibleMoves, char a_dangerColor)
{
	//Search for possible 3 in a rows. If there is one, that is the most optimal play.
	for (int i = 0; i < a_possibleMoves.size(); i++) {
		vector<int> emptyIndices = FindEmptyIndices(a_board, a_possibleMoves[i]);

		for (int j = 0; j < emptyIndices.size(); j++) {
			int possibleConsectutive = FindConsecutiveIfPlaced(a_board, a_possibleMoves[i], emptyIndices[j]);
			
			//If it's possible to create four consecutive stones, and it doesn't put the player in danger of being captured, return it.
			if (possibleConsectutive == StrategyConstants::CONSECUTIVE_3_DISTANCE && !InDangerOfCapture(a_board, a_possibleMoves[i][emptyIndices[j]], a_dangerColor))
			{
				return a_possibleMoves[i][emptyIndices[j]];
			}
		}
	}

	return {};
}

/* *********************************************************************
Function Name: FindFourConsecutive
Purpose: To find a location on the board that would create four consecutive pieces, if any are possible, given multiple sets of possible locations to build on.
Parameters:
			a_board, a Board object representing the current board of the round.
			a_possibleMoves, a vector<vector<vector<int>>> containing sets of locations. Example: {{{row1, col1, direction}, {row2, col2, direction}}, {{}}, ...}}}
			a_dangerColor, a character representing the stone color to check if it is in danger of being captured.
Return Value: A vector<int> containing the row, column, and direction being built in, if it exists.
Algorithm:
			1) Loop through every set of possible locations within a_possibleMoves.
			2) For each set, find the indices of the empty locations.
			3) For each empty index, find the number of consecutive pieces that would occur if a stone was placed there.
			4) If the number of consecutive pieces that would occur is four, return this location if it does not put the player in danger of being captured.
			5) Otherwise, return an empty vector if nothing was found.
Assistance Received: None
********************************************************************* */
vector<int> Player::FindFourConsecutive(Board a_board, vector<vector<vector<int>>> a_possibleMoves, char a_dangerColor)
{
	//Search for possible 4 in a rows. If there is one, that is the most optimal play.
	for (int i = 0; i < a_possibleMoves.size(); i++) {
		vector<int> emptyIndices = FindEmptyIndices(a_board, a_possibleMoves[i]);

		for (int j = 0; j < emptyIndices.size(); j++) {
			int possibleConsectutive = FindConsecutiveIfPlaced(a_board, a_possibleMoves[i], emptyIndices[j]);
			
			//If it's possible to create four consecutive stones, and it doesn't put the player in danger of being captured, return it.
			if (possibleConsectutive == StrategyConstants::CONSECUTIVE_4_DISTANCE && !InDangerOfCapture(a_board, a_possibleMoves[i][emptyIndices[j]], a_dangerColor))
			{
				return a_possibleMoves[i][emptyIndices[j]];
			}
		}
	}

	return {};
}

