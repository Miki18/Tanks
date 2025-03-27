//includes
#pragma once
#include "../Headers.h"

class Menu
{
	private:
		//Show Screen - each enum is related to specyfic screen such as main menu, level select etc
		enum ShowScreen
		{
			MainMenu,
			AreYouSure,
			Credits,
			Ranks,
			Options,
			Controls,
			Tips,
			None,    //2 last enums (None and Game) are not related to specyfic screen
			Game	//They are variables that trigger specyfic action
		};
		//variables for state manage
		sf::RenderWindow& window;
		bool& changeState;

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

		//ImGui Section
		//Patterns
		void ButtonPattern(ImVec2 WindowPosition, ShowScreen NextScreen, std::string Title, std::string WindowText);
		void TextPattern(ImVec2 TextPosition, std::string TextTitle, std::string Text);
		//Screen design
		void MainMenuScheme();
		void AreYouSureScheme();
		void CreditsScheme();
		void RanksScheme();
		void OptionsScheme();
		void ControlsScheme();
		void TipsScheme();

		//Draw a proper screen
		void ImGuiDraw();

	public:
		//constructor
		Menu(sf::RenderWindow& window, bool& changeState);

		//input, update, render
		void input();
		void update();
		void render();
};

