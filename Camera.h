#pragma once
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "SFML/Graphics.hpp"
#include <math.h>
#include <vector>
#include "minimap.h"
#include <iostream>


class Camera {

protected:
	sf::RenderWindow& screeny;
	float rayLength, fieldOfView, direction;
	std::vector <sf::RectangleShape*> rayers;

public:

	Camera(sf::RenderWindow& window);

	void drawRays(float angle);

	float horizontalCollison(float angle, sf::Vector2f position, int map[5][5]);


};



#endif
