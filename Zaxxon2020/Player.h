#pragma once
#include "Shared.h"

class Player
{
private:
	sf::Texture texture;

	float movementSpeed;

	sf::Vector2f positonToWorld;
	float positionZ;

	//Fonctions privées
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();
	sf::Sprite sprite;

	//Getter
	sf::Vector2f getPos();
	float getMovementSpeed();

	//Setter
	void setMovementSpeed(float newMovementSpeed);

	//Fonction

	//Movement
	void moveToWorld(sf::Vector2f posXY);
	sf::Vector2f WorldToScreen(sf::Vector2f v);
	sf::Vector2f ScreenToWorld(sf::Vector2f v);
};

