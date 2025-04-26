//This is main file .cpp related to Menu state (Menu.h)
#include "Menu.h"

void Menu::LoadRanks()
{
	std::fstream file;
	file.open("Saved/Rank", std::ios::in);

	std::string res;     //here getline will return lines
	std::string sep = "";    //we separate it on different strings
	
	int place = 0;             //place
	while (getline(file, res))   //read lines
	{
		sep.clear();
		int i = 0;
		for (i = 0; i < res.length(); i++)    //load until ' '
		{
			if (res[i] != ' ')
			{
				sep.append(1, res[i]);
			}
			else
			{
				break;
			}
		}
		i++;    //go to next char

		ranks[0][place] = sep;    //save
		sep.clear();

		for (i; i < res.length(); i++)
		{
			if (res[i] != ' ')
			{
				sep.append(1, res[i]);
			}
			else
			{
				break;
			}
		}
		i++;

		ranks[1][place] = sep;
		sep.clear();

		for (i; i < res.length(); i++)
		{
			if (res[i] != ' ')
			{
				sep.append(1, res[i]);
			}
			else
			{
				break;
			}
		}

		ranks[2][place] = sep;
		sep.clear();
		place++;
	}
	file.close();
}

//Creates table with ranks
void Menu::ShowRanks(float YPos, float height)
{
	ImGui::SetNextWindowSize(ImVec2(1100, height));
	ImGui::SetNextWindowPos(ImVec2(static_cast<float>(WindowXSize / 2) - 550, YPos));
	ImGui::Begin("ScoreTables", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	if (ImGui::BeginTable("Scores", 3), ImGuiTableFlags_Borders, ImGuiTableFlags_BordersInner)
	{
		for (int row = 0; row <= 10; row++)
		{
			ImGui::TableNextRow();
			if (row == 0)
			{
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Nick");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("Score");
				ImGui::TableSetColumnIndex(2);
				ImGui::Text("Level");
				ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(150, 150, 150, 255));
			}
			else
			{
				for (int column = 0; column < 3; column++)
				{
					ImGui::TableSetColumnIndex(column);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(190, 190, 190, 205));
					ImGui::Text("%s ", ranks[column][row - 1].c_str());
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::End();
}

//ImGui Section
//Patterns
void Menu::ButtonPattern(ImVec2 WindowPosition, ShowScreen NextScreen, std::string WindowTitle, std::string WindowText, int LevelNumber = 1)
{
	//Button Pattern
	
	//ImGui WindowSettings
	ImGui::SetNextWindowPos(WindowPosition);
	ImGui::Begin(WindowTitle.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowSize(ImVec2{ ButtonDefaultXSize, ButtonDefaultYSize });
	if (ImGui::Button(WindowText.c_str(), ImVec2{static_cast<float>(ButtonDefaultXSize * 0.95), static_cast<float>(ButtonDefaultYSize * 0.84)}))
	{
		//"Game" and "None" from enum inform us to start game level or quick game
		if (NextScreen == ShowScreen::Game)
		{
			level = LevelNumber;
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

void Menu::BackgroundPattern(ImVec2 BackgroundPosition, ImVec2 BackgrondSize, std::string Title)
{
	//Partially transparent background pattern
	ImGui::SetNextWindowPos(BackgroundPosition);
	ImGui::SetNextWindowSize(BackgrondSize);
	ImGui::SetNextWindowBgAlpha(0.45);
	ImGui::Begin("Backgrouynd", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::End();
}

//Screen design
//Each screen use patterns with appropriate parameters
void Menu::MainMenuScheme()
{
	float YPosition = 100;
	YPosition += ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Levels, "PlayButton", "Play");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Ranks, "Ranks", "Ranks");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Options, "Options", "Options");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::AreYouSure, "ExitButton", "Exit");
	TextPattern(ImVec2{ 0, 825 }, "Version", "v.1.1.0a");
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
	BackgroundPattern(ImVec2(static_cast<float>(WindowXSize / 2) - 550, 175), ImVec2(1100, 425), "Background");

	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 200 }, "Creator", "This game was made by Miki18");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 300 }, "Music", "Music is from Kevin MacLeod");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 400 }, "Sound", "Sound is from SOUNDFX FREE");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 500 }, "Title", "Title is from TextCraft");
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::Options, "Back", "Back");
}

void Menu::RanksScheme()
{
	ShowRanks(200, 450);
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::MainMenu, "Back", "Back");
}

void Menu::OptionsScheme()
{
	float YPosition = 100;
	YPosition += ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Credits, "Credits", "Credits");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Settings, "Settings", "Settings");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::Tips, "Tips", "Tips");
	YPosition += ButtonDefaultYSize + ((WindowYSize - 100) - (ButtonDefaultYSize * 4)) / 5;
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, YPosition }, ShowScreen::MainMenu, "Back", "Back");
}

