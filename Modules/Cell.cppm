module;
#include <iostream>
#include "SFML/Graphics.hpp"
#include <algorithm>
using namespace sf;
export module Cell;

export class Cell
{
private:
	RectangleShape cell;

	double position;
	double verticalSpeed;
	double mass;
	bool fixed;
public:
	Cell();
	Cell(double height, double width, double x, double y, double mass = 1);
	void draw(RenderWindow& window);
	void move();
	void setVerticalSpeed(double verticalSpeed);
	double getVerticalSpeed();
	double getVerticalPosition();
	void setVerticalPosition(double verticalPosition);
	double getMass();
	void setMass(double mass);
	bool clickOnCell(double x, double y);
	void setFixed(bool fixed);
	bool getFixed();
};

Cell::Cell()
{

}
Cell::Cell(double width, double height, double x, double y, double mass)
{
	this->cell.setSize(Vector2f(width, height));
	this->cell.setPosition(Vector2f(x, y));
	this->verticalSpeed = 0;
	this->mass = mass;
	this->fixed = false;
	this->position = 0;
	
}

void Cell::draw(RenderWindow& window)
{
	double normalPos = this->position / 5;
	double color = std::clamp((int)(normalPos * 255), 0, 255);
	cell.setFillColor(fixed ? Color::Red : Color::Color(color, color, color));
	window.draw(cell);
}
void Cell::move()
{
	this->position += this->verticalSpeed;
}
void Cell::setVerticalSpeed(double verticalSpeed)
{
	this->verticalSpeed = verticalSpeed;
}
double Cell::getVerticalSpeed()
{
	return this->verticalSpeed;
}
double Cell::getVerticalPosition()
{
	return this->position;
}
void Cell::setVerticalPosition(double verticalPosition)
{
	this->position = position;
}
double Cell::getMass()
{
	return this->mass;
}
void Cell::setMass(double mass)
{
	this->mass = mass;
}
bool Cell::clickOnCell(double x, double y)
{
	double cellkPosX = cell.getPosition().x;
	double cellPosY = cell.getPosition().y;
	return (x > cellkPosX && x < cellkPosX + cell.getSize().x) &&
		(y > cellPosY && y < cellPosY + cell.getSize().y);
}
void Cell::setFixed(bool fixed)
{
	this->fixed = fixed;
}
bool Cell::getFixed()
{
	return this->fixed;
}