//includes
#pragma once
#include "../Headerfiles/Headers.h"

class Menu
{
	private:
		//variables for state manage
		sf::RenderWindow& window;
		bool& changeState;

	public:
		//constructor
		Menu(sf::RenderWindow& window, bool& changeState);

		//input, update, render
		void input(sf::Clock deltaClock);
		void update();
		void render();
};