void Menu::SettingsScheme()
{
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 200, 200 }, "Movement", "RMB - Move");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 200, 300 }, "Shoot", "LMB - Shoot");
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::Options, "Back", "Back");

	ImGui::SetNextWindowPos(ImVec2(static_cast<float>(WindowXSize / 2) - 250, 450));
	ImGui::Begin("CheckBox", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Checkbox("Music", &RunMusic))
	{
		if (RunMusic == true)
		{
			music.play();
		}
		else
		{
			music.stop();
		}
	}
	ImGui::SameLine();
	ImGui::Checkbox("Sound", &RunSound);
	ImGui::End();
}

void Menu::TipsScheme()
{
	BackgroundPattern(ImVec2(static_cast<float>(WindowXSize / 2) - 550, 175), ImVec2(1100, 425), "Background");

	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 200 }, "YourTank", "Your tank has yellow bullets");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 300 }, "EnemyTank", "Enemy tanks have red bullets");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 400 }, "PowerUps", "Round objects are Power Ups");
	TextPattern(ImVec2{ static_cast<float>(WindowXSize / 2) - 500, 500 }, "Points", "Objects with '1' are points");
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::Options, "Back", "Back");
}

void Menu::LevelsScheme()
{
	TextPattern(ImVec2(WindowXSize / 2 - 200, 150), "Select Level", "Select Level");
	float XPosition = 0;
	XPosition += (WindowXSize - (ButtonDefaultXSize * 2)) / 7 * 3;
	ButtonPattern(ImVec2{ XPosition, 300 }, ShowScreen::Game, "Level1", "Level 1", 1);
	XPosition += ButtonDefaultXSize + (WindowXSize - (ButtonDefaultXSize * 2)) / 7;
	ButtonPattern(ImVec2{ XPosition, 300 }, ShowScreen::Game, "Level2", "Level 2", 2);
	XPosition = (WindowXSize - (ButtonDefaultXSize * 2)) / 7 * 3;
	ButtonPattern(ImVec2{ XPosition, 450 }, ShowScreen::Game, "Level3", "Level 3", 3);
	XPosition += ButtonDefaultXSize + (WindowXSize - (ButtonDefaultXSize * 2)) / 7;
	ButtonPattern(ImVec2{ XPosition, 450 }, ShowScreen::Game, "Level4", "Level 4", 4);
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 600 }, ShowScreen::Game, "Random", "Random", 5);
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::MainMenu, "Back", "Back");

	//Choose color
	ImGui::SetNextWindowSize(ImVec2(200, 250));
	ImGui::SetNextWindowPos(ImVec2(0, 450));
	ImGui::SetNextWindowBgAlpha(0.0);
	ImGui::Begin("Choose Col", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::SliderInt(" ", &G, 0, 255, "G");
	ImGui::SliderInt("  ", &B, 0, 255, "B");
	ImGui::End();

	window.draw(rectangle);
	circle.setFillColor(sf::Color(0, (uint8_t)G, (uint8_t)B, 255));   //update color
	window.draw(circle);
}

