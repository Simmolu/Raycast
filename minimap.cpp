#include "minimap.h"

Minimap::Minimap(sf::RenderWindow& window, int map[5][5]) 
	: mrScreen(window)

{
	this->viewWindow = sf::RectangleShape(sf::Vector2f(150, 150));
	this->viewWindow.setFillColor(sf::Color::Black);
	this->viewWindow.setOutlineColor(sf::Color::White);
	this->viewWindow.setOutlineThickness(1.0);
	this->viewWindow.setPosition(1, 1);

	this->playerRay = sf::RectangleShape(sf::Vector2f(1, 75));
	this->playerRay.setFillColor(sf::Color::White);
	this->playerRay.setOrigin(0.5, 0);
	this->playerRay.setPosition(76, 76);

	this->viewRay = sf::CircleShape(50, 3);
	this->viewRay.setFillColor(sf::Color(255, 255, 255, 1));
	this->viewRay.setOutlineColor(sf::Color::White);
	this->viewRay.setOutlineThickness(1.0);
	this->viewRay.setOrigin(50, 0);
	this->viewRay.setPosition(76, 76);
}


void Minimap::rotateRays(float degrees) {
	playerRay.rotate(degrees);
	viewRay.rotate(degrees);
}

float Minimap::getAngle() {
	return this->playerRay.getRotation();
}

void Minimap::drawCam()
{
	mrScreen.draw(this->playerRay);
	mrScreen.draw(this->viewWindow);
	mrScreen.draw(this->viewRay);
}
