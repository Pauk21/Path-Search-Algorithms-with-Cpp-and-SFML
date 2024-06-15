#include "Display.h"

Display::Display()
{
	Instant.loadFromFile("Images/Instant.png");
	Animated.loadFromFile("Images/Animated.png");

	dsp.setSize(sf::Vector2f(160, 46));
	dsp.setPosition(1000, 30);
	dsp.setTexture(&Instant);

	state = 1;
}

void Display::ChangeState() {

	switch (state)
	{
	case 1:
		state = 2;
		dsp.setTexture(&Animated);
		break;
	case 2:
		state = 1;
		dsp.setTexture(&Instant);
		break;
	default:
		break;
	}
}

sf::RectangleShape Display::getDisplay()
{
	return dsp;
}
