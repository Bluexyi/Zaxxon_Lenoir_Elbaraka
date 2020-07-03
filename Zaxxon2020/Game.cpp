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

void Game::update()
{
	this->updatePollEvents();
}

void Game::render()
{
	this->window.clear();
	this->window.draw(this->player->sprite);
	this->window.display();
}
