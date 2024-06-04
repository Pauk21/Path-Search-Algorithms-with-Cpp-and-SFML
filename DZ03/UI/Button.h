#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;

class Button
{
private:
	int positionX;
	int positionY;
	int sizeX;
	int sizeY;

	sf::RectangleShape image;

	sf::Texture texturePressed;
	sf::Texture textureReleased;

public:
	void SetSize(int sizeX, int sizeY);
	void SetPosition(int positionX, int positionY);
	void SetTexture(string PRESSED, string RELEASED);

	pair<int, int> GetSize();
	pair<int, int> GetPosition();
	sf::RectangleShape GetButton();

	bool IsPressed();
	bool IsReleased();
};

