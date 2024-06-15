#include "GameScreen.h"


GameScreen::GameScreen()
{
	for (size_t i = 0; i < HEIGHT; i++)
		for (size_t j = 0; j < WIDTH; j++)
			*(gameBoard + i * WIDTH + j) = 1;

	hlColor = 5;
	brushMode = 5;
	isSetStart = false;
	isSetEnd = false;
	isStarted = false;
	foundPath = false;
	prevCell = 1;
	doInstant = false;
	modeSelection = 1;
}

void GameScreen::Update(sf::RenderWindow& window)
{
	DrawBoard(window);
	HLBoard(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		BrushDrawing();
		ResetBoard();
		StartSearch(window);
		SelectMode();	
	}
}

void GameScreen::DrawBoard(sf::RenderWindow& window)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cell.UpdatePosition(POSX + j * CELL_SIZE, POSY + i * CELL_SIZE);
			cell.UpdateState(*(gameBoard + i * WIDTH + j));
			window.draw(cell.GetCell());
		}
	}
}

void GameScreen::HLBoard(sf::RenderWindow& window)
{
	auto mousePosition = sf::Mouse::getPosition();

	if (mousePosition.x >= POSX && mousePosition.x <= 1920 - POSX &&
		mousePosition.y >= POSY && mousePosition.y <= 1020) {
		mousePosition.x = (int)(mousePosition.x - POSX) / 20;
		mousePosition.y = (int)(mousePosition.y - POSY) / 20;
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cell.UpdatePosition(POSX + j * CELL_SIZE, POSY + i * CELL_SIZE);
			if (i == mousePosition.y && j == mousePosition.x) {
				cell.UpdateState(hlColor);
			}
			else {
				cell.UpdateState(5);
			}			
			window.draw(cell.GetCell());
		}
	}
}

void GameScreen::BrushDrawing()
{
	if (UI.buttonDraw.IsPressed()) {
		brushMode = 0;
		hlColor = 0;
	}

	if (UI.buttonErase.IsPressed()) {
		brushMode = 1;
		hlColor = 1;
	}

	if (UI.buttonA.IsPressed()) {
		brushMode = 2;
		hlColor = 2;
	}

	if (UI.buttonB.IsPressed()) {
		brushMode = 3;
		hlColor = 3;
	}

	auto mousePosition = sf::Mouse::getPosition();
	if (mousePosition.x >= POSX && mousePosition.x <= 1920 - POSX &&
		mousePosition.y >= POSY && mousePosition.y <= 1020) {
		
		switch (brushMode)
		{
		case 0:
		case 1:
			mPos = GetMousePos(mousePosition);
			prevCell = *(gameBoard + mPos.first * WIDTH + mPos.second);
			if (prevCell != 2 && prevCell != 3)
				*(gameBoard + mPos.first * WIDTH + mPos.second) = hlColor;
			isStarted = false;
			break;
		case 2:
			mPos = GetMousePos(mousePosition);
			SetStart(mPos);
			brushMode = 5;
			hlColor = 5;
			isStarted = false;
			break;
		case 3:
			mPos = GetMousePos(mousePosition);
			SetEnd(mPos);
			brushMode = 5;
			hlColor = 5;
			isStarted = false;
			break;
		default:
			break;
		}
	}
}

void GameScreen::SetStart(pair<int, int> mPos)
{
	if (isSetStart)
		*(gameBoard + start.first * WIDTH + start.second) = 1;
	this->start = mPos;
	*(gameBoard + start.first * WIDTH + start.second) = 2;
	isSetStart = true;

	std::cout << "START: " << start.first << " | " << start.second << endl;
}

void GameScreen::SetEnd(pair<int, int> mPos)
{
	if (isSetEnd)
		*(gameBoard + end.first * WIDTH + end.second) = 1;
	this->end = mPos;
	*(gameBoard + end.first * WIDTH + end.second) = 3;
	isSetEnd = true;

	std::cout << "END: " << end.first << " | " << end.second << endl;
}

pair<int, int> GameScreen::GetMousePos(sf::Vector2i mousePosition)
{
	mousePosition.x = (int)(mousePosition.x - POSX) / 20;
	mousePosition.y = (int)(mousePosition.y - POSY) / 20;
	return pair<int, int>(mousePosition.y, mousePosition.x);
}

void GameScreen::ResetBoard()
{
	if (UI.buttonReset.IsPressed()) {
		isStarted = false;
		brushMode = 5;
		hlColor = 5;

		for (size_t i = 0; i < HEIGHT; i++)
			for (size_t j = 0; j < WIDTH; j++)
				*(gameBoard + i * WIDTH + j) = 1;
	}
}

void GameScreen::StartSearch(sf::RenderWindow& window)
{	
	if (UI.buttonStart.IsPressed() && isStarted == false) {
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				if (*(gameBoard + i * WIDTH + j) == 4)
					*(gameBoard + i * WIDTH + j) = 1;

		isStarted = true;
		foundPath = AS.aStarSearch(gameBoard, start, end, window, doInstant);
		if (foundPath) {
			DrawPath();
		}
	}

}

void GameScreen::DrawPath()
{
	printf("\nThe Path is ");
	int row = end.first;
	int col = end.second;

	stack<Pair> Path;

	while (!((*(AS.cellDetails + row * WIDTH + col)).parent_i == row
		&& (*(AS.cellDetails + row * WIDTH + col)).parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = (*(AS.cellDetails + row * WIDTH + col)).parent_i;
		int temp_col = (*(AS.cellDetails + row * WIDTH + col)).parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
		if (*(gameBoard + p.first * WIDTH + p.second) != 2 &&
			*(gameBoard + p.first * WIDTH + p.second) != 3) {
			*(gameBoard + p.first * WIDTH + p.second) = 4;
		}		
	}

	std::cout << endl << endl;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << *(gameBoard + i * WIDTH + j);
		}
		std::cout << endl;
	}
	std::cout << endl << endl;
}

void GameScreen::SelectMode() {

	if (UI.LeftArrow.IsPressed()) {
		modeSelection--;
		if (modeSelection < 1) modeSelection = 2;
	}

	if (UI.RightArrow.IsPressed()) {
		modeSelection++;
		if (modeSelection > 2) modeSelection = 1;
	}

	//if (modeSelection == 1)
	//	doInstant = true;
	//else
	//	doInstant = false;

	UI.dsp.ChangeState();
}