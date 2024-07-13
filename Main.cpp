#include <iostream>
#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include "minimap.h"
#include "Application.h"




int main() {

	

	sf::RenderWindow mrScreen(sf::VideoMode(720, 480), "Raycast");

	Application app(mrScreen);

	while (app.appRun())
	{
		
	}

	return 0;
}


