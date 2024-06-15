#pragma once
#include <SFML/Graphics.hpp>
#include "../UI/Button.h"
#include "Display.h"

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
	Button LeftArrow;
	Button RightArrow;

	// Display
	Display dsp;

	void Load();
	void Update(sf::RenderWindow& window);
	void ButtonPressed();
	void ButtonReleased();
};

