#pragma once
#include <SFML/Graphics.hpp>

class Display
{
private:
	sf::Texture Instant;
	sf::Texture Animated;
	sf::RectangleShape dsp;

	// 1 instant
	// 2 animated
	int state;
public:
	Display();
	void ChangeState();
	sf::RectangleShape getDisplay();
};