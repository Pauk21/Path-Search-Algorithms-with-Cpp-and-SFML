#include "AStar.h"

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool AStar::isValid(int row, int col)
{
	// Returns true if row number and column number 
	// is in range
	return (row >= 0) && (row < HEIGHT) && (col >= 0)
		&& (col < WIDTH);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool AStar::isUnBlocked(int* grid, int row, int col)
{
	// Returns true if the cell is not blocked else false
	switch (*(grid + row * WIDTH + col)) {
	case 1:
	case 2:
	case 3:
		return true;
		break;
	case 0:
		return false;
	}
}

// A Utility Function to check whether destination cell has
// been reached or not
bool AStar::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double AStar::calculateHValue(int row, int col, Pair dest)
{
	// Return using the distance formula
	return ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
bool AStar::aStarSearch(int* grid, Pair src, Pair dest, sf::RenderWindow& window)
{
	float deltaTime = 500;
	sf::Clock frClock;

	// If the source is out of range
	if (isValid(src.first, src.second) == false) {
		printf("Source is invalid\n");
		return false;
	}

	// If the destination is out of range
	if (isValid(dest.first, dest.second) == false) {
		printf("Destination is invalid\n");
		return false;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
		== false) {
		printf("Source or the destination is blocked\n");
		return false;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest)
		== true) {
		printf("We are already at the destination\n");
		return true;;
	}

	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			*(closedList + i * WIDTH + j) = false;	

	int i, j;

	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			(*(cellDetails + i * WIDTH + j)).f = FLT_MAX;
			(*(cellDetails + i * WIDTH + j)).g = FLT_MAX;
			(*(cellDetails + i * WIDTH + j)).h = FLT_MAX;
			(*(cellDetails + i * WIDTH + j)).parent_i = -1;
			(*(cellDetails + i * WIDTH + j)).parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	(*(cellDetails + i * WIDTH + j)).f = 0.0;
	(*(cellDetails + i * WIDTH + j)).g = 0.0;
	(*(cellDetails + i * WIDTH + j)).h = 0.0;
	(*(cellDetails + i * WIDTH + j)).parent_i = i;
	(*(cellDetails + i * WIDTH + j)).parent_j = j;

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of pair of
	pair.*/
	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		*(closedList + i * WIDTH + j) = true;

			/*
			Generating all the 8 successor of this cell

				N.W N N.E
				\ | /
					\ | /
				W----Cell----E
					/ | \
					/ | \
				S.W S S.E

			Cell-->Popped Cell (i, j)
			N --> North	 (i-1, j)
			S --> South	 (i+1, j)
			E --> East	 (i, j+1)
			W --> West		 (i, j-1)
			N.E--> North-East (i-1, j+1)
			N.W--> North-West (i-1, j-1)
			S.E--> South-East (i+1, j+1)
			S.W--> South-West (i+1, j-1)*/

			// To store the 'g', 'h' and 'f' of the 8 successors
			double gNew, hNew, fNew;

			//----------- 1st Successor (North) ------------

			// Only process this cell if this is a valid one
			if (isValid(i - 1, j) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i - 1, j, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + (i - 1) * WIDTH + j)).parent_i = i;
					(*(cellDetails + (i - 1) * WIDTH + j)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;;
				}
				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + (i - 1) * WIDTH + j) == false
					&& isUnBlocked(grid, i - 1, j)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.0;
					hNew = calculateHValue(i - 1, j, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + (i - 1) * WIDTH + j)).f == FLT_MAX
						|| (*(cellDetails + (i - 1) * WIDTH + j)).f > fNew) {
						openList.insert(make_pair(
							fNew, make_pair(i - 1, j)));

						// Update the details of this cell
						(*(cellDetails + (i - 1) * WIDTH + j)).f = fNew;
						(*(cellDetails + (i - 1) * WIDTH + j)).g = gNew;
						(*(cellDetails + (i - 1) * WIDTH + j)).h = hNew;
						(*(cellDetails + (i - 1) * WIDTH + j)).parent_i = i;
						(*(cellDetails + (i - 1) * WIDTH + j)).parent_j = j;
					}
				}
			}

			//----------- 2nd Successor (South) ------------

			// Only process this cell if this is a valid one
			if (isValid(i + 1, j) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i + 1, j, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + (i + 1) * WIDTH + j)).parent_i = i;
					(*(cellDetails + (i + 1) * WIDTH + j)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;
				}
				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + (i + 1) * WIDTH + j) == false
					&& isUnBlocked(grid, i + 1, j)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.0;
					hNew = calculateHValue(i + 1, j, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + (i + 1) * WIDTH + j)).f == FLT_MAX
						|| (*(cellDetails + (i + 1) * WIDTH + j)).f > fNew) {
						openList.insert(make_pair(
							fNew, make_pair(i + 1, j)));
						// Update the details of this cell
						(*(cellDetails + (i + 1) * WIDTH + j)).f = fNew;
						(*(cellDetails + (i + 1) * WIDTH + j)).g = gNew;
						(*(cellDetails + (i + 1) * WIDTH + j)).h = hNew;
						(*(cellDetails + (i + 1) * WIDTH + j)).parent_i = i;
						(*(cellDetails + (i + 1) * WIDTH + j)).parent_j = j;
					}
				}
			}

			//----------- 3rd Successor (East) ------------

			// Only process this cell if this is a valid one
			if (isValid(i, j + 1) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i, j + 1, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + i * WIDTH + j + 1)).parent_i = i;
					(*(cellDetails + i * WIDTH + j + 1)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;
				}

				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + i * WIDTH + j + 1) == false
					&& isUnBlocked(grid, i, j + 1)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.0;
					hNew = calculateHValue(i, j + 1, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + i * WIDTH + j + 1)).f == FLT_MAX
						|| (*(cellDetails + i * WIDTH + j + 1)).f > fNew) {
						openList.insert(make_pair(fNew, make_pair(i, j + 1)));

						// Update the details of this cell
						(*(cellDetails + i * WIDTH + j + 1)).f = fNew;
						(*(cellDetails + i * WIDTH + j + 1)).g = gNew;
						(*(cellDetails + i * WIDTH + j + 1)).h = hNew;
						(*(cellDetails + i * WIDTH + j + 1)).parent_i = i;
						(*(cellDetails + i * WIDTH + j + 1)).parent_j = j;
					}
				}
			}

			//----------- 4th Successor (West) ------------

			// Only process this cell if this is a valid one
			if (isValid(i, j - 1) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i, j - 1, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + i * WIDTH + j - 1)).parent_i = i;
					(*(cellDetails + i * WIDTH + j - 1)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;
				}

				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + i * WIDTH + j - 1) == false
					&& isUnBlocked(grid, i, j - 1)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.0;
					hNew = calculateHValue(i, j - 1, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + i * WIDTH + j - 1)).f == FLT_MAX
						|| (*(cellDetails + i * WIDTH + j - 1)).f > fNew) {
						openList.insert(make_pair(fNew, make_pair(i, j - 1)));

						// Update the details of this cell
						(*(cellDetails + i * WIDTH + j - 1)).f = fNew;
						(*(cellDetails + i * WIDTH + j - 1)).g = gNew;
						(*(cellDetails + i * WIDTH + j - 1)).h = hNew;
						(*(cellDetails + i * WIDTH + j - 1)).parent_i = i;
						(*(cellDetails + i * WIDTH + j - 1)).parent_j = j;
					}
				}
			}

			//----------- 5th Successor (North-East)
			//------------

			// Only process this cell if this is a valid one
			if (isValid(i - 1, j + 1) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i - 1, j + 1, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + (i - 1) * WIDTH + j + 1)).parent_i = i;
					(*(cellDetails + (i - 1) * WIDTH + j + 1)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;
				}

				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + (i - 1) * WIDTH + j + 1) == false
					&& isUnBlocked(grid, i - 1, j + 1)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.414;
					hNew = calculateHValue(i - 1, j + 1, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + (i - 1) * WIDTH + j + 1)).f == FLT_MAX
						|| (*(cellDetails + (i - 1) * WIDTH + j + 1)).f > fNew) {
						openList.insert(make_pair(fNew, make_pair(i - 1, j + 1)));

						// Update the details of this cell
						(*(cellDetails + (i - 1) * WIDTH + j + 1)).f = fNew;
						(*(cellDetails + (i - 1) * WIDTH + j + 1)).g = gNew;
						(*(cellDetails + (i - 1) * WIDTH + j + 1)).h = hNew;
						(*(cellDetails + (i - 1) * WIDTH + j + 1)).parent_i = i;
						(*(cellDetails + (i - 1) * WIDTH + j + 1)).parent_j = j;
					}
				}
			}

			//----------- 6th Successor (North-West)
			//------------

			// Only process this cell if this is a valid one
			if (isValid(i - 1, j - 1) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i - 1, j - 1, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + (i - 1) * WIDTH + j - 1)).parent_i = i;
					(*(cellDetails + (i - 1) * WIDTH + j - 1)).parent_j = j;
					printf("The destination cell is found\n");
					//tracePath(cellDetails, dest);
					foundDest = true;
					return true;
				}

				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + (i - 1) * WIDTH + j - 1) == false
					&& isUnBlocked(grid, i - 1, j - 1)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.414;
					hNew = calculateHValue(i - 1, j - 1, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + (i - 1) * WIDTH + j - 1)).f == FLT_MAX
						|| (*(cellDetails + (i - 1) * WIDTH + j - 1)).f > fNew) {
						openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
						// Update the details of this cell
						(*(cellDetails + (i - 1) * WIDTH + j - 1)).f = fNew;
						(*(cellDetails + (i - 1) * WIDTH + j - 1)).g = gNew;
						(*(cellDetails + (i - 1) * WIDTH + j - 1)).h = hNew;
						(*(cellDetails + (i - 1) * WIDTH + j - 1)).parent_i = i;
						(*(cellDetails + (i - 1) * WIDTH + j - 1)).parent_j = j;
					}
				}
			}

			//----------- 7th Successor (South-East)
			//------------

			// Only process this cell if this is a valid one
			if (isValid(i + 1, j + 1) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i + 1, j + 1, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + (i + 1) * WIDTH + j + 1)).parent_i = i;
					(*(cellDetails + (i + 1) * WIDTH + j + 1)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;
				}

				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + (i + 1) * WIDTH + j + 1) == false
					&& isUnBlocked(grid, i + 1, j + 1)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.414;
					hNew = calculateHValue(i + 1, j + 1, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + (i + 1) * WIDTH + j + 1)).f == FLT_MAX
						|| (*(cellDetails + (i + 1) * WIDTH + j + 1)).f > fNew) {
						openList.insert(make_pair(fNew, make_pair(i + 1, j + 1)));

						// Update the details of this cell
						(*(cellDetails + (i + 1) * WIDTH + j + 1)).f = fNew;
						(*(cellDetails + (i + 1) * WIDTH + j + 1)).g = gNew;
						(*(cellDetails + (i + 1) * WIDTH + j + 1)).h = hNew;
						(*(cellDetails + (i + 1) * WIDTH + j + 1)).parent_i = i;
						(*(cellDetails + (i + 1) * WIDTH + j + 1)).parent_j = j;
					}
				}
			}

			//----------- 8th Successor (South-West)
			//------------

			// Only process this cell if this is a valid one
			if (isValid(i + 1, j - 1) == true) {
				// If the destination cell is the same as the
				// current successor
				if (isDestination(i + 1, j - 1, dest) == true) {
					// Set the Parent of the destination cell
					(*(cellDetails + (i + 1) * WIDTH + j - 1)).parent_i = i;
					(*(cellDetails + (i + 1) * WIDTH + j - 1)).parent_j = j;
					printf("The destination cell is found\n");
					foundDest = true;
					return true;
				}

				// If the successor is already on the closed
				// list or if it is blocked, then ignore it.
				// Else do the following
				else if (*(closedList + (i + 1) * WIDTH + j - 1) == false
					&& isUnBlocked(grid, i + 1, j - 1)
					== true) {
					gNew = (*(cellDetails + i * WIDTH + j)).g + 1.414;
					hNew = calculateHValue(i + 1, j - 1, dest);
					fNew = gNew + hNew;

					// If it isn’t on the open list, add it to
					// the open list. Make the current square
					// the parent of this square. Record the
					// f, g, and h costs of the square cell
					//			 OR
					// If it is on the open list already, check
					// to see if this path to that square is
					// better, using 'f' cost as the measure.
					if ((*(cellDetails + (i + 1) * WIDTH + j - 1)).f == FLT_MAX
						|| (*(cellDetails + (i + 1) * WIDTH + j - 1)).f > fNew) {
						openList.insert(make_pair(fNew, make_pair(i + 1, j - 1)));

						// Update the details of this cell
						(*(cellDetails + (i + 1) * WIDTH + j - 1)).f = fNew;
						(*(cellDetails + (i + 1) * WIDTH + j - 1)).g = gNew;
						(*(cellDetails + (i + 1) * WIDTH + j - 1)).h = hNew;
						(*(cellDetails + (i + 1) * WIDTH + j - 1)).parent_i = i;
						(*(cellDetails + (i + 1) * WIDTH + j - 1)).parent_j = j;
					}
				}
			}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destination cell. This may happen when the
	// there is no way to destination cell (due to
	// blockages)
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return false;
}

