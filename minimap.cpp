#include "minimap.h"
#include <iostream>


Minimap::Minimap(sf::RenderWindow& window, const int map[5][5]) 
	: mrScreen(window)

{

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (map[i][j] == 1) {
				sf::RectangleShape* wallPtr = new sf::RectangleShape(sf::Vector2f(30.0, 30.0));
				wallPtr->setOrigin(15.0, 15.0);
				wallPtr->setFillColor(sf::Color::Green);
				wallPtr->setOutlineColor(sf::Color::White);
				wallPtr->setOutlineThickness(1.0);
				wallPtr->setPosition(15 + (j * 30), 15 + (i * 30));
				this->walls.push_back(wallPtr);
			}
			else {
				sf::RectangleShape* wallPtr = new sf::RectangleShape(sf::Vector2f(30.0, 30.0));
				wallPtr->setOrigin(15.0, 15.0);
				wallPtr->setFillColor(sf::Color::Black);
				wallPtr->setOutlineColor(sf::Color::White);
				wallPtr->setOutlineThickness(1.0);
				wallPtr->setPosition(15 + (j * 30), 15 + (i * 30));
				this->walls.push_back(wallPtr);
			}
		}
	}


	this->viewWindow = sf::RectangleShape(sf::Vector2f(150, 150));
	this->viewWindow.setFillColor(sf::Color::Black);
	this->viewWindow.setOutlineColor(sf::Color::White);
	this->viewWindow.setOutlineThickness(1.0);
	this->viewWindow.setPosition(0, 0);

	this->playerRay = sf::RectangleShape(sf::Vector2f(1, 50));
	this->playerRay.setFillColor(sf::Color::White);
	this->playerRay.setOrigin(0.5, 0);
	this->playerRay.setPosition(75, 75);
	//this->playerRay.setRotation(110);

	this->viewRay = sf::CircleShape(50, 3);
	this->viewRay.setFillColor(sf::Color(255, 255, 255, 1));
	this->viewRay.setOutlineColor(sf::Color::White);
	this->viewRay.setOutlineThickness(1.0);
	this->viewRay.setOrigin(50, 0);
	this->viewRay.setPosition(76, 76);

	std::cout << this->walls.size() << " Walls should be present\n";
	std::cout << "Feed the blacks\n";
	this->moveSpeed = 0.05;
}


void Minimap::rotateRays(float degrees) {
	playerRay.rotate(degrees);
	viewRay.rotate(degrees);
}

float Minimap::getAngle() {
	float angle = this->playerRay.getRotation() + 90.0f;
	if (angle > 360.0f)
		angle = angle - 360.0f;

	angle = static_cast<int>(angle * 10) / 10.0f;

	return angle;
}

void Minimap::drawCam()
{
	mrScreen.draw(this->viewWindow);
	for (auto& wall : this->walls) {
		mrScreen.draw(*wall);
	}
	mrScreen.draw(this->playerRay);
	//mrScreen.draw(this->viewRay);
}

void Minimap::moveCam(bool back)
{
	float currAngle = playerRay.getRotation();

	if (back) {
		currAngle = currAngle + 180;

		if (currAngle > 360)
			currAngle = currAngle - 360;
	}

	if ((int)currAngle == 0) {
		this->playerRay.move(0.0f, moveSpeed);
		return;
	}
	else if ((int)currAngle == 90) {
		this->playerRay.move(-moveSpeed, 0.0f);
		return;
	}
	else if ((int)currAngle == 180) {
		this->playerRay.move(0.0f, -moveSpeed);
		return;
	}
	else if ((int)currAngle == 270) {
		this->playerRay.move(moveSpeed, 0.0f);
		return;
	}

	if (currAngle < 90) {
		this->playerRay.move(-(moveSpeed * (currAngle / 90)), moveSpeed - (moveSpeed * (currAngle / 90)));
		return;
	}
	else if (currAngle > 90 && currAngle < 180) {
		this->playerRay.move(-moveSpeed + (moveSpeed * ((currAngle-90) / 90)), -(moveSpeed * ((currAngle-90) / 90)));
		return;
	}
	else if (currAngle > 180 && currAngle < 270) {
		this->playerRay.move(moveSpeed * ((currAngle-180) / 90), -moveSpeed + (moveSpeed * ((currAngle-180) / 90)));
		return;
	}
	else if (currAngle > 270 && currAngle < 360) {
		this->playerRay.move(moveSpeed - (moveSpeed * ((currAngle - 270) / 90)), (moveSpeed * ((currAngle - 270) / 90)));
		return;
	}



}

sf::Vector2f Minimap::getPos()
{
	return this->playerRay.getPosition();
}
