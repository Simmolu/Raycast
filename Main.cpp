#include <iostream>
#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include "minimap.h"


/*bool mouseisMoving(sf::Mouse* Mickey, sf::Vector2i prevMouse, sf::RenderWindow* window) {
	if (Mickey->getPosition(*window).x > prevMouse.x)
		return true;
	else if (Mickey->getPosition(*window).x < prevMouse.x)
		return false;

}*/


int main() {


	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Font read error.";
		return 0;
	}


	sf::RenderWindow mrScreen(sf::VideoMode(720, 480), "Raycast");
	sf::Event e;

	sf::Text pos;
	pos.setCharacterSize(20);
	pos.setFillColor(sf::Color::White);
	pos.setFont(font);
	pos.setPosition(660, 440);

	int worldMap[5][5] = {
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1}
	};


	Minimap mappy(mrScreen, worldMap);


	std::vector <sf::RectangleShape*> rays;
	for (int i = 0; i < 720; i++) {
		sf::RectangleShape* rayPtr = new sf::RectangleShape(sf::Vector2f(1, 20));
		rayPtr->setOrigin(0.5, 10);
		rayPtr->setPosition((float)i, 240);
		rayPtr->setFillColor(sf::Color::Green);
		rays.push_back(rayPtr);
	}



	sf::Mouse mickey;
	int x, y;
	float currAngle;

	while (mrScreen.isOpen())
	{
		mrScreen.clear();
		

		sf::Vector2i mousePos = mickey.getPosition(mrScreen);
		x = mappy.getPos().x;
		y = mappy.getPos().y;


		pos.setString("X: " + std::to_string(x) + "\nY: " + std::to_string(y));


		while (mrScreen.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					mrScreen.close();
			
			}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			mappy.rotateRays(-0.1);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			mappy.rotateRays(0.1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			mappy.moveCam();
		}

		for (auto& ray : rays) {
			ray->setSize(sf::Vector2f(1.0, mappy.getAngle()));
			ray->setOrigin(0.5, mappy.getAngle() / 2);
			ray->setPosition(ray->getPosition().x, 240);
			mrScreen.draw(*ray);
		}


		mappy.drawCam();

		mrScreen.draw(pos);
		

		mrScreen.display();
	}

	return 0;
}


