//includes
#pragma once
#include "../Headerfiles/Headers.h"

class Menu
{
	private:
		//Show Screen - each enum is related to specyfic screen such as main menu, level select etc
		enum ShowScreen
		{
			MainMenu,
			AreYouSure,
			None,    //2 last enums (None and Game) are not related to specyfic screen
			Game	//They are variables that trigger specyfic action
		};
		//variables for state manage
		sf::RenderWindow& window;
		bool& changeState;
		const int WindowXSize = 1600;
		const int WindowYSize = 900;

		const float ButtonDefaultXSize = 300;
		const float ButtonDefaultYSize = 150;
		
		ImGuiStyle& style = ImGui::GetStyle();

		ShowScreen showscreen = MainMenu;
		//ImGui Section
		//Buttons design (in ImGuiMenuButtons.cpp)
		//MainMenu
		void ButtonScheme(ImVec2 WindowPosition, ShowScreen NextScreen, std::string Title, std::string WindowText);
		//Screen design
		void MainMenuScheme();
		void AreYouSureScheme();
		void ImGuiDraw();

	public:
		//constructor
		Menu(sf::RenderWindow& window, bool& changeState);

		//input, update, render
		void input(sf::Clock deltaClock);
		void update();
		void render();
};

