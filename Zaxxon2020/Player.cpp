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

void Player::initVariables() {
	this->movementSpeed = 3.f;
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

float Player::getMovementSpeed()
{
	return this->movementSpeed;
}

void Player::setMovementSpeed(float newMovementSpeed)
{
	this->movementSpeed = newMovementSpeed;
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
	// Function to convert a world position to a screen (view) position
	// ScreenX = 2*WorldX - 2*WorldY
	// ScreenY = WorldX + WorldY
	return sf::Vector2f(2.0f * position.x - 2.0f * position.y, position.x + position.y);
}

sf::Vector2f Player::ScreenToWorld(sf::Vector2f position)
{
	// Function to convert a screen (view) position to a world position
	// WorldX = (ScreenX + 2*ScreenY)/4
	// WorldY = (2*ScreenY - ScreenX)/4
	return sf::Vector2f((position.x + 2.0f * position.y) / 4.0f, (2.0f * position.y - position.x) / 4.0f);
}
