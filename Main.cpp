// HOW TO SPOON
#include <iostream>
#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <time.h>
#include <Windows.h>


/*bool mouseisMoving(sf::Mouse* Mickey, sf::Vector2i prevMouse, sf::RenderWindow* window) {
	if (Mickey->getPosition(*window).x > prevMouse.x)
		return true;
	else if (Mickey->getPosition(*window).x < prevMouse.x)
		return false;

}*/


int main() {

	sf::RenderWindow mrScreen(sf::VideoMode(640, 480), "Raycast");
	sf::Event e;

	sf::RectangleShape testBlonk;
	testBlonk.setSize(sf::Vector2f(240, 10));
	testBlonk.setOrigin(120, 5);
	testBlonk.rotate(90);
	testBlonk.setPosition(320, 240);
	testBlonk.setFillColor(sf::Color::Green);




	while (mrScreen.isOpen())
	{
		mrScreen.clear();


		while (mrScreen.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				mrScreen.close();
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			testBlonk.setSize(sf::Vector2f(testBlonk.getSize().x - 0.2, testBlonk.getSize().y));
			testBlonk.setPosition(testBlonk.getPosition().x, testBlonk.getPosition().y + 0.1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			testBlonk.setSize(sf::Vector2f(testBlonk.getSize().x + 0.2, testBlonk.getSize().y));
			testBlonk.setPosition(testBlonk.getPosition().x, testBlonk.getPosition().y - 0.1);
		}

		mrScreen.draw(testBlonk);
		mrScreen.display();
	}

	return 0;

}


