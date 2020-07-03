#pragma once
#include "Shared.h"
#include "Player.h"
#include "Bullet.h"

class Game
{
private:
	sf::RenderWindow window;

	//Ressources
	//std::map<std::string, sf::Texture> textures;
	std::vector<std::shared_ptr<Bullet>> bullets;

	//Player
	std::shared_ptr<Player> player;

	//Fonctions priv�es
	void initWindow();
	void initTextures();
	void initPlayer();
	//void initEnemies();

public:
	Game();
	virtual ~Game();

	//Fonctions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateBullets();

	void update();
	void render();
};