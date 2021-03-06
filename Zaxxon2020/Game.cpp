#include "Game.h"
#include <SFML/Audio.hpp>

using namespace sf;

//Constructeur
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initHUD();
	this->initWorld();
	this->initSong();
	this->initPlayer();
	this->initEnemies();
}

//Destructeur
Game::~Game()
{
}

//Fonctions priv�es
void Game::initWindow()
{
	this->window.create(VideoMode(800, 600), "Saxxon ESGI", Style::Close);
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

	if (!bufferThemeGameOver.loadFromFile("assets/song/game-over-theme.wav")) {
		std::cout << "ERROR::GAME::INITSONG::Impossible de charger le son game-over-theme.wav" << "\n";
	}
	this->themeGameOver.setBuffer(bufferThemeGameOver);
	this->themeGameOver.setVolume(50);
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

	//Init gameOver text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(36);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER !");
	this->gameOverText.setPosition(
		this->window.getSize().x / 2 - this->gameOverText.getGlobalBounds().width / 2,
		this->window.getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2);

	//Init player HUD
	this->playerPvBar.setSize(sf::Vector2f(300, 25));
	this->playerPvBar.setFillColor(sf::Color::Red);
	this->playerPvBar.setPosition(sf::Vector2f(30, 50));

	this->playerPvBarBack = this->playerPvBar;
	this->playerPvBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	if (!this->worldBackgroundTexture.loadFromFile("assets/background/space-font.jpg")) {
		std::cout << "ERROR::GAME::INITWORLD::Impossible de charger la texture space-font.jpg" << "\n";
	}
	this->worldBackgroundSprite.setTexture(this->worldBackgroundTexture);
}

void Game::initSystems()
{
	this->playGameOverTheme = false;
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
		this->updatePollEvents();

		if (this->player->getPv() > 0) {
			this->update();
		}
		if (!this->playGameOverTheme && this->player->getPv() <= 0) {
			this->themeGameOver.play();
			this->playGameOverTheme = true;
		}
		this->render();
	}
}

sf::Vector2f Game::ScreenToWorld(sf::Vector2f v)
{
	return sf::Vector2f((v.x + 2 * v.y) / 4, (2 * v.y - v.x) / 4);
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
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		currentPosition.x -= 1 * this->player->getMovementSpeed();
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		currentPosition.x += 1 * this->player->getMovementSpeed();
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		currentPosition.y -= 1 * this->player->getMovementSpeed();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		currentPosition.y += 1 * this->player->getMovementSpeed();
	}

	this->player->moveToWorld(currentPosition);

	if (Keyboard::isKeyPressed(Keyboard::Space) && this->player->canAttack()) {
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
				if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds())) {
					this->enemies[i]->losePv(1);
					this->songHit.play();
					this->bullets.erase(this->bullets.begin() + j);
					if (this->enemies[i]->getPv() <= 0) {
						this->points += this->enemies[i]->getPoints();
						this->enemies.erase(this->enemies.begin() + i);
						enemy_Removed = true;
					}
				}
			}
		}

		//Supprimer les enemies en bas de l'�cran
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

void Game::renderWorld()
{
	this->window.draw(this->worldBackgroundSprite);
}

void Game::render()
{
	this->window.clear();

	this->renderWorld();

	this->window.draw(this->player->sprite);
	for (int i = 0; i < bullets.size(); i++) {
		this->window.draw(bullets[i]->getSprite());
	}

	for (std::shared_ptr <Enemy> enemy : this->enemies) {
		this->window.draw(enemy->shape);
	}
	this->renderHUD();

	//Game Over
	if (this->player->getPv() <= 0) {
		this->themeInGame.stop();
		this->window.draw(this->gameOverText);
	}

	this->window.display();
}