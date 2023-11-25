#pragma once
#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "SFML/Graphics.hpp"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include "minimap.h"
#include "Camera.h"

class Application
{
protected:
	sf::Font fonty;
	sf::RenderWindow& mrScreen;
	sf::Event ev;
	sf::Text position;
	Minimap mapper;
	Camera cam;
	float x, y;
	


public:

	Application(sf::RenderWindow& screen, int map[5][5]);

	void drawEverything();

	bool appRun();

};





#endif // !APPLICATION_H_INCLUDED