void Menu::SaveScoreScheme()
{
	static char PlayerName[11] = { 0 };   //for insert name (no longer than 10)   static to keep value
	TextPattern(ImVec2(WindowXSize / 2 - 600, 300), "Congrats", "Congratulations! You are top 10!");
	TextPattern(ImVec2(WindowXSize / 2 - 300, 400), "Insert", "Insert your name");
	ImGui::SetNextWindowSize(ImVec2(400, 200));
	ImGui::SetNextWindowPos(ImVec2(WindowXSize / 2 - 150, 500));
	ImGui::Begin("Name", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::InputText("##", PlayerName, 11);      // '##' will not be shown next to input field
	ImGui::End();

	//Button - but in this case a very specyfic button is needed, so this screen will not use typical button pattern
	ImGui::SetNextWindowPos(ImVec2( WindowXSize / 2 - ButtonDefaultXSize / 2, 750 ));
	ImGui::Begin("Done", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowSize(ImVec2{ ButtonDefaultXSize, ButtonDefaultYSize });
	if (ImGui::Button("Done", ImVec2{static_cast<float>(ButtonDefaultXSize * 0.95), static_cast<float>(ButtonDefaultYSize * 0.84)}))
	{
		std::string Name = PlayerName;
		if (!Name.empty())    //Name has to have at least one char
		{
			bool IsOk = true;
			for (int i = 0; i < Name.length(); i++)
			{
				if (Name[i] == ' ')    //Name can't have space
				{
					IsOk = false;
					break;
				}
			}

			if (IsOk)
			{
				//Update ranks
				//No need to check 10th place, because if player see that screen that means he has bigger score than 10th place (we checked it earlier)
				for (int i = 8; i >= 0; i--)
				{
					if (YourLastScore > stoi(ranks[1][i]))     //if your score is bigger than we move i-th score down
					{
						ranks[0][i + 1] = ranks[0][i];
						ranks[1][i + 1] = ranks[1][i];
						ranks[2][i + 1] = ranks[2][i];

						if (i == 0)       //in case if player got 1st place
						{
							ranks[0][i] = Name;
							ranks[1][i] = std::to_string(YourLastScore);
							if (level == 5)
							{
								ranks[2][i] = "R";
							}
							else
							{
								ranks[2][i] = std::to_string(level);
							}
						}
					}
					else      //if not than write player's score to i-1 th position
					{
						ranks[0][i + 1] = Name;
						ranks[1][i + 1] = std::to_string(YourLastScore);
						if (level == 5)
						{
							ranks[2][i + 1] = "R";
						}
						else
						{
							ranks[2][i + 1] = std::to_string(level);
						}
						break;
					}
				}

				std::fstream file;
				file.open("Saved/Rank", std::ios::out);   //we overwrite the file
				for (int i = 0; i < 10; i++)
				{
					file << ranks[0][i] << " " << ranks[1][i] << " " << ranks[2][i] << "\n";
				}
				file.close();
				memset(PlayerName, 0, sizeof(PlayerName));
				showscreen = ShowScreen::End;
			}
		}
	}
	ImGui::End();
}

void Menu::EndScheme()
{
	ShowRanks(200, 350);
	TextPattern(ImVec2(static_cast<float>(WindowXSize / 2) - 250, 600), "YourScore", "Your Score: " + std::to_string(YourLastScore));
	ButtonPattern(ImVec2{ WindowXSize / 2 - ButtonDefaultXSize / 2, 750 }, ShowScreen::MainMenu, "MainMenu", "Back");
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
	else if (showscreen == ShowScreen::Settings)
	{
		SettingsScheme();
	}
	else if (showscreen == ShowScreen::Tips)
	{
		TipsScheme();
	}
	else if (showscreen == ShowScreen::Levels)
	{
		LevelsScheme();
	}
	else if (showscreen == ShowScreen::SaveScore)
	{
		SaveScoreScheme();
	}
	else if (showscreen == ShowScreen::End)
	{
		EndScheme();
	}
}

//constructor
Menu::Menu(sf::RenderWindow& window, bool& changeState, int& level, int& YourLastScore, bool MainMenu, int& G, int& B, bool& RunMusic, bool& RunSound): window(window), changeState(changeState), level(level), YourLastScore(YourLastScore), backgroundtex("Resources/background.png"), backgroundsprite(backgroundtex), titletex("Resources/Title.png"), titlesprite(titletex), G(G), B(B), RunMusic(RunMusic), RunSound(RunSound)
{
	//set title sprite position
	titlesprite.setPosition(sf::Vector2f(WindowXSize/2 - 250, 40));
	//set font scale
	ImGui::GetIO().FontGlobalScale = 5;

	LoadRanks();

	//Imgui WindowStyle
	style.Colors[ImGuiCol_Button] = ImVec4(0.75f, 0.75f, 0.75f, 0.8f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);

	//Set visualization parameters
	//This is very similar to this what is in Player class constructor
	circle.setRadius(20.0f);
	circle.setFillColor(sf::Color{ 0,(uint8_t) G, (uint8_t) B, 255 });
	circle.setOutlineThickness(5.0f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition(sf::Vector2f(80, 400));

	//15 and 40 were swapped to change rotation of barrel
	rectangle.setSize(sf::Vector2f(15, 40));
	rectangle.setFillColor(sf::Color{ 128, 128, 128, 255 });
	rectangle.setOutlineThickness(5.0f);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOrigin(sf::Vector2f(7.5, 0));
	rectangle.setPosition(sf::Vector2f(80, 400));

	//Start music
	music.openFromFile("Music/Polkka.mp3");
	music.setLooping(true);

	if (RunMusic == true)
	{
		music.play();
	}

	//Choose starter screen
	if (MainMenu)
	{
		showscreen = ShowScreen::MainMenu;
	}
	else
	{
		if (stoi(ranks[1][9]) < YourLastScore)
		{
			showscreen = ShowScreen::SaveScore;
		}
		else
		{
			showscreen = ShowScreen::End;
		}
	}
}


//input, update and render

//Input - it handles events and player inputs
void Menu::input()
{
	while (const auto event = window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(window, *event);
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}

	ImGui::SFML::Update(window, deltaClock.getElapsedTime());
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