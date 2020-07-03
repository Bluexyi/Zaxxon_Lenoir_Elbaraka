#pragma once
#include "Shared.h"

class Player
{
private:
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

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
	sf::FloatRect getBounds();
	float getMovementSpeed();

	//Setter
	void setMovementSpeed(float newMovementSpeed);

	//Fonction

	//Attack
	void updateAttack();
	bool canAttack();

	//Movement
	void moveToWorld(sf::Vector2f posXY);
	sf::Vector2f WorldToScreen(sf::Vector2f v);
	sf::Vector2f ScreenToWorld(sf::Vector2f v);

	//Other
	void update();
};

