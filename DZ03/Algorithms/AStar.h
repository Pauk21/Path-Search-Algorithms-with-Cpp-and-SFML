#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <set>
#include "../Game/Cell.h"

using namespace std;

#define HEIGHT 44
#define WIDTH 88

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

class AStar
{
private:
	struct cell {
		// Row and Column index of its parent
		// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
		int parent_i, parent_j;
		// f = g + h
		double f, g, h;
	};

	bool isValid(int row, int col);
	bool isUnBlocked(int* grid, int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	bool* closedList = new bool[HEIGHT * WIDTH];

	

	Cell cel;

public:
	bool aStarSearch(int* grid, Pair src, Pair dest, sf::RenderWindow& window);
	
	// Declare a 2D array of structure to hold the details
	// of that cell
	cell* cellDetails = new cell[HEIGHT * WIDTH];
};

