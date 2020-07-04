#include "Bullet.h"

using namespace sf;

Bullet::~Bullet() {

}

Bullet::Bullet()
{
}

Bullet::Bullet(Vector2f currentPlayerPosition, float movement_speed) {
	//Charge les fichiers de texture
	if (!this->texture.loadFromFile("assets/missile/1.png")) {
		std::cout << "ERROR::BULLET::INITTEXTURE::Impossible de charger le fichier de texture du missile" << "\n";
	}
	this->sprite.setTexture(texture);
	//this->shape.setRotation(45);

	this->moveToWorld(currentPlayerPosition);
	//this->sprite.setPosition(currentPlayerPosition);
	this->mouvementSpeed = movement_speed;
}

void Bullet::initVariables() {
	this->mouvementSpeed = 3.f;
}

//Getter
FloatRect Bullet::getBounds() {
	return this->sprite.getGlobalBounds(); //Obtenir le rectangle global de délimitation de l'entité
}

sf::Sprite Bullet::getSprite()
{
	return this->sprite;
}

//Movement
void Bullet::moveToWorld(sf::Vector2f posXY)
{
	this->positonToWorld = posXY;
	sf::Vector2f positionToScreen = WorldToScreen(posXY);
	posXY.y -= this->positionZ;
	this->sprite.setPosition(positionToScreen);
}

sf::Vector2f Bullet::WorldToScreen(sf::Vector2f position)
{
	return sf::Vector2f(2.0f * position.x - 2.0f * position.y, position.x + position.y);
}

void Bullet::update() {
	//Movement
	sf::Vector2f newPos = positonToWorld;
	newPos.y -= this->mouvementSpeed;
	this->moveToWorld(newPos);
}