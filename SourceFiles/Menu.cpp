//This is main file .cpp related to Menu state (Menu.h)
#include "../Headerfiles/Menu.h"

//ImGui Section
void Menu::ImGuiDraw()
{
	PlayButton(ImVec2{100, 200});
	ExitButton(ImVec2{ 400, 500 });
}

//constructor
Menu::Menu(sf::RenderWindow& window, bool& changeState): window(window), changeState(changeState)
{
	
}


//input, update and render

//Input - it handles events and player inputs
void Menu::input(sf::Clock deltaClock)
{
	while (const auto event = window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(window, *event);
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}

	ImGui::SFML::Update(window, deltaClock.restart());
}

//update - update menu's logic
void Menu::update()
{

}

//render - render objects on the screen
void Menu::render()
{
	//here clear -> draw -> display system is used
	window.clear(sf::Color::Cyan);
	ImGuiDraw();
	ImGui::SFML::Render(window);
	window.display();
}