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

void Player::initVariables() {

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


