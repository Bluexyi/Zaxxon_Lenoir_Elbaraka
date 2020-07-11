#include "Shared.h"

class Enemy
{
private:
	unsigned pointCount;
	int type;
	float speed;
	int pv;
	int pvMax;
	int damage;
	int points;

	sf::Vector2f positonToWorld;
	float positionZ;

	void initVariables();
	void initShape();

public:
	Enemy(sf::Vector2f spawnPosition);
	virtual ~Enemy();
	sf::CircleShape shape;

	//getter
	sf::FloatRect getBounds();
	int getPoints();
	int getDamage();

	//Movement
	void moveToWorld(sf::Vector2f posXY);
	sf::Vector2f WorldToScreen(sf::Vector2f v);
	sf::Vector2f ScreenToWorld(sf::Vector2f v);

	//fonctions
	void update();

};