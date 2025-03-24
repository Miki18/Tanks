//This is main file .cpp related to Menu state (Menu.h)
#include "Menu.h"

//ImGui Section
//Patterns
void Menu::ButtonPattern(ImVec2 WindowPosition, ShowScreen NextScreen, std::string WindowTitle, std::string WindowText)
{
	//Button Pattern

	//Imgui WindowStyle
	style.Colors[ImGuiCol_Button] = ImVec4(0.75f, 0.75f, 0.75f, 0.8f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);

	//ImGui WindowSettings
	ImGui::SetNextWindowPos(WindowPosition);
	ImGui::Begin(WindowTitle.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowSize(ImVec2{ ButtonDefaultXSize, ButtonDefaultYSize });
	if (ImGui::Button(WindowText.c_str(), ImVec2{static_cast<float>(ButtonDefaultXSize * 0.95), static_cast<float>(ButtonDefaultYSize * 0.84)}))
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

void Menu::TextPattern(ImVec2 TextPosition, std::string TextTitle, std::string Text)
{
	//Text Pattern
	ImGui::SetNextWindowPos(TextPosition);
	ImGui::Begin(TextTitle.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text(Text.c_str());
	ImGui::End();
}

//Screen design
//Each screen use patterns with appropriate parameters
void Menu::MainMenuScheme()
{
	float YPosition = 100;
	YPosition += ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize/2 - ButtonDefaultXSize/2, YPosition }, ShowScreen::Game, "PlayButton", "Play");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Ranks, "Ranks", "Ranks");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Options, "Options", "Options");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::AreYouSure, "ExitButton", "Exit");
}

void Menu::AreYouSureScheme()
{
	TextPattern(ImVec2(WindowXSize / 2 - 200, 250), "AreYouSure", "Are You Sure?");
	float XPosition = 0;
	XPosition += (WindowXSize - (ButtonDefaultXSize * 2)) / 7 * 3;
	ButtonPattern(ImVec2{XPosition, 600}, ShowScreen::None, "YesButton", "Yes");
	XPosition += ButtonDefaultXSize + (WindowXSize - (ButtonDefaultXSize * 2)) / 7;
	ButtonPattern(ImVec2{ XPosition, 600 }, ShowScreen::MainMenu, "NoButton", "No");
}

void Menu::CreditsScheme()
{
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 200 }, "Creator", "This game was made by Miki18");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 450, 300 }, "Music", "Music from Kevin MacLeod");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 550, 400 }, "Title", "Title was generated with TextCraft");
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::Options, "Back", "Back");
}

void Menu::RanksScheme()
{
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::MainMenu, "Back", "Back");
}

void Menu::OptionsScheme()
{
	float YPosition = 100;
	YPosition += ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Credits, "Credits", "Credits");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Controls, "Controls", "Controls");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Tips, "Tips", "Tips");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::MainMenu, "Back", "Back");
}

void Menu::ControlsScheme()
{
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 200, 200 }, "Movement", "RMB - Move");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 200, 300 }, "Shoot", "LMB - Shoot");
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::Options, "Back", "Back");
}

void Menu::TipsScheme()
{
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 750, 200 }, "YourTank", "Your tank is green and has yellow bullets");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 650, 300 }, "EnemyTank", "Enemy tank is red and has red bullets");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 750, 400 }, "PowerUps", "Round Transparent objects are Power Ups");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 600, 500 }, "Points", "Yellow objects with '1' are points");
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::Options, "Back", "Back");
}

//Choose Screen design based on enum ShowScreen and showscreen value
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
	else if (showscreen == ShowScreen::Credits)
	{
		CreditsScheme();
	}
	else if (showscreen == ShowScreen::Ranks)
	{
		RanksScheme();
	}
	else if (showscreen == ShowScreen::Options)
	{
		OptionsScheme();
	}
	else if (showscreen == ShowScreen::Controls)
	{
		ControlsScheme();
	}
	else if (showscreen == ShowScreen::Tips)
	{
		TipsScheme();
	}
}

//constructor
Menu::Menu(sf::RenderWindow& window, bool& changeState): window(window), changeState(changeState), backgroundtex("Resources/background.png"), backgroundsprite(backgroundtex), titletex("Resources/Title.png"), titlesprite(titletex)
{
	//set title sprite position
	titlesprite.setPosition(sf::Vector2f(WindowXSize/2 - 250, 40));
	//set font scale
	ImGui::GetIO().FontGlobalScale = 5;
}


//input, update and render

//Input - it handles events and player inputs
void Menu::input(sf::Clock &deltaClock)
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
	window.clear();
	window.draw(backgroundsprite);
	window.draw(titlesprite);
	ImGuiDraw();
	ImGui::SFML::Render(window);
	window.display();
}