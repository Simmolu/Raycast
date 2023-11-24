#pragma once


#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include <SFML/Graphics.hpp>



class Minimap {

protected:
	sf::RenderWindow& mrScreen;
	sf::RectangleShape viewWindow;
	sf::RectangleShape playerRay;
	sf::CircleShape viewRay;

public:
	Minimap(sf::RenderWindow& Screen, int map[5][5]);

	void rotateRays(float degrees);

	float getAngle();

	void drawCam();

};




#endif // !MINIMAP_H_INCLUDED
