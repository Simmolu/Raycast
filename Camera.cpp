#include "Camera.h"

const float YSTEP = 30.0f; // width of cell
const float XSTEP = 30.0f; // height of cell
const float PI = 3.1415926535f; // PI
const float angleStep = 60.0f / 720.0f; // each ray should be a slice of 60 degrees, need enough to paint 720 rays for 720 wide screen

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
	this->fieldOfView = 60.0;
}

void Camera::drawFloor() {
	sf::RectangleShape floor = sf::RectangleShape(sf::Vector2f(720, 480));
	floor.setFillColor(sf::Color::White);
	floor.setPosition(0, 0);
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
			angleoffset = abs(angle - startAngle) * PI/180; //fixes fishbowl
			//height = 480 - (4 * (horizontalCollison(startAngle, position, map) * cos(angleoffset)));
			height = ceil((30 / (horizontalCollison(startAngle, position, map) * cos(angleoffset))) * 554);
			if (height < 0) {
				height = 1;
			}
			ray->setSize(sf::Vector2f(1.0, height));
			ray->setOrigin(0.5, height / 2);
			ray->setPosition(ray->getPosition().x, 240);
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
	const float epsilon = 0.5f;

	float vrayx, vrayy, hrayx, hrayy, xoff, yoff, playy, playx, dof, distanceV, distanceH, ntan, aTan;
	int mapx, mapy, temp, count;
	bool up = false, right = false, isVertical = false, isHorizontal = false;
	playy = position.y;
	playx = position.x;
	dof = 0.0f;


	
	
	float yNearest, xNearest;


	// So I believe what we need to do here is check both veritcal and horizontal line collison. Compare the distance to collisions for the ray, if it hit a vertical line first draw that distance if it hit horizontal draw that. 



	if (angle > 180.0f or angle < 180.0f) {
		if ((fabs(fmod(angle, 360)) < epsilon || fabs(fmod(angle, 180)) < epsilon)) {
			if (abs(angle - 180) < epsilon) { //WE ARE LOOKING STRAIGHT LEFT
				xoff = -30;
				xNearest = int(playx / 30) * 30;
				hrayy = int(playy / 30) * 30;
				hrayx = xNearest;

				while (dof < 3) {
					mapy = (int)(hrayy / 30) - 1;
					mapx = (int)(hrayx / 30);

					if (mapx > 5)
						mapx = 5;
					if (mapy > 5)
						mapy = 5;
					if (mapx < 0)
						mapx = 0;
					if (mapy < 0)
						mapy = 0;

					if (map[mapx][mapy] == 1)
						dof = 8.0f;
					else {
						hrayx += xoff;
						dof += 1;
					}
				}
				return sqrt(pow(playx - hrayx, 2) + pow(playy - playy, 2));
			}
			else if (abs(angle-360) < epsilon) { // WE ARE LOOKING STRAIGHT RIGHT
				xoff = 30;
				xNearest = int(playx / 30) * 30;
				hrayy = int(playy / 30) * 30;
				hrayx = xNearest;
				while (dof < 3) {
					mapy = (int)(hrayy / 30) - 1;
					mapx = (int)(hrayx / 30);

					if (mapx > 5)
						mapx = 5;
					if (mapy > 5)
						mapy = 5;
					if (mapx < 0)
						mapx = 0;
					if (mapy < 0)
						mapy = 0;

					if (map[mapx][mapy] == 1)
						dof = 8.0f;
					else {
						hrayx += xoff;
						dof += 1;
					}
				}
				return sqrt(pow(playx - hrayx, 2) + pow(playy - playy, 2));
			}
		}


		// CHECK HORIZONTAL LINE COLLISION ----------------------------------------------------------------------------------------------------------------------------------------------
		aTan = -1 / tan(angle * (PI / 180));
		//Looking up
		if (angle > 180.0f) {
			hrayy = (int)(playy / 30) * 30;
			hrayx = (playy - hrayy) * aTan + playx;
			yoff = -30;
			xoff = -yoff * aTan;
			up = true;
		}
		//Looking down
		if (angle < 180.0f) {
			hrayy = ((int)(playy / 30) * 30) + 30;
			hrayx = (playy - hrayy) * aTan + playx;
			yoff = +30;
			xoff = -yoff * aTan;
		}

		while (dof < 3) {
			mapx = ((int)(hrayx / 30) - 1);
			mapy = (int)(hrayy / 30);

			if (mapx > 5)
				mapx = 5;
			if (mapy > 5)
				mapy = 5;
			if (mapx < 0)
				mapx = 0;
			if (mapy < 0)
				mapy = 0;

			if (up)
				mapy = mapy - 1;
			if (map[mapy][mapx + 1] == 1)
				dof = 8.0f;
			else {
				hrayx += xoff;
				hrayy += yoff;
				dof += 1;
			}
		}
	}
	distanceH = sqrt(pow(hrayx - playx, 2) + pow(hrayy - playy, 2));

	// STRAIGHT UP/DOWN/SIDE ------------------------------------------------------------------------
	dof = 0.0;
	if (fabs(fmod(angle, 180) - 90) < epsilon) {
		if (abs(angle - 270.0) < epsilon) { //WE ARE LOOKING STRAIGHT UP
			yoff = -30;
			yNearest = (int)(playy / 30) * 30;
			hrayy = yNearest;
			hrayx = int(playx / 30) * 30;
			while (dof < 3) {
				mapy = (int)(hrayy / 30) - 1;
				mapx = (int)(hrayx / 30);
				if (mapx > 5)
					mapx = 5;
				if (mapy > 5)
					mapy = 5;
				if (mapx < 0)
					mapx = 0;
				if (mapy < 0)
					mapy = 0;
				if (map[mapx][mapy] == 1)
					dof = 8.0f;
				else {
					hrayy += yoff;
					dof += 1;
				}
			}
			return sqrt(pow(playx - playx, 2) + pow(hrayy - playy, 2));
		}
		else { // WE ARE LOOKING STRAIGHT DOWN
			yNearest = ceil(playy / 30) * 30;
			yoff = 30;
			hrayy = yNearest;
			hrayx = int(playx / 30) * 30;
			while (dof < 3) {
				mapy = (int)(hrayy / 30);
				mapx = (int)(hrayx / 30);

				if (mapx > 5)
					mapx = 5;
				if (mapy > 5)
					mapy = 5;
				if (mapx < 0)
					mapx = 0;
				if (mapy < 0)
					mapy = 0;

				if (map[mapy][mapx] == 1) {
					dof = 8.0f;
				}
				else {
					hrayy += yoff;
					dof += 1;
				}
			}
			return sqrt(pow(playx - playx, 2) + pow(hrayy - playy, 2));
		}
	}

	dof = 0.0;
	



	if (!isVertical) {
		//looking right

		ntan = -tan(angle * (PI / 180));
		if (angle > 270 || angle < 90) {
			vrayx = ((int)(playx / 30) * 30) + 30;
			vrayy = (playx - vrayx) * ntan + playy;
			xoff = +30;
			yoff = -xoff * ntan;
			right = true;
		}
		//looking left
		else if (angle > 90 && angle < 270) {
			vrayx = (int)(playx / 30) * 30;
			vrayy = (playx - vrayx) * ntan + playy;
			xoff = -30;
			yoff = -xoff * ntan;
		}


		while (dof < 3) {
			mapx = std::min((int)(vrayx / 30) - 1, 5);
			mapy = std::min((int)(vrayy / 30), 5);
			if (mapx > 5)
				mapx = 5;
			if (mapy > 5)
				mapy = 5;
			if (mapx < 0)
				mapx = 0;
			if (mapy < 0)
				mapy = 0;
			if (right) {
				mapx += 1;
				temp = mapx;
				mapx = mapy;
				mapy = temp;
			}
			if (map[mapx][mapy] == 1)
				dof = 8.0f;
			else {
				vrayx += xoff;
				vrayy += yoff;
				dof += 1;
			}

		}
		distanceV = sqrt(pow(vrayx - playx, 2) + pow(vrayy - playy, 2));

	}

	if (distanceV > distanceH) { // check if a horizontal or vertical wall is closer to camera, draw that one
		return distanceH;
	}
	else {
		return distanceV;
	}

}


