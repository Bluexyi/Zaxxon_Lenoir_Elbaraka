#include "Game.h"
#include <SFML/Audio.hpp>

using namespace sf;

//Constructeur
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initSong();
	this->initPlayer();
	this->initEnemies();
}

//Destructeur
Game::~Game()
{
}

//Fonctions privées
void Game::initWindow()
{
	this->window.create(VideoMode(800, 600), "Saxon ESGI", Style::Close);
	this->window.setFramerateLimit(60);
	this->window.setVerticalSyncEnabled(false);
}

void Game::initSong()
{
	if (!bufferThemeInGame.loadFromFile("assets/song/airwolf-theme.wav")) {
		std::cout << "ERROR::GAME::INITSONG::Impossible de charger le son airwolf-theme.wav" << "\n";
	}
	this->themeInGame.setBuffer(bufferThemeInGame);
	this->themeInGame.setVolume(30);

	if (!bufferSongShootPLayer.loadFromFile("assets/song/firePlayer.wav")) {
		std::cout << "ERROR::GAME::INITSONG::Impossible de charger le son firePlayer.wav" << "\n";
	}
	this->SongShootPLayer.setBuffer(bufferSongShootPLayer);
	this->SongShootPLayer.setVolume(30);

	if (!bufferSongHit.loadFromFile("assets/song/hit1.wav")) {
		std::cout << "ERROR::GAME::INITSONG::Impossible de charger le son hit1.wav" << "\n";
	}
	this->songHit.setBuffer(bufferSongHit);
	this->songHit.setVolume(100);
}

void Game::initTextures() {
	//this->textures["BULLET"].loadFromFile("assets/missile/sperm.png");
}

void Game::initPlayer() {
	this->player = std::make_shared<Player>();
	this->player->moveToWorld(sf::Vector2f(30, 30));
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Fonctions Public
void Game::run()
{
	this->themeInGame.play();
	while (this->window.isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents() {
	Event event;
	while (this->window.pollEvent(event)) {
		if (event.Event::type == Event::Closed) {
			this->window.close();
		}
		if (event.Event::KeyPressed && event.Event::key.code == Keyboard::Escape) {
			this->window.close();
		}
	}
}

void Game::updateInput() {
	//Move Player
	Vector2f currentPosition = this->player->getPos();
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		currentPosition.x -= 1 * this->player->getMovementSpeed();
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		currentPosition.x += 1 * this->player->getMovementSpeed();
	}
	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		currentPosition.y -= 1 * this->player->getMovementSpeed();
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		currentPosition.y += 1 * this->player->getMovementSpeed();
	}

	this->player->moveToWorld(currentPosition);

	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack()) {
		this->SongShootPLayer.play();
		this->bullets.push_back(std::make_shared<Bullet>(currentPosition,5.f));
	}
}

void Game::updateBullets() {

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->update();

		if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0.f) {
			//Delete bullet
			this->bullets.erase(bullets.begin() + i);
		}
	}
}

void Game::updateEnnemiesAndCombat()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		//int randbool = rand() % 2;
		//this->player->moveToWorld(sf::Vector2f(rand() % this->window.getSize().x / 2.f + this->window.getSize().x / 2.f, 0)))
		//if (randbool) {
			this->enemies.push_back(std::make_shared<Enemy>(sf::Vector2f(rand() % this->window.getSize().x - 20, -100)));
		//}
		/*else {
			this->enemies.push_back(std::make_shared<Enemy>(this->window.getSize().x - 100.f, rand() % this->window.getSize().y / 2.f));
		}*/
		this->spawnTimer = 0.f;
	}

	for (int i = 0; i < this->enemies.size(); i++) {
		bool enemy_Removed = false;
		this->enemies[i]->update();

		for (size_t j = 0; j < this->bullets.size(); j++) {
			if (!enemy_Removed) {
				if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds())) { //intersects Vérifie l'intersection entre deux rectangles
					this->songHit.play();
					this->bullets.erase(this->bullets.begin() + j);
					this->enemies.erase(this->enemies.begin() + i);
					enemy_Removed = true;
				}
			}
		}

		//Supprimer les enemies en bas de l'écran
		if (!enemy_Removed) {
			if (this->enemies[i]->getBounds().top > this->window.getSize().y) {
				this->enemies.erase(this->enemies.begin() + i);
				std::cout << this->enemies.size() << "\n";
			}
		}
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
	this->updateEnnemiesAndCombat();
}

void Game::render()
{
	this->window.clear();
	this->window.draw(this->player->sprite);
	for (int i = 0; i < bullets.size(); i++) {
		this->window.draw(bullets[i]->getSprite());
	}

	for (std::shared_ptr <Enemy> enemy : this->enemies) {
		this->window.draw(enemy->shape);
	}
	this->window.display();
}