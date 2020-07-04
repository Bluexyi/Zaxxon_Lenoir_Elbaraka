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

	void initShape();
	void initVariables();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	sf::CircleShape shape;

	//getter
	sf::FloatRect getBounds();

	//fonctions
	void update();
	//void render(sf::RenderTarget target);

};