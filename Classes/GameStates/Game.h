//includes
#pragma once
#include "../Headers.h"
#include "../Objects/Player.h";
#include "../Objects/Bullet.h";

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

	sf::Vector2f CurrentMousePos = {0, 0};

	bool MovePlayer = false;

public:
	//constructor
	Game(sf::RenderWindow& window, bool& changeState);

	//input, update, render
	void input(sf::Clock &deltaClock);
	void update(sf::Clock &deltaClock);
	void render();
};
