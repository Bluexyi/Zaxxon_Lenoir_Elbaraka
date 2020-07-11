#pragma once
#include "Shared.h"
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <SFML/Audio.hpp>

class Game
{
private:
	sf::RenderWindow window;

	//Ressources
	//std::map<std::string, sf::Texture> textures;
	std::vector<std::shared_ptr<Bullet>> bullets;

	//HUD
	sf::Font font;
	sf::Text pointText;

	//Systems
	unsigned points;

	//Player
	std::shared_ptr<Player> player;

	//PlayerHUD
	sf::RectangleShape playerPvBar;
	sf::RectangleShape playerPvBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<std::shared_ptr<Enemy>> enemies;

	//Song
	sf::SoundBuffer bufferThemeInGame;
	sf::SoundBuffer bufferSongShootPLayer;
	sf::SoundBuffer bufferSongHit;

	sf::Sound themeInGame;
	sf::Sound SongShootPLayer;
	sf::Sound songHit;

	//Fonctions privées
	void initWindow();
	void initSong();
	void initTextures();
	void initHUD();
	void initSystems();
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();



	//Fonctions
	void run();
	sf::Vector2f ScreenToWorld(sf::Vector2f v);
	void updatePollEvents();
	void updateInput();
	void updateHUD();
	void updateBullets();
	void updateEnnemies();
	void updateCombat();
	void update();
	void renderHUD();
	void render();
};