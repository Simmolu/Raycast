#pragma once
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "SFML/Graphics.hpp"
#include <math.h>
#include <vector>
#include "minimap.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>


class Camera {

protected:
	sf::RenderWindow& screeny;
	float rayLength, fieldOfView, direction;
	std::vector <std::unique_ptr<sf::RectangleShape>> rayers;

public:

	Camera(sf::RenderWindow& window);

	void drawRays(float angle, sf::Vector2f position, const int map [5][5]);

	float horizontalCollison(float angle, sf::Vector2f position, const int map[5][5]);

	void drawFloor();

};



#endif
