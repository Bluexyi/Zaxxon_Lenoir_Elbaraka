#include "Shared.h"

class Enemy
{
private:
	int type;
	float speed;
	int pv;
	int pvMax;
	int damage;
	int points;

	sf::Vector2f positonToWorld;
	float positionZ;

	void initShape();
	void initVariables();

public:
	Enemy(sf::Vector2f spawnPosition);
	virtual ~Enemy();
	sf::CircleShape shape;

	//getter
	sf::FloatRect getBounds();

	//Movement
	void moveToWorld(sf::Vector2f posXY);
	sf::Vector2f WorldToScreen(sf::Vector2f v);

	//fonctions
	void update();

};