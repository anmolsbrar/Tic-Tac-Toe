#include <iostream>
#include <string>

#define GRID_SIZE 3

using std::cout;
using std::endl;
using std::cin;

typedef char Grid[GRID_SIZE][GRID_SIZE];

enum Player { PL_X = 0, PL_O = 1 };

void populateGrid(Grid);
void printGrid(Grid);
bool selectCell(Grid, int, Player);
Player checkWinner(Grid, bool&);
Player playerNumber();
void togglePlayer(bool&, Player&);
void playGame(Player, bool, Grid);


int main()
{
	Player user, winner, currPlayer;
	Grid grid;
	bool isDone, isPlayer;
	int cell, turnNum;
	char input;
	do
	{
		turnNum = 0;
		isDone = false;
		isPlayer = false;
		input = '\0';
		currPlayer = PL_X;
		
		cout << "Welcome to Tic-Tac-Toe\n";
		cout << "Enter P to play, Enter E to exit\n";
		cin >> input;
		populateGrid(grid);
		user = playerNumber();
		printGrid(grid);
		while (turnNum < 9 && !isDone)
		{
			if (user == PL_X && turnNum == 0)
				isPlayer = true;

			playGame(currPlayer, isPlayer, grid);
			
			system("CLS");
			printGrid(grid);

			winner = checkWinner(grid, isDone);
			togglePlayer(isPlayer, currPlayer);
			turnNum++;
		}

		if (winner == user)
			cout << "You win\n";
		else
			cout << "You lose\n";

	} while (input != 'E' || input != 'e');
	return 0;
}

void populateGrid(Grid g)
{
	int number = 1;
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			g[i][j] = std::to_string(number).c_str()[0];
			number++;
		}
	}
}

void printGrid(Grid g)
{
	cout << " " << g[0][0] << " | " << g[0][1] << " | " << g[0][2] << endl;
	cout << "---|---|---\n";
	cout << " " << g[1][0] << " | " << g[1][1] << " | " << g[1][2] << endl;
	cout << "---|---|---\n";
	cout << " " << g[2][0] << " | " << g[2][1] << " | " << g[2][2] << endl;
}

bool selectCell(Grid g, int c, Player p)
{
	char cellNum = std::to_string(c).c_str()[0];
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (g[i][j] == cellNum)
			{
				if(p == PL_X)
					g[i][j] = 'X';
				else if(p == PL_O)
					g[i][j] = 'O';
				return true;
			}
		}
	}
	return false;
}

Player checkWinner(Grid g, bool& terminate)
{
	auto check = [&terminate](int num)->Player {
		if (num == 3)
		{
			terminate = true;
			return PL_X;
		}
		else if (num == -3)
		{
			terminate = true;
			return PL_O;
		}
		else
			terminate = false;
	};

	int count = 0;
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
			count += (g[i][j] == 'X') ? 1 : (g[i][j] == 'O') ? -1 : 0;
		if (count == 3 || count == -3)
			return check(count);

		count = 0;
	}

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
			count += (g[j][i] == 'X') ? 1 : (g[j][i] == 'O') ? -1 : 0;
		if (count == 3 || count == -3)
			return check(count);
		count = 0;
	}

	
	for (int i = 0; i < GRID_SIZE; i++)
		count += (g[i][i] == 'X') ? 1 : (g[i][i] == 'O') ? -1 : 0;
	if (count == 3 || count == -3)
		return check(count);

	count = 0;
	for (int i = 0; i < GRID_SIZE; i++)
		count += (g[i][2 - i] == 'X') ? 1 : (g[i][2 - i] == 'O') ? -1 : 0;
	if (count == 3 || count == -3)
		return check(count);

}

Player playerNumber()
{
	char input;
	cout << "Select your symbol\n";
	cout << "X goes first and O goes after.";
	cin >> input;
	if (input == 'x' || input == 'X')
		return PL_X;
	else
		return PL_O;
}

void togglePlayer(bool &isPlayer, Player &player)
{
	if (isPlayer)
		isPlayer = false;
	else
		isPlayer = true;

	if (player == PL_X)
		player = PL_O;
	else if (player == PL_O)
		player = PL_X;
}

void playGame(Player p, bool isPlayer, Grid g)
{
	int cell;
	if (isPlayer)
	{
		cin >> cell;
		if (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		while (!selectCell(g, cell, p))
		{
			cout << "Please enter a valid cell number\n";
			cin >> cell;
		}
	}
	else
	{
		while (true)
		{
			int cellNum = rand() % 9 + 1;
			if (selectCell(g, cellNum, p))
				break;
		}
	}
}
