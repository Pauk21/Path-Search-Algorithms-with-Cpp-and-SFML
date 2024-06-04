#pragma once
#include <SFML/Graphics.hpp>
#include "../UI/Button.h"

class UserInterface
{
private:
	// textures
	sf::Texture textureButtonBase;
	sf::Texture textureButtonBasePressed;
	
	// background
	sf::RectangleShape bg;
	// Bools
	bool pointASet;
	bool pointBSet;
	bool start;
	bool stop;
	bool restart;

public:
	UserInterface();

	// Buttons
	Button buttonA;
	Button buttonB;
	Button buttonStart;
	Button buttonStop;
	Button buttonDraw;
	Button buttonErase;
	Button buttonReset;

	void Load();
	void Update(sf::RenderWindow& window);
	void ButtonPressed();
	void ButtonReleased();
};

