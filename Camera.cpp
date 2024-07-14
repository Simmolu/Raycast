#include "Camera.h"

const float YSTEP = 30.0f; // width of cell
const float XSTEP = 30.0f; // height of cell
const float PI = 3.1415926535f; // PI
const int blocksize = 30, screenCenter = 240;


Camera::Camera(sf::RenderWindow& window)
	: screeny(window)
{
	
	for (int i = 0; i < 720; i++) {
		auto rayPtr = std::make_unique<sf::RectangleShape>(sf::Vector2f(1, 20));
		rayPtr->setOrigin(0.5, 10);
		rayPtr->setPosition(static_cast<float>(i), 240);
		rayPtr->setFillColor(sf::Color::Green);
		this->rayers.push_back(std::move(rayPtr));
	}
	this->fieldOfView = 60.0; // can be adjusted, best visuals at 60
	this->angleStep = fieldOfView / 720.0f;  // each ray should be a slice of 60 degrees, need enough to paint 720 rays for 720 wide screen

	this->floor = sf::RectangleShape(sf::Vector2f(720, 240));
	this->floor .setFillColor(sf::Color::Cyan);
	this->floor.setOutlineColor(sf::Color::Yellow);
	this->floor.setOutlineThickness(1.0);
	this->floor.setPosition(0, 0);

	this->sky = sf::RectangleShape(sf::Vector2f(720, 240));
	this->sky.setFillColor(sf::Color::Black);
	this->sky.setOutlineColor(sf::Color::Yellow);
	this->sky.setOutlineThickness(1.0);
	this->sky.setPosition(0, 240);
}


void Camera::drawFloor() {
	this->screeny.draw(this->floor);
	this->screeny.draw(this->sky);
}

void Camera::drawRays(float angle, sf::Vector2f position, const int map [5][5])
{
	float height;
	float startAngle = angle - 30;
	float angleoffset;

	if (startAngle < 0) {
		startAngle = 360 + startAngle;
	}


	for (auto& ray : this->rayers) {
		if (ray) {

			angleoffset = abs(angle - startAngle) * PI/180; //multiplying distance by cos of this value fixes fishbowl lens effect
			height = ceil((30 / (horizontalCollison(startAngle, position, map) * cos(angleoffset))) * 554);

			ray->setSize(sf::Vector2f(1.0, height));
			ray->setOrigin(0.5, height / 2);
			ray->setPosition(ray->getPosition().x, screenCenter);

			this->screeny.draw(*ray);

			startAngle = startAngle + angleStep;
			if (startAngle > 360)
				startAngle = startAngle - 360;
		}
		else
			std::cerr << "Null ray encountered!" << std::endl;
	}
}

float Camera::horizontalCollison(float angle, sf::Vector2f position, const int map [5][5])
{	
	float distanceV = 0;
	float distanceH = 0;
	float rayx, rayy, xoff, yoff, playy, playx, dof, ntan, aTan;
	int mapx, mapy;
	bool up = false, right = false;
	playy = position.y;
	playx = position.x;
	dof = 0.0f;


	// So I believe what we need to do here is check both veritcal and horizontal line collison. Compare the distance to collisions for the ray, if it hit a vertical line first draw that distance if it hit horizontal draw that. 

	//BETTER NEW ALGORITHM -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int loopNo = 0;
	while (loopNo < 2) {
		dof = 0.0f;
		up = false;
		

		// CHECK HORIZONTAL LINE COLLISION -----------------------------------
		if (loopNo == 0) {
			aTan = -1 / tan(angle * (PI / 180));
			//Looking up
			if (angle > 180.0f) {
				rayy = (int)(playy / blocksize) * blocksize;
				rayx = (playy - rayy) * aTan + playx;
				yoff = -blocksize;
				xoff = -yoff * aTan;
				up = true;
			}
			//Looking down
			if (angle < 180.0f) {
				rayy = ((int)(playy / blocksize) * blocksize) + blocksize;
				rayx = (playy - rayy) * aTan + playx;
				yoff = +blocksize;
				xoff = -yoff * aTan;
			}
		}


		// CHECK VERTICAL LINE COLLISION--------------------------------------
		else if (loopNo == 1){
			ntan = -tan(angle * (PI / 180));
			//looking right
			if (angle > 270 || angle < 90) {
				rayx = ((int)(playx / blocksize) * blocksize) + blocksize;
				rayy = (playx - rayx) * ntan + playy;

				xoff = +blocksize;
				yoff = -xoff * ntan;
				right = true;
			}
			//looking left
			else if (angle > 90 && angle < 270) {
				rayx = (int)(playx / blocksize) * blocksize;
				rayy = (playx - rayx) * ntan + playy;
				xoff = -blocksize;
				yoff = -xoff * ntan;
			}
		}


		while (dof < 3) {
			if (loopNo == 0) { // calc horizontal intersection on first loop
				mapx = (int)(rayx / blocksize);
				mapy = (int)(rayy / blocksize);
			}
			if (loopNo == 1) { // calc vertical intersection on second loop
				mapx = (int)(rayx / blocksize) - 1;
				mapy = (int)(rayy / blocksize);
			}

			if (up)
				mapy = mapy - 1;

			if (right) 
				mapx += 1;
			

			//clamp map values to avoid array out of bounds for far wall/infinite trig calcs
			if (mapx > 5)
				mapx = 5;
			if (mapy > 5)
				mapy = 5;
			if (mapx < 0)
				mapx = 0;
			if (mapy < 0)
				mapy = 0;


			if (map[mapy][mapx] == 1)
				dof = 8.0f;
			else {
				rayx += xoff;
				rayy += yoff;
				dof += 1;
			}

		}
		if (loopNo == 0) {
			distanceH = sqrt(pow(rayx - playx, 2) + pow(rayy - playy, 2));
		}
		else if (loopNo == 1) {
			distanceV = sqrt(pow(rayx - playx, 2) + pow(rayy - playy, 2));
		}

		loopNo++;
	}
		if (distanceV > distanceH) { // check if a horizontal or vertical wall is closer to camera, draw that one
			return distanceH;
		}
		else {
			return distanceV;
		}
}


