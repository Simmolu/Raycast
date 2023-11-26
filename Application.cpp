#include "Application.h"

Application::Application(sf::RenderWindow& screen, int mappy[5][5])
	: mrScreen(screen), mapper(Minimap(screen, mappy)), cam(Camera(screen)), ev(sf::Event())
{
	this->fonty = sf::Font();
	if (!fonty.loadFromFile("arial.ttf")) {
		throw std::invalid_argument("Font cannot be read.");
	}

	this->position = sf::Text();
	this->position.setCharacterSize(20);
	this->position.setFillColor(sf::Color::White);
	this->position.setFont(this->fonty);
	this->position.setPosition(640, 420);
}

void Application::drawEverything()
{
	this->x = this->mapper.getPos().x;
	this->y = this->mapper.getPos().y;
	this->cam.drawRays(this->mapper.getAngle());
	this->mapper.drawCam();
	this->position.setString("X: " + std::to_string(this->x) + "\nY: " + std::to_string(this->y));
	this->mrScreen.draw(position);
	this->mrScreen.display();
}

bool Application::appRun(int map[5][5]) {
	this->mrScreen.clear();


	while (this->mrScreen.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed) {
			mrScreen.close();
			return false;
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->mapper.rotateRays(-0.1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->mapper.rotateRays(0.1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->mapper.moveCam();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		std::cout << this->cam.horizontalCollison(this->mapper.getAngle(), this->mapper.getPos(), map) << "\n";
	}

	drawEverything();
	return true;
}
