#include "circle.h"
#include <vector>
#include "stdlib.h"
#include <math.h>

const double COLLISION_FRICTION = 1.0;

Circle::Circle(double x, double y, double dx, double dy, int r, std::vector<int> color)
	:	mX(x), mY(y), mDx(dx), mDy(dy), mRadius(r), mColor(color)
{
}

int Circle::getX() {
	return mX;
}

int Circle::getY() {
	return mY;
}

double Circle::getDx() {
	return mDx;
}

double Circle::getDy() {
	return mDy;
}

int Circle::getRadius() {
	return mRadius;
}


std::vector<int> Circle::getColor() {
	return mColor;
}

void Circle::changeColor() {
	std::srand(std::time(0));
	int red = std::rand() % 2;
	int green = std::rand() % 2;
	int blue = std::rand() % 2;
	while (red == 1 && blue == 1 && green == 1) {
		red = std::rand() % 2;
		green = std::rand() % 2;
		blue = std::rand() % 2;
	}
	mColor[0] =red;
	mColor[1] = green;
	mColor[2] = blue;
}

void Circle::gravity(int screen_x, int screen_y) {
	if (mX + mDx + mRadius > screen_x) {
		mDx = -mDx;
	}
	if (mX + mDx - mRadius < 0) {
		mDx = -mDx;
	}
	if (mY + mDy + mRadius > screen_y) {
		mDy = -mDy;
	}
	if (mY + mDy - mRadius < 0) {
		mDy = -mDy;
	}
	mDy -= .005;
}

void Circle::move(int screen_x, int screen_y) {

	if (mX + mDx + mRadius > screen_x) {
		mDx = -mDx;
	}
	if (mX + mDx - mRadius < 0) {
		mDx = -mDx;
	}
	if (mY + mDy + mRadius > screen_y) {
		mDy = -mDy;
	}
	if (mY + mDy - mRadius < 0) {
		mDy = -mDy;
	}
	mX += mDx;
	mY += mDy;
}

double Circle::getnextx() { 
	return mX + mDx; 
}

double Circle::getnexty() { 
	return mY + mDy; 
}

void Circle::setdx(double dx) {
	mDx = dx;
}
void Circle::setdy(double dy) { 
	mDy = dy; 
}

bool Circle::willCollide(int n, int i, std::vector<Circle> &circles) {
	double x = circles[i].getnextx() - circles[n].getnextx();
	double y = circles[i].getnexty() - circles[n].getnexty();
	double dist = sqrt((x*x) + (y*y));
	if (dist <= circles[i].getRadius() + circles[n].getRadius()) {

		return true;
	}
	else {
		return false;
	}
}

void Circle::checkForCollision(int n, std::vector<Circle> &circles) {
	for (int i = 0; i < circles.size(); i++) {
		if (willCollide(n, i, circles) == true && n != i) {
			collide(n, i, circles);
		}
	}
}

struct vectortype
{
	double x;
	double y;
};

void Circle::collide(int p1, int p2, std::vector<Circle> &particles) {
	changeColor();
	vectortype en; // Center of Mass coordinate system, normal component
	vectortype et; // Center of Mass coordinate system, tangential component
	vectortype u[2]; // initial velocities of two particles
	vectortype um[2]; // initial velocities in Center of Mass coordinates
	double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
	double umn[2]; // initial velocities in Center of Mass coordinates, normal component
	vectortype v[2]; // final velocities of two particles
	double m[2];	// mass of two particles
	double M; // mass of two particles together
	vectortype V; // velocity of two particles together
	double size;
	int i;

	double xdif = particles[p1].getnextx() - particles[p2].getnextx();
	double ydif = particles[p1].getnexty() - particles[p2].getnexty();

	// set Center of Mass coordinate system
	size = sqrt(xdif*xdif + ydif*ydif);
	xdif /= size; ydif /= size; // normalize
	en.x = xdif;
	en.y = ydif;
	et.x = ydif;
	et.y = -xdif;

	// set u values
	u[0].x = particles[p1].getDx();
	u[0].y = particles[p1].getDy();
	m[0] = particles[p1].getRadius()*particles[p1].getRadius();
	u[1].x = particles[p2].getDx();
	u[1].y = particles[p2].getDy();
	m[1] = particles[p2].getRadius()*particles[p2].getRadius();

	// set M and V
	M = m[0] + m[1];
	V.x = (u[0].x*m[0] + u[1].x*m[1]) / M;
	V.y = (u[0].y*m[0] + u[1].y*m[1]) / M;

	// set um values
	um[0].x = m[1] / M * (u[0].x - u[1].x);
	um[0].y = m[1] / M * (u[0].y - u[1].y);
	um[1].x = m[0] / M * (u[1].x - u[0].x);
	um[1].y = m[0] / M * (u[1].y - u[0].y);

	// set umt and umn values
	for (i = 0; i<2; i++)
	{
		umt[i] = um[i].x * et.x + um[i].y * et.y;
		umn[i] = um[i].x * en.x + um[i].y * en.y;
	}

	// set v values
	for (i = 0; i<2; i++)
	{
		v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
		v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
	}

	// reset particle values
	particles[p1].setdx(v[0].x*COLLISION_FRICTION);
	particles[p1].setdy(v[0].y*COLLISION_FRICTION);
	particles[p2].setdx(v[1].x*COLLISION_FRICTION);
	particles[p2].setdy(v[1].y*COLLISION_FRICTION);

}