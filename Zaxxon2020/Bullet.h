#include "Shared.h"

class Bullet
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f direction;
	float mouvementSpeed;

	sf::Vector2f positonToWorld;
	float positionZ;


	//Fonctions privées
	void initVariables();



public:
	Bullet();
	Bullet(sf::Vector2f currentPlayerPosition, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Getter
	sf::FloatRect getBounds();
	sf::Sprite getSprite();

	//Movement
	void moveToWorld(sf::Vector2f posXY);
	sf::Vector2f WorldToScreen(sf::Vector2f v);

	void update();

};
