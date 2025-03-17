#include "../Headerfiles/Menu.h"

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
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				changeState = true;
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
	window.clear(sf::Color::Blue);
	ImGui::SFML::Render(window);
	window.display();
}