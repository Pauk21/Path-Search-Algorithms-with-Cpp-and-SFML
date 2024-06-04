#include <SFML/Graphics.hpp>
#include "Game/GameScreen.h"
#include "UI/UserInterface.h"

int main() {
	GameScreen gameScreen;
	UserInterface UI;

	// Settings za Windowe
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Clock frameClock;
	float deltaTime = 1.0f / 60.0f;

	// Kreira se glavni Window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "DZ03 by PAUK", sf::Style::Fullscreen, settings);

	while (window.isOpen()) {

		sf::Event evnt;

		while (window.pollEvent(evnt)) {

			// zatvaranje screena
			if (evnt.type == sf::Event::Closed) window.close();
			if (evnt.type == sf::Event::KeyPressed)
				if (evnt.key.code == sf::Keyboard::Escape) window.close();

			// UI kontrole
			if (evnt.type == sf::Event::MouseButtonPressed)
				if (evnt.mouseButton.button == sf::Mouse::Left) {
					UI.ButtonPressed();
					if (UI.buttonStop.IsPressed())
						window.close();
				}
			if (evnt.type == sf::Event::MouseButtonReleased) 
				if (evnt.mouseButton.button == sf::Mouse::Left) UI.ButtonReleased();
		}
		if (frameClock.getElapsedTime().asMilliseconds() >= deltaTime) {
			window.clear();
			UI.Update(window);
			gameScreen.Update(window);
			window.display();
			frameClock.restart();
		}
		
	}
}