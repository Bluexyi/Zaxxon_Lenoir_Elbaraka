#include "Game.h"

using namespace sf;

//Constructeur
Game::Game()
{
	this->initWindow();
	//this->initTextures();
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
	this->window.setFramerateLimit(60); // Fréquence de rafraichissement de l'image
	this->window.setVerticalSyncEnabled(false); // Synchronise sur la fréquence verticale de l'écran
}

void Game::initTextures() {
	//this->textures()["BULLET"]= new Texture();
	//this->textures["BULLET"].loadFromFile("textures/sperm.png");
}

void Game::initPlayer() {
	this->player = std::make_shared<Player>();
	this->player->sprite.setPosition(10, 10);
	//this->player->moveToWorld(sf::Vector2f(10, 10));
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
	while (this->window.pollEvent(event)) { // Tant qu'il y a des évènements à traiter...
		if (event.Event::type == Event::Closed) { // L'évènement sf::Event::Closed est déclenché lorsque l'utilisateur veut fermer la fenêtre
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
	/*
	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack()) {
		this->bullets.push_back(
			std::make_shared<Bullet>(this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 4.f,
				this->player->getPos().y,
				1.f,
				-1.f,
				5.f
				)
		);
	}*/
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
}

void Game::render()
{
	this->window.clear();
	this->window.draw(this->player->sprite);
	this->window.display();
}
