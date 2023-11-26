#include <iostream>
#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include "minimap.h"
#include "Application.h"


/*bool mouseisMoving(sf::Mouse* Mickey, sf::Vector2i prevMouse, sf::RenderWindow* window) {
	if (Mickey->getPosition(*window).x > prevMouse.x)
		return true;
	else if (Mickey->getPosition(*window).x < prevMouse.x)
		return false;

}*/


int main() {

	int worldMap[5][5] = {
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1}
	};

	sf::RenderWindow mrScreen(sf::VideoMode(720, 480), "Raycast");

	Application app(mrScreen, worldMap);

	while (app.appRun(worldMap))
	{
		
	}

	return 0;
}


