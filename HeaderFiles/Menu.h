//includes
#pragma once
#include "../Headerfiles/Headers.h"

class Menu
{
	private:
		//variables for state manage
		sf::RenderWindow& window;
		bool& changeState;
		const int WindowXSize = 1600;
		const int WindowYSize = 900;

		const float ButtonDefaultXSize = 300;
		const float ButtonDefaultYSize = 150;
		
		ImGuiStyle& style = ImGui::GetStyle();

		//ImGui Section
		//Buttons design (in ImGuiMenuButtons.cpp)
		void PlayButton(ImVec2 WindowPosition);
		void ExitButton(ImVec2 WindowPosition);

		//Screen design
		void DefaultButtonSettings();
		void MainMenuScheme();
		void ImGuiDraw();

	public:
		//constructor
		Menu(sf::RenderWindow& window, bool& changeState);

		//input, update, render
		void input(sf::Clock deltaClock);
		void update();
		void render();
};

