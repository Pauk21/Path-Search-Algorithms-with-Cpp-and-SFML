#include "Cell.h"

Cell::Cell()
{
	state = 0;
	cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cell.setPosition(POSX, POSY);
	cell.setFillColor(sf::Color::White);
	cell.setOutlineColor(sf::Color{ 45,35,46,200 });
	cell.setOutlineThickness(2.0f);
}

void Cell::UpdateState(int state)
{
	this->state = state;
}

void Cell::UpdatePosition(int x, int y)
{
	cell.setPosition(x, y);
}

sf::RectangleShape Cell::GetCell()
{
	switch (state)
	{
	case 0:
		cell.setFillColor(sf::Color::Black);
		break;
	case 1:
		cell.setFillColor(sf::Color::White);
		break;
	case 2:
		cell.setFillColor(sf::Color{150, 75, 200, 200});
		break;
	case 3:
		cell.setFillColor(sf::Color{206, 129, 71, 250});
		break;
	case 4:
		cell.setFillColor(sf::Color::Red);
		break;
	case 5:
		cell.setFillColor(sf::Color::Transparent);
		break;
	case 6:
		cell.setFillColor(sf::Color::Cyan);
		break;
	}

	return cell;
}
