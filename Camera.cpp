#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
	: screeny(window)
{
	for (int i = 0; i < 720; i++) {
		sf::RectangleShape* rayPtr = new sf::RectangleShape(sf::Vector2f(1, 20));
		rayPtr->setOrigin(0.5, 10);
		rayPtr->setPosition((float)i, 240);
		rayPtr->setFillColor(sf::Color::Green);
		this->rayers.push_back(rayPtr);
	}
}

void Camera::drawRays(float angle)
{
	for (auto& ray : this->rayers) {
		ray->setSize(sf::Vector2f(1.0, angle));
		ray->setOrigin(0.5, angle / 2);
		ray->setPosition(ray->getPosition().x, 240);
		this->screeny.draw(*ray);
	}
}
