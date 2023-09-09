#include "UserInput.h"

//Default Constructor
UserInput::UserInput()
{
}

//Obtains a valid location to place a stone from the user.
//Assistance received: https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
string UserInput::GetPlayLocation(Board a_board)
{
	//Location should be in the format J12 where J is a column on the board (A-S) and 12 is a row on the board (1-19)
	string location;
	bool validLocation = false;

	//There is a handicap for the second turn of the first player. The play must be within three intersections of the center piece.
	bool handicap = a_board.CountPieces('W') == 1 && a_board.CountPieces('B') == 1;

	cout << "Please enter a location on the board that you would like to place a stone (Ex: J12): ";
	cin >> location;
	
	while (!validLocation) 
	{
		//Valid locations can only be 2-3 characters in length. Some examples: A8, B19, S4.
		if (location.length() < 2 || location.length() > 3)
		{
			cout << "Invalid location length, locations must be 2-3 characters in length. Please re-enter a location to place a stone: ";
			cin >> location;
		}
		//Valid columns are from A-S.
		else if (location[0] < 'A' || location[0] > 'S') 
		{
			cout << "Invalid column, columns must from A-S. Please re-enter a location to place a stone: ";
			cin >> location;
		}
		//Valid rows must be numerical and cannot be letters or symbols.
		else if (!isdigit(location[1]) || (location.length() == 3 && !isdigit(location[2])))
		{
			cout << "Invalid row, rows must be numerical from 1-19. Please re-enter a location to place a stone: ";
			cin >> location;
		}
		//Valid rows are from 1-19. The substring after the first character represents the row, and should be converted to an int before comparison.
		else if (stoi(location.substr(1, 2)) < 1 || stoi(location.substr(1, 2)) > 19)
		{
			cout << "Invalid row, rows must be from 1-19. Please re-enter a location to place a stone: ";
			cin >> location;
		}
		//The second turn of the player who went first must place their piece within three intersections of the center piece (J10).
		//Column must be from G-M and location must be from 7-13.
		else if (handicap && (location[0] < 'G' || location[0] > 'M' || stoi(location.substr(1, 2)) < 7 || stoi(location.substr(1, 2)) > 13))
		{
			cout << "The location must be no more than three intersections away from the center piece on this turn. Please re-enter a location to place a stone: ";
			cin >> location;
		}
		//Lastly, a valid location has to be empty on the game board.
		else if (!a_board.IsEmptyLocation(location[0], stoi(location.substr(1, 2))))
		{
			cout << "This location already has a stone placed here. Please re-enter a location to place a stone: ";
			cin >> location;
		}
		else
		{
			//If all test cases are passed, the location is considered to be valid.
			validLocation = true;
		}
	}
	
	//Print out a newline for spacing purposes.
	cout << endl;

	return location;
}

//Gets input from the user regarding whether or not they want to start a new game or load a game.
string UserInput::GetTournamentChoice()
{
	string response;
	bool valid = false;

	cout << "Welcome to Pente!" << endl;
	cout << "Options:" << endl;
	cout << "1. Start a new tournament." << endl;
	cout << "2. Load a tournament from a file." << endl << endl;

	cout << "Enter your choice (1 or 2): ";
	cin >> response;

	while (!valid) 
	{
		if (response != "1" && response != "2")
		{
			cout << "Invalid input. Please enter 1 or 2: ";
			cin >> response;
		}
		else
		{
			valid = true;
		}
	}

	return response;
}

//Gets input form the user regarding the coin toss call to determine the first player.
string UserInput::GetCoinTossCall()
{
	string response;
	bool valid = false;

	cout << "The first player must be determined using a coin toss." << endl << endl;
	
	cout << "Enter 'H' for Heads or 'T' for tails: ";
	cin >> response;
	
	while (!valid)
	{
		if (response != "H" && response != "T")
		{
			cout << "Invalid input. Please enter H or T: ";
			cin >> response;
		}
		else
		{
			valid = true;
		}
	}

	return response;
}

string UserInput::GetHumanDecision()
{
	string response;
	bool valid = false;

	cout << "Options:" << endl;
	cout << "1. Place a tile." << endl;
	cout << "2. Ask for help." << endl;
	cout << "3. Save and exit game." << endl << endl;

	cout << "Enter your choice (1-3): ";
	cin >> response;

	while (!valid)
	{
		if (response != "1" && response != "2" && response != "3")
		{
			cout << "Invalid input. Please enter 1, 2, or 3: ";
			cin >> response;
		}
		else
		{
			valid = true;
		}
	}

	cout << endl;

	return response;
}

string UserInput::GetSaveDecision()
{
	string response;
	bool valid = false;

	cout << "Would you like to save and exit the game or continue playing? Enter \"Y\" or \"N\": ";
	cin >> response;

	while (!valid)
	{
		if (response != "Y" && response != "N")
		{
			cout << "Invalid input. Please enter Y or N: ";
			cin >> response;
		}
		else
		{
			valid = true;
		}
	}

	cout << endl;

	return response;
}
