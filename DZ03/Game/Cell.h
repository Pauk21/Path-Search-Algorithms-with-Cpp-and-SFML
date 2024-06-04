#pragma once
#include <SFML/Graphics.hpp>

#define CELL_SIZE 20
#define POSX 80
#define POSY 140

class Cell
{
private:
	int state;
	sf::RectangleShape cell;

	
public:
	Cell();

	void UpdateState(int state);
	void UpdatePosition(int x, int y);

	sf::RectangleShape GetCell();
};