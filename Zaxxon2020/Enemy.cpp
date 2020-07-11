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
	this->speed = this->pointCount / 3;
	this->pvMax = this->pointCount;
	this->pv =this->pvMax;
	this->damage = this->pointCount / 2;
	this->points = this->pointCount;
}

Enemy::Enemy(sf::Vector2f spawnPosition) {
	this->initVariables();
	this->initShape();
	//this->shape.setPosition(spawnPosition);
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
	return sf::Vector2f(2.0 * position.x - 2.0 * position.y, position.x + position.y);
}

void Enemy::update()
{
	//this->shape.move(0, 10);
	sf::Vector2f newPos = positonToWorld;
	newPos.y += this->speed;
	this->moveToWorld(newPos);
}