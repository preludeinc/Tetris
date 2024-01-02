#include "Point.h"

Point::Point() { this->x = 0; this->y = 0; }

Point::Point(int x, int y) : x(x), y(y) {}

int Point::getX() const { return x; }

int Point::getY() const { return y; }

void Point::setX(int x) { this->x = x; }

void Point::setY(int y) { this->y = y; }

void Point::setXY(int x, int y) { setX(x); setY(y); }

void Point::swapXY() { setXY(y, x); }

void Point::multiplyX(int factor) { x = x * factor; }

void Point::multiplyY(int factor) { y = y * factor; }

std::string Point::toString() const
{
	return '[' + x + "," + y + ']';
}
