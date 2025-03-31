//includes
#pragma once
#include "../Headers.h"
#include "../Objects/Player.h"
#include "../Objects/Bullet.h"
#include "../Objects/Coin.h"
#include "../Objects/Wall.h"

class Game
{
private:
	//variables for state manage
	sf::RenderWindow& window;
	bool& changeState;
	int& level;

	const int WindowXSize = 1600;
	const int WindowYSize = 900;

	Player player;
	std::vector<Bullet> bullets;
	std::vector<Coin> coins;
	std::vector<Wall> walls;

	sf::Clock deltaClock;

	float TimeUntilCoinSpawn = 5.0f;
	float TimeSincePlayerShoot = 100.0f;

	sf::Vector2f CurrentMousePos = {0, 0};

	sf::Texture CoinText;

	bool MovePlayer = false;

	//load and create level
	void LoadLevel(int LevelNumber);

public:
	//constructor
	Game(sf::RenderWindow& window, bool& changeState, int& level);

	//input, update, render
	void input();
	void update();
	void render();
};