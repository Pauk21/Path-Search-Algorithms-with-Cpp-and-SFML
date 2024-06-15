#pragma once
#include <SFML/Graphics.hpp>
#include "../UI/UserInterface.h"
#include "../Game/Cell.h"
#include "../Algorithms/AStar.h"
#include <iostream>

class GameScreen
{
private:
	UserInterface UI;
	AStar AS;

	bool isStarted;
	bool foundPath;

	// 0 - blocked cell
	// 1 - free cell
	// 2 - start cell
	// 3 - end cell
	// 4 - path cell
	// 5 - transparent cell
	int* gameBoard = new int[HEIGHT * WIDTH];
	int hlColor;

	Cell cell;

	
	// 0 - draw blocked cell
	// 1 - draw free cell
	// 2 - set start cell
	// 3 - set end cell
	// 5 - transparent cell
	int brushMode;

	int prevCell;

	void DrawBoard(sf::RenderWindow& window);
	void HLBoard(sf::RenderWindow& window);
	void BrushDrawing();
	void ResetBoard();
	void StartSearch(sf::RenderWindow& window);
	void DrawPath();

	pair<int, int> start;
	bool isSetStart;
	void SetStart(pair<int, int> mPos);

	pair<int, int> end;
	bool isSetEnd;
	void SetEnd(pair<int, int> mPos);
	
	pair<int, int> GetMousePos(sf::Vector2i mousePosition);
	pair<int, int> mPos;
public:
	GameScreen();
	void Update(sf::RenderWindow& window);

	
};

