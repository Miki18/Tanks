//This is main file .cpp related to Menu state (Menu.h)
#include "../Headerfiles/Menu.h"

//ImGui Section
void Menu::ButtonScheme(ImVec2 WindowPosition, ShowScreen NextScreen, std::string WindowTitle, std::string WindowText)
{
	//Imgui WindowStyle
	style.Colors[ImGuiCol_Button] = ImVec4(0.75f, 0.75f, 0.75f, 0.8f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);

	//ImGui WindowSettings
	ImGui::SetNextWindowPos(WindowPosition);
	ImGui::Begin(WindowTitle.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowSize(ImVec2{ ButtonDefaultXSize, ButtonDefaultYSize });
	if (ImGui::Button(WindowText.c_str(), ImVec2{static_cast<float>(ButtonDefaultXSize * 0.95), static_cast<float>(ButtonDefaultYSize * 0.88)}))
	{
		//"Game" and "None" from enum inform us to start game level or quick game
		if (NextScreen == ShowScreen::Game)
		{
			changeState = true;
		}
		else if (NextScreen == ShowScreen::None)
		{
			window.close();
		}
		else
		{
			showscreen = NextScreen;
		}
	}
	ImGui::End();
}

void Menu::MainMenuScheme()
{
	float YPosition = 0;
	YPosition += (WindowYSize - (ButtonDefaultYSize * 2)) / 3;
	ButtonScheme(ImVec2{ WindowXSize/2 - ButtonDefaultXSize/2, YPosition }, ShowScreen::Game, "PlayButton", "Play");
	YPosition += ButtonDefaultYSize + (WindowYSize - (ButtonDefaultYSize * 2)) / 3;
	ButtonScheme(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::AreYouSure, "ExitButton", "Exit");
}

void Menu::AreYouSureScheme()
{
	float XPosition = 0;
	XPosition += (WindowXSize - (ButtonDefaultXSize * 2)) / 7 * 3;
	ButtonScheme(ImVec2{XPosition, 500}, ShowScreen::None, "YesButton", "Yes");
	XPosition += ButtonDefaultXSize + (WindowXSize - (ButtonDefaultXSize * 2)) / 7;
	ButtonScheme(ImVec2{ XPosition, 500 }, ShowScreen::MainMenu, "NoButton", "No");
}

void Menu::ImGuiDraw()
{
	if (showscreen == ShowScreen::MainMenu)
	{
		MainMenuScheme();
	}
	else if (showscreen == ShowScreen::AreYouSure)
	{
		AreYouSureScheme();
	}
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