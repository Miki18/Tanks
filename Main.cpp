//	Tanks
//	Game was made by Miki18
// 
//includes; Headers has include from imgui, sfml and others that are needed in different files
//Menu.h and Game.h are classes
#include "Headers.h"
#include "Classes/GameStates/Menu.h"
#include "Classes/GameStates/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//State Enum
	enum State
	{
		MenuState,
		GameState
	};

	//Setting antialliasing
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	//Create RenderWindow and variables for manage states (and those which has to be between states)
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ 1600, 900 }), "Tanks", sf::Style::None, sf::State::Fullscreen, settings);
	State CurrentGameState = State::MenuState;
	bool changeState;
	int YourLastScore = 0;

	//To select level
	//Level 1 is default
	int level = 1;

	//Player color (RGB) - R value will always be 0
	//G = 100 and B = 0 <- default values
	int G = 100;
	int B = 0;

	//Music variables
	bool RunMusic = true;
	bool RunSound = true;

	//Imgui init
	ImGui::SFML::Init(window);

	//States
	Menu* menu = new Menu(window, changeState, level, YourLastScore, true, G, B, RunMusic, RunSound);     //FINAL  //Last argument tell us if we should start with MainMenu or End screen
	Game* game = nullptr;

	//Main game loop
	while (window.isOpen())
	{
		//Choose if we should go to menu or game state
		if (CurrentGameState == State::MenuState)
		{
			menu->input();
		}
		else
		{
			game->input();
		}

		if (CurrentGameState == State::MenuState)
		{
			menu->update();
		}
		else
		{
			game->update();
		}

		//change state if changeState is set on true to the opposite state
		if (changeState == true)
		{
			if (CurrentGameState == State::MenuState)
			{
				delete menu;
				YourLastScore = 0;       //reset
				game = new Game(window, changeState, level, YourLastScore, G, B, RunMusic, RunSound);
				CurrentGameState = State::GameState;
			}
			else
			{
				delete game;
				menu = new Menu(window, changeState, level, YourLastScore, false, G, B, RunMusic, RunSound);
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