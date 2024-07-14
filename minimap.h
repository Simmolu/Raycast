#pragma once


#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>



class Minimap {

protected:
	sf::RenderWindow& mrScreen;
	sf::RectangleShape viewWindow;
	sf::RectangleShape playerRay;
	sf::CircleShape viewRay;
	std::vector <sf::RectangleShape*> walls;

	float moveSpeed;

public:
	Minimap(sf::RenderWindow& Screen, const int map[5][5]);

	void rotateRays(float degrees);

	float getAngle();

	void drawCam();

	void moveCam(bool back, const int map[5][5]);

	sf::Vector2f getPos();

};




#endif // !MINIMAP_H_INCLUDED
