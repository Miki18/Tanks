//includes
#pragma once
#include "../Headers.h"

class Menu
{
	private:
		//Show Screen - each enum is related to specyfic screen such as main menu, level select etc
		enum ShowScreen
		{
			MainMenu,      //MainMenu
			AreYouSure,    //Question when player wants to quit
			Credits,      //Shows credits
			Ranks,         //Show rank
			Options,       //Options
			Controls,      //Show how to control your tank
			Tips,          //advice for player/how to play
			Levels,        //select level
			SaveScore,      //player will see it when he gets high score (when he will be in top 10)
			End,           //player will see it after game
			None,    //2 last enums (None and Game) are not related to specyfic screen
			Game	//They are variables that trigger specyfic action
		};
		//variables for state manage
		sf::RenderWindow& window;
		bool& changeState;
		int& level;
		int& YourLastScore;

		//Time
		sf::Clock deltaClock;

		//Constants
		const int WindowXSize = 1600;
		const int WindowYSize = 900;

		const float ButtonDefaultXSize = 300;
		const float ButtonDefaultYSize = 100;
		
		//ImGui text style
		ImGuiStyle& style = ImGui::GetStyle();

		//sprites with textures
		sf::Texture backgroundtex;
		sf::Sprite backgroundsprite;
		sf::Texture titletex;
		sf::Sprite titlesprite;

		//We start from MainMenu
		ShowScreen showscreen = MainMenu;

		//Load ranks when starts Menu
		void LoadRanks();
		std::string ranks[3][10];
		void ShowRanks(float YPos, float height);

		//ImGui Section
		//Patterns
		void ButtonPattern(ImVec2 WindowPosition, ShowScreen NextScreen, std::string Title, std::string WindowText, int LevelNumber);
		void TextPattern(ImVec2 TextPosition, std::string TextTitle, std::string Text);
		//Screen design
		void MainMenuScheme();
		void AreYouSureScheme();
		void CreditsScheme();
		void RanksScheme();
		void OptionsScheme();
		void ControlsScheme();
		void TipsScheme();
		void LevelsScheme();
		void SaveScoreScheme();
		void EndScheme();

		//Draw a proper screen
		void ImGuiDraw();

	public:
		//constructor
		Menu(sf::RenderWindow& window, bool& changeState, int& level, int& YourLastScore, bool MainMenu);

		//input, update, render
		void input();
		void update();
		void render();
};

