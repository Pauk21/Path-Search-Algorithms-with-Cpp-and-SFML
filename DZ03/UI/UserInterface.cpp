#include "UserInterface.h"


UserInterface::UserInterface()
{
	Load();
	bg.setSize(sf::Vector2f(1920.0f, 1080.0f));
	bg.setFillColor(sf::Color{ 224, 221, 207, 200 });
}

void UserInterface::Update(sf::RenderWindow& window)
{
	window.draw(bg);
	window.draw(buttonA.GetButton());
	window.draw(buttonB.GetButton());
	window.draw(buttonStart.GetButton());
	window.draw(buttonStop.GetButton());
	window.draw(buttonDraw.GetButton());
	window.draw(buttonErase.GetButton());
	window.draw(buttonReset.GetButton());
}

void UserInterface::ButtonPressed()
{
	buttonA.IsPressed();
	buttonB.IsPressed();
	buttonStart.IsPressed();
	buttonStop.IsPressed();
	buttonDraw.IsPressed();
	buttonErase.IsPressed();
	buttonReset.IsPressed();
}

void UserInterface::ButtonReleased()
{
	buttonA.IsReleased();
	buttonB.IsReleased();
	buttonStart.IsReleased();
	buttonStop.IsReleased();
	buttonDraw.IsReleased();
	buttonErase.IsReleased();
	buttonReset.IsReleased();
}

void UserInterface::Load()
{
	// BUTTON A
	buttonA.SetSize(128, 64);
	buttonA.SetPosition(80, 30);
	buttonA.SetTexture("Images/ButtonAPressed.png", "Images/ButtonAReleased.png");

	// BUTTON B
	buttonB.SetSize(128, 64);
	buttonB.SetPosition(224, 30);
	buttonB.SetTexture("Images/ButtonBPressed.png", "Images/ButtonBReleased.png");

	// BUTTON DRAW
	buttonDraw.SetSize(128, 64);
	buttonDraw.SetPosition(368, 30);
	buttonDraw.SetTexture("Images/ButtonDRAWPressed.png", "Images/ButtonDRAWReleased.png");

	// BUTTON ERASE
	buttonErase.SetSize(128, 64);
	buttonErase.SetPosition(512, 30);
	buttonErase.SetTexture("Images/ButtonERASEPressed.png", "Images/ButtonERASEReleased.png");

	// BUTTON RESTART
	buttonReset.SetSize(128, 64);
	buttonReset.SetPosition(656, 30);
	buttonReset.SetTexture("Images/ButtonRESETPressed.png", "Images/ButtonRESETReleased.png");

	// BUTTON START
	buttonStart.SetSize(128, 64);
	buttonStart.SetPosition(1568, 30);
	buttonStart.SetTexture("Images/ButtonSTARTPressed.png", "Images/ButtonSTARTReleased.png");

	// BUTTON STOP
	buttonStop.SetSize(128, 64);
	buttonStop.SetPosition(1712, 30);
	buttonStop.SetTexture("Images/ButtonSTOPPressed.png", "Images/ButtonSTOPReleased.png");

	
}