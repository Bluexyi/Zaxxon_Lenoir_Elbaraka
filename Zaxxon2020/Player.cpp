#include "Player.h"

using namespace sf;

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

//Functions publiques
void Player::initVariables() 
{
	this->movementSpeed = 3;
	this->attackCooldownMax = 10;
	this->attackCooldown = this->attackCooldownMax;

	this->pvMax = 30;
	this->pv = this->pvMax;
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("assets/player/1.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Impossible de charger le fichier de texture du player" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
}

//Fonctions privées

//Getter
Vector2f Player::getPos() {
	return this->positonToWorld;
}

sf::FloatRect Player::getBounds()
{
	return this->sprite.getGlobalBounds();
}

float Player::getMovementSpeed()
{
	return this->movementSpeed;
}

int Player::getPv()
{
	return this->pv;
}

int Player::getPvMax()
{
	return this->pvMax;
}

//Setters
void Player::setMovementSpeed(float newMovementSpeed)
{
	this->movementSpeed = newMovementSpeed;
}

void Player::setPv(int pv)
{
	this->pv = pv;
}

void Player::losePv(int value)
{
	this->pv -= value;
	if (this->pv < 0) {
		this->pv = 0;
	}
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5;
	}
}

//Functions
bool Player::canAttack() 
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.5;
		return true;
	}
	return false;
}

void Player::moveToWorld(sf::Vector2f posXY)
{
	this->positonToWorld = posXY;
	sf::Vector2f positionToScreen = WorldToScreen(posXY);
	posXY.y -= this->positionZ;
	this->sprite.setPosition(positionToScreen);
}

sf::Vector2f Player::WorldToScreen(sf::Vector2f position)
{
	return sf::Vector2f(2.0 * position.x - 2.0 * position.y, position.x + position.y);
}

//Other
void Player::update()
{
	this->updateAttack();
}