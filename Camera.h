#pragma once
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "SFML/Graphics.hpp"
#include <math.h>
#include <vector>
#include "minimap.h"


class Camera {

protected:
	sf::RenderWindow& screeny;
	float rayLength;
	std::vector <sf::RectangleShape*> rayers;

public:

	Camera(sf::RenderWindow& window);

	void drawRays(float angle);


};



#endif
