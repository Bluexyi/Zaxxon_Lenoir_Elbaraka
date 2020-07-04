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

Enemy::Enemy(float pos_x, float pos_y) {
	this->initShape();
	this->initVariables();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy() {

}

//Getter
sf::FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds();
}

//Fonctions
void Enemy::update()
{
	this->shape.move(-1.f, 1.f);
}