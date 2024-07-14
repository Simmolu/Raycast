#include "Application.h"


const int Application::map[5][5] = {
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,1,1},
	{1,0,0,0,1},
	{1,1,1,1,1},
};

Application::Application(sf::RenderWindow& screen)
	: mrScreen(screen), mapper(Minimap(screen, this->map)), cam(Camera(screen)), ev(sf::Event())
{
	this->fonty = sf::Font();
	if (!fonty.loadFromFile("arial.ttf")) {
		throw std::invalid_argument("Font cannot be read.");
	}

	this->position = sf::Text();
	this->position.setCharacterSize(15);
	this->position.setFillColor(sf::Color::White);
	this->position.setFont(this->fonty);
	this->position.setPosition(620, 400);

	this->x = 0;
	this->y = 0;
}



void Application::drawEverything()
{
	this->x = (int)(this->mapper.getPos().x / 30);
	this->y = (int)(this->mapper.getPos().y / 30);
	
	
	this->cam.drawFloor();
	
	this->cam.drawRays(this->mapper.getAngle(), this->mapper.getPos(), this->map);
	this->mapper.drawCam();

	this->position.setString("X: " + std::to_string(this->x) + "\nY: " + std::to_string(this->y) + "\n Angle: " + std::to_string(this->mapper.getAngle()) + "\n");
	this->mrScreen.draw(position);
	this->mrScreen.display();
	
}

bool Application::appRun() {
	this->mrScreen.clear();
	float horiz = 0;
	

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
		this->mapper.moveCam(false, this->map);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->mapper.moveCam(true, this->map);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		return false;
	}
	drawEverything();
	
	return true;
}
