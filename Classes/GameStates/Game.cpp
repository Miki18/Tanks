#include "Game.h"

//load and create level
void Game::LoadLevel(int levelNumber)
{
	if (levelNumber == 5)
	{
		//generate level
		//9x16 - this is centre of the map (more or less)
		walls.emplace_back(sf::Vector2f(25 + 16 * 50, 25 + 9 * 50));
		int up = rand() % 6;
		int down = rand() % 6;
		int left = rand() % 11;
		int right = rand() % 11;
		for (int i = 1; i <= up; i++)
		{
			walls.emplace_back(sf::Vector2f(25 + 16 * 50, 25 + 9 * 50 + i * 50));
		}

		for (int i = 1; i <= down; i++)
		{
			walls.emplace_back(sf::Vector2f(25 + 16 * 50, 25 + 9 * 50 - i * 50));
		}

		for (int i = 1; i <= left; i++)
		{
			walls.emplace_back(sf::Vector2f(25 + 16 * 50 - i * 50, 25 + 9 * 50));
		}

		for (int i = 1; i <= right; i++)
		{
			walls.emplace_back(sf::Vector2f(25 + 16 * 50 + i * 50, 25 + 9 * 50));
		}
	}
	else
	{
		//load level
		std::ifstream file;
		std::string filename = "Levels/level" + std::to_string(levelNumber);
		file.open(filename, std::ios::in);
		if (!file.good())
		{
			window.close();
			exit(1);
		}
		
		std::string line;

		for (int x = 0; x < 18; x++)
		{
			getline(file,line);
			for (int y = 0; y < line.length(); y++)
			{
				if (line[y] == 'W')
				{
					walls.emplace_back(sf::Vector2f(25 + y * 50, 25 + x * 50));
				}
			}
		}
	}
}

//Constructor
Game::Game(sf::RenderWindow& window, bool& changeState, int& level) : window(window), changeState(changeState), level(level), player(sf::Vector2f(0, 0)), CoinText("Resources/coin.png")
{
	srand(time(NULL));
	LoadLevel(level);
	CoinText.setSmooth(false);
}


//input, update and render

//Input - it handles events and player inputs
void Game::input()
{
	while (const auto event = window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(window, *event);
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}

		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (keyPressed->button == sf::Mouse::Button::Right)
			{
				MovePlayer = true;
			}

			if (keyPressed->button == sf::Mouse::Button::Left)
			{
				if (TimeSincePlayerShoot > player.getCooldown())
				{
					sf::Vector2f Pos = player.getPosition();
					bullets.emplace_back(Pos, CurrentMousePos, WindowXSize, WindowYSize);
					TimeSincePlayerShoot = 0.0f;
				}
			}
		}

		if (const auto* keyReleased = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (keyReleased->button == sf::Mouse::Button::Right)
			{
				MovePlayer = false;
			}
		}
	}

	ImGui::SFML::Update(window, deltaClock.getElapsedTime());
}

