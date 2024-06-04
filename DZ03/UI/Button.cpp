#include "Button.h"

void Button::SetSize(int sizeX, int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	image.setSize(sf::Vector2f(sizeX, sizeY));
}

void Button::SetPosition(int positionX, int positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
	image.setPosition(sf::Vector2f(positionX, positionY));
}

void Button::SetTexture(string PRESSED, string RELEASED)
{
	texturePressed.loadFromFile(PRESSED);
	textureReleased.loadFromFile(RELEASED);

	image.setTexture(&textureReleased);
}

pair<int, int> Button::GetSize()
{
	return pair<int, int>(sizeX, sizeY);
}

pair<int, int> Button::GetPosition()
{
	return pair<int, int>(positionX, positionY);
}

sf::RectangleShape Button::GetButton()
{
	return image;
}

bool Button::IsPressed()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition();

	if (mousePosition.x > positionX && 
		mousePosition.x < positionX + sizeX &&
		mousePosition.y > positionY && 
		mousePosition.y < positionY + sizeY) {
		image.setTexture(&texturePressed);
		return true;
	}

	return false;
}

bool Button::IsReleased()
{
	image.setTexture(&textureReleased);
	return true;
}
