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
	this->movementSpeed = 3.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	//Charge les fichiers de texture
	if (!this->texture.loadFromFile("assets/player/1.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Impossible de charger le fichier de texture du player" << "\n";
	}
}

void Player::initSprite()
{
	//Charge les fichiers de sprite
	this->sprite.setTexture(this->texture);

	//Resize les sprites
	//this->sprite.scale(0.15f, 0.15f);
	//this->sprite.setRotation(45);
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

//Setters
void Player::setMovementSpeed(float newMovementSpeed)
{
	this->movementSpeed = newMovementSpeed;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}

//Functions
bool Player::canAttack() 
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.5f;
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
	return sf::Vector2f(2.0f * position.x - 2.0f * position.y, position.x + position.y);
}

//Other
void Player::update()
{
	this->updateAttack();
}