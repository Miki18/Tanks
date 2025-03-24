//includes; Headers has include from imgui, sfml and others that are needed in different files
//Menu.h and Game.h are classes
#include "Headers.h"
#include "Classes/GameStates/Menu.h"
#include "Classes/GameStates/Game.h"

int main() {

	//State Enum
	enum State
	{
		MenuState,
		GameState
	};

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	//Create RenderWindow and variables for manage states
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ 1600, 900 }), "Tanks", sf::Style::None, sf::State::Fullscreen, settings);
	State CurrentGameState = State::MenuState;     //FINAL
	//State CurrentGameState = State::GameState;      //FOR TESTS
	bool changeState;

	//Imgui init
	ImGui::SFML::Init(window);

	//Clock
	sf::Clock deltaClock;

	//States
	Menu* menu = new Menu(window, changeState);     //FINAL
	Game* game = nullptr;

	//Menu* menu = nullptr;                            //FOR TESTS
	//Game* game = new Game(window, changeState);

	//Main game loop
	while (window.isOpen())
	{
		//Choose if we should go to menu or game state
		if (CurrentGameState == State::MenuState)
		{
			menu->input(deltaClock);
		}
		else
		{
			game->input(deltaClock);
		}

		if (CurrentGameState == State::MenuState)
		{
			menu->update();
		}
		else
		{
			game->update(deltaClock);
		}

		//change state if changeState is set on true to the opposite state
		if (changeState == true)
		{
			if (CurrentGameState == State::MenuState)
			{
				delete menu;
				game = new Game(window, changeState);
				CurrentGameState = State::GameState;
			}
			else
			{
				delete game;
				menu = new Menu(window, changeState);
				CurrentGameState = State::MenuState;
			}
			changeState = false;
		}

		if (CurrentGameState == State::MenuState)
		{
			menu->render();
		}
		else
		{
			game->render();
		}
	}

	//imgui shutdown
	ImGui::SFML::Shutdown();
}