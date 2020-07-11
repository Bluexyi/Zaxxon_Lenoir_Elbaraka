#include "Enemy.h"

using namespace sf;

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = 5.0 / this->pointCount;
	this->pvMax = this->pointCount;
	this->pv =this->pvMax;
	this->damage = this->pv / 2;
	this->points = this->pointCount;
}

Enemy::Enemy(sf::Vector2f spawnPosition) {
	this->initVariables();
	this->initShape();
	this->moveToWorld(spawnPosition);
}

Enemy::~Enemy() {

}

//Getter
sf::FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds();
}

int Enemy::getPoints()
{
	return this->points;
}

int Enemy::getDamage()
{
	return this->damage;
}

int Enemy::getPv()
{
	return this->pv;
}

void Enemy::losePv(int value)
{
	this->pv -= value;
	if (this->pv < 3) {
		this->pv = 0;
	}
	this->shape.setRadius(this->pv * 5);
	this->shape.setPointCount(this->pv);
}

//Fonctions

//Movement
void Enemy::moveToWorld(sf::Vector2f posXY)
{
	this->positonToWorld = posXY;
	sf::Vector2f positionToScreen = WorldToScreen(posXY);
	posXY.y -= this->positionZ;
	this->shape.setPosition(positionToScreen);
}

sf::Vector2f Enemy::WorldToScreen(sf::Vector2f position)
{
	return sf::Vector2f(2 * position.x - 2 * position.y, position.x + position.y);
}

void Enemy::update()
{
	sf::Vector2f newPos = positonToWorld;
	newPos.y += this->speed;
	this->moveToWorld(newPos);
}