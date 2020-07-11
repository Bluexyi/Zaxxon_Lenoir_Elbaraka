#include "Game.h"
#include <SFML/Audio.hpp>

using namespace sf;

//Constructeur
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initHUD();
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
}

void Game::initHUD()
{
	//Load font
	if (!this->font.loadFromFile("assets/policy/Fipps-Regular.otf")) {
		std::cout << "ERROR::GAME::INITHUD::Impossible de charger la police d'ecriture Fipps-Regular.otf" << "\n";
	}

	//Init point text
	this->pointText.setPosition(30, 30);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("score");

	//Init player HUD
	this->playerPvBar.setSize(sf::Vector2f(300, 25));
	this->playerPvBar.setFillColor(sf::Color::Red);
	this->playerPvBar.setPosition(sf::Vector2f(30, 50));

	this->playerPvBarBack = this->playerPvBar;
	this->playerPvBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initSystems()
{
}

void Game::initPlayer() {
	this->player = std::make_shared<Player>();
	this->player->moveToWorld(sf::Vector2f(30, 30));
}

void Game::initEnemies()
{
	this->spawnTimerMax = 5;
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

sf::Vector2f Game::ScreenToWorld(sf::Vector2f v)
{
	return sf::Vector2f((v.x + 2.0f * v.y) / 4.0f, (2.0f * v.y - v.x) / 4.0f);
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
		this->bullets.push_back(std::make_shared<Bullet>(currentPosition,5));
	}
}

void Game::updateHUD()
{
	std::stringstream ss;
	ss << "Score: " << this->points;
	this->pointText.setString(ss.str());

	float pvPercent = static_cast<float>(this->player->getPv()) / this->player->getPvMax();
	this->playerPvBar.setSize(sf::Vector2f(this->playerPvBarBack.getSize().x * pvPercent, this->playerPvBar.getSize().y));
}

void Game::updateBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->update();

		if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0) {
			//Delete bullet
			this->bullets.erase(bullets.begin() + i);
		}
	}
}

void Game::updateEnnemies()
{
	//Spawn enemies
	this->spawnTimer += 0.5;
	if (this->spawnTimer >= this->spawnTimerMax) {
		std::cout << "Spawn Enemy";
		Vector2f virtualPosition = ScreenToWorld(sf::Vector2f(this->window.getSize().x, this->window.getSize().y));
		this->enemies.push_back(std::make_shared<Enemy>(sf::Vector2f(rand() % static_cast<int>(virtualPosition.x) + 1, -100)));
		this->spawnTimer = 0;
	}

	//update
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update();

		if (enemies[i]->getBounds().top + enemies[i]->getBounds().height > this->window.getSize().y) {
			//Delete bullet
			this->enemies.erase(enemies.begin() + i);
		}
		else if (enemies[i]->getBounds().intersects(this->player->getBounds())) {
			this->player->losePv(enemies[i]->getDamage());
			this->enemies.erase(enemies.begin() + i);
		}
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); i++) {
		bool enemy_Removed = false;
		this->enemies[i]->update();

		for (size_t j = 0; j < this->bullets.size(); j++) {
			if (!enemy_Removed) {
				if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds())) { //intersects Vérifie l'intersection entre deux rectangles
					this->points += this->enemies[i]->getPoints();
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
	this->updateEnnemies();
	this->updateCombat();
	this->updateHUD();
}

void Game::renderHUD()
{
	this->window.draw(this->pointText);
	this->window.draw(this->playerPvBarBack);
	this->window.draw(this->playerPvBar);
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
	this->renderHUD();
	this->window.display();
}