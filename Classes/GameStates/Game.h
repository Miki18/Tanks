//includes
#pragma once
#include "../Headers.h"
#include "../Objects/Player.h";
#include "../Objects/Bullet.h";
#include "../Objects/Coin.h";

class Game
{
private:
	//variables for state manage
	sf::RenderWindow& window;
	bool& changeState;
	const int WindowXSize = 1600;
	const int WindowYSize = 900;

	Player player;
	std::vector<Bullet> bullets;
	std::vector<Coin> coins;

	sf::Clock deltaClock;

	float TimeUntilCoinSpawn = 3.0f;
	float TimeSincePlayerShoot = 100.0f;

	sf::Vector2f CurrentMousePos = {0, 0};

	sf::Texture CoinText;

	bool MovePlayer = false;

public:
	//constructor
	Game(sf::RenderWindow& window, bool& changeState);

	//input, update, render
	void input();
	void update();
	void render();
};