//update - update game's logic
void Game::update()
{
	//Update Time and Mouse Position
	float dt = deltaClock.restart().asSeconds();
	CurrentMousePos = window.mapPixelToCoords(sf::Mouse::getPosition());

	//Player move
	player.TransformPlayer(CurrentMousePos, WindowXSize, WindowYSize, dt, MovePlayer);

	//Player can't go outside
	if (player.getPosition().x < player.getPlayerRadius())
	{
		player.SetPlayerXPosition(player.getPlayerRadius());
	}
	else if (player.getPosition().x > WindowXSize - player.getPlayerRadius())
	{
		player.SetPlayerXPosition(WindowXSize - player.getPlayerRadius());
	}

	if (player.getPosition().y < player.getPlayerRadius())
	{
		player.SetPlayerYPosition(player.getPlayerRadius());
	}
	else if (player.getPosition().y > WindowYSize - player.getPlayerRadius())
	{
		player.SetPlayerYPosition(WindowYSize - player.getPlayerRadius());
	}

	//bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].MoveBullet(dt);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].CheckBullet())
		{
			bullets.erase(bullets.begin() + i);
		}
	}

	//Coins spawning (every 3 secons and no more than 10)
	TimeUntilCoinSpawn = TimeUntilCoinSpawn - dt;
	if (TimeUntilCoinSpawn < 0.0f and coins.size() < 10)
	{
		int PosX = rand() % 18;
		int PosY = rand() % 32;
		bool CanSpawn = true;

		for (int i = 0; i < walls.size(); i++)
		{
			if (walls[i].getPosition() == sf::Vector2f(25 + PosX * 50, 25 + PosY * 50))
			{
				CanSpawn = false;
				break;
			}
		}

		if (CanSpawn == true)
		{
			Coin coin(CoinText, sf::Vector2f(rand()%WindowXSize, rand()%WindowYSize));
			coins.emplace_back(coin);
		}
		else
		{
			//lower X or Y value and try again
		}
		TimeUntilCoinSpawn = 5.0f;
	}

	//Check walls collision
	for (int i = 0; i < walls.size(); i++)
	{
		if (player.getPosition().x > walls[i].getPosition().x - walls[i].getWallSize()/2 and player.getPosition().x < walls[i].getPosition().x + walls[i].getWallSize()/2)
		{
			if (player.getPosition().y > walls[i].getPosition().y)
			{
				if (player.getPosition().y - walls[i].getPosition().y < player.getPlayerRadius() + walls[i].getWallSize()/2)
				{
					player.SetPlayerYPosition(walls[i].getPosition().y + player.getPlayerRadius() + walls[i].getWallSize()/2);
				}
			}
			else
			{
				if (walls[i].getPosition().y - player.getPosition().y < player.getPlayerRadius() + walls[i].getWallSize()/2)
				{
					player.SetPlayerYPosition(walls[i].getPosition().y - player.getPlayerRadius() - walls[i].getWallSize()/2);
				}
			}
		}

		if (player.getPosition().y > walls[i].getPosition().y - walls[i].getWallSize() / 2 and player.getPosition().y < walls[i].getPosition().y + walls[i].getWallSize() / 2)
		{
			if (player.getPosition().x > walls[i].getPosition().x)
			{
				if (player.getPosition().x - walls[i].getPosition().x < player.getPlayerRadius() + walls[i].getWallSize() / 2)
				{
					player.SetPlayerXPosition(walls[i].getPosition().x + player.getPlayerRadius() + walls[i].getWallSize() / 2);
				}
			}
			else
			{
				if (walls[i].getPosition().x - player.getPosition().x < player.getPlayerRadius() + walls[i].getWallSize() / 2)
				{
					player.SetPlayerXPosition(walls[i].getPosition().x - player.getPlayerRadius() - walls[i].getWallSize() / 2);
				}
			}
		}

		for (int u = 0; u < bullets.size(); u++)
		{
			if (sqrt(pow((bullets[u].getBulletPosition().x - walls[i].getPosition().x), 2) + pow((bullets[u].getBulletPosition().y - walls[i].getPosition().y), 2)) < bullets[u].getBulletSize() + walls[i].getWallSize() / 2)
			{
				bullets.erase(bullets.begin() + u);
			}
		}
	}

	for (int i = 0; i < coins.size(); i++)
	{
		if (sqrt(pow((coins[i].getPosition().x - player.getPosition().x), 2) + pow((coins[i].getPosition().y - player.getPosition().y), 2) < player.getPlayerRadius() * 2))
		{
			player.AddPoint();
			coins.erase(coins.begin() + i);
		}
	}

	TimeSincePlayerShoot = TimeSincePlayerShoot + dt;
	printf("%f\n", dt);
}

//render - render objects on the screen
void Game::render()
{
	//here clear -> draw -> display system is used
	window.clear(sf::Color{0,153, 76, 255});
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].DrawCoin(window);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].DrawBullet(window);
	}
	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].DrawWall(window);
	}
	player.DrawPlayer(window);
	ImGui::Begin("Window");
	ImGui::Text("%i %i", player.getPoints(), player.getHealth());
	ImGui::End();
	ImGui::SFML::Render(window);
	window.display();
}