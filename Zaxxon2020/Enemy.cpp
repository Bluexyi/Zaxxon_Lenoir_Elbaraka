#include "Enemy.h"

using namespace sf;

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
	this->shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

void Enemy::initVariables()
{
	this->type = 0;
	this->speed = 5.f;
	this->pvMax = 10;
	this->pv = 0;
	this->damage = 1;
	this->points = 5;
}

Enemy::Enemy(sf::Vector2f spawnPosition) {
	this->initShape();
	this->initVariables();
	this->moveToWorld(spawnPosition);
}

Enemy::~Enemy() {

}

//Getter
sf::FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds();
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
	return sf::Vector2f(2.0f * position.x - 2.0f * position.y, position.x + position.y);
}

void Enemy::update()
{
	//this->shape.move(0, 10);
	sf::Vector2f newPos = positonToWorld;
	newPos.y += this->speed;
	this->moveToWorld(newPos);
}