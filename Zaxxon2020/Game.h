#pragma once
#include "Shared.h"
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;

	//Ressources
	std::map<std::string, sf::Texture> textures;

	//Player
	std::shared_ptr<Player> player;

	//Fonctions privées
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

	void update();
	void render();

};

