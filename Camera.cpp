#include "Camera.h"

const float YSTEP = 30.0f;
const float XSTEP = 30.0f;

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
	this->fieldOfView = 60.0;
}

void Camera::drawRays(float angle)
{
	/*for (auto& ray : this->rayers) {
		ray->setSize(sf::Vector2f(1.0, angle));
		ray->setOrigin(0.5, angle / 2);
		ray->setPosition(ray->getPosition().x, 240);
		this->screeny.draw(*ray);
	}*/
	sf::RectangleShape ray = *this->rayers[359];

}

float Camera::horizontalCollison(float angle, sf::Vector2f position, int map [5][5])
{
	float currentX, currentY;
	bool collide = false;
	float yNearest = position.y - ((int)(position.y / YSTEP) * YSTEP);
	float alpha = angle + 180.0f;
	if (alpha > 180.0f)
		alpha = alpha - 180.0f;
	float xNearest = yNearest / tan(alpha * (3.14f / 180.0f));
	float xStep = YSTEP / tan(alpha * (3.14f / 180.0f));
	currentX = position.x + xNearest;
	currentY = position.y + yNearest;

	std::cout << "CURRENTX: " << std::to_string(currentX) << "\nCURRENTY: " << std::to_string(currentY) << "\n";

	if (map[(int)(currentX / 30) + 1][(int)(currentY / 30)] == 1)
		return (sqrt(pow(position.x - currentX, 2) + pow(position.y - currentY, 2)));
	else
		return 0.0f;

	/*while (!collide) {
		currentX = position.x + xStep;
		currentY = position.y + y

	}*/


}


