#pragma once
#include "Shared.h"

class Player
{
private:
	sf::Texture texture;

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
};

