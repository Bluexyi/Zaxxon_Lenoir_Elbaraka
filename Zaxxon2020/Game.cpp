#include "Game.h"

using namespace sf;

//Constructeur
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	//this->initEnemies();
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

void Game::initTextures() {
	//this->textures["BULLET"].loadFromFile("assets/missile/sperm.png");
}

void Game::initPlayer() {
	this->player = std::make_shared<Player>();
	this->player->moveToWorld(sf::Vector2f(30, 30));
}

//Fonctions Public
void Game::run()
{
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
		this->bullets.push_back(
			std::make_shared<Bullet>(
				currentPosition,
				1.f,
				-1.f,
				5.f
			)
		);
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

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
}

void Game::render()
{
	this->window.clear();
	this->window.draw(this->player->sprite);
	for (int i = 0; i < bullets.size(); i++) {
		this->window.draw(bullets[i]->getSprite());
	}
	this->window.display();
}
