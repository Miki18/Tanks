#include "Game.h"

//load and create level
//Levels 1 - 4 are loaded from files
//level 5 means player selected "random" option
//On one level there are 32 and 18 places where wall or coin can spawn (1600/50 and 900/50)
void Game::LoadLevel(int levelNumber)
{
	if (levelNumber == 5)
	{
		//generate level
		//9x16 - this is centre of the map (more or less)
		walls.emplace_back(sf::Vector2f(25 + 16 * 50, 25 + 9 * 50));
		int up = rand() % 7;
		int down = rand() % 7;
		int left = rand() % 13;
		int right = rand() % 13;
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


//Functions connected with coins

//Manage coin spawning (measure and control time and coins number)
void Game::CoinSpawningControl(float dt)
{
	//Coins spawning (every 3 secons and no more than 10)
	TimeUntilCoinSpawn = TimeUntilCoinSpawn - dt;
	if (TimeUntilCoinSpawn < 0.0f and coins.size() < 10)
	{
		int PosX = rand() % 32;
		int PosY = rand() % 18;

		SpawnCoinAlgorithm(PosX, PosY, 1);

		TimeUntilCoinSpawn = 5.0f;
	}
	else if (TimeUntilCoinSpawn < 0.0f and coins.size() >= 10)
	{
		TimeUntilCoinSpawn = 5.0f;
	}
}

//Check if coin doesn't collide with wall and spawns if not
bool Game::SpawnCoin(int PosX, int PosY)
{
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].getPosition() == sf::Vector2f(25 + PosX * 50, 25 + PosY * 50))
		{
			return false;
		}
	}

	Coin coin(CoinText, sf::Vector2f(25 + PosX * 50, 25 + PosY * 50));
	coins.emplace_back(coin);
	return true;
}

//Spawn coin
//PosX and PosY is a place where we check if we can spawn coin
//Iteration is a recursion's number
void Game::SpawnCoinAlgorithm(int PosX, int PosY, int Iteration = 0)
{
	//In first iteration we check one place
	if (Iteration == 0)
	{
		if (!SpawnCoin(PosX, PosY))
		{
			SpawnCoinAlgorithm(PosX, PosY, 1);
		}
	}
	else
	{
		//In other iteration we change place and check left, right, top and down
		//"Iteration" variable shows how far we should move
		int BiggerPosX = PosX + Iteration;
		if (BiggerPosX > 32)
		{
			BiggerPosX = 32;
		}

		if (SpawnCoin(BiggerPosX, PosY))
		{
			return;
		}

		int SmallerPosX = PosX - Iteration;
		if (SmallerPosX < 0)
		{
			SmallerPosX = 0;
		}

		if (SpawnCoin(SmallerPosX, PosY))
		{
			return;
		}
		
		int BiggerPosY = PosY + Iteration;
		if (BiggerPosY > 18)
		{
			BiggerPosY = 18;
		}

		if (SpawnCoin(PosX, BiggerPosY))
		{
			return;
		}

		int SmallerPosY = PosY - Iteration;
		if (SmallerPosY < 0)
		{
			SmallerPosY = 0;
		}

		if (SpawnCoin(PosX, SmallerPosY))
		{
			return;
		}

		//In every iteration we increase "Iteration" more and more, so we check futher and futher places
		Iteration++;
		//In case if program couldn't find a free space, recursion will be cut off to not fall in endless loop
		if (Iteration > 30)
		{
			return;
		}
		else
		{
			SpawnCoinAlgorithm(PosX, PosY, Iteration);
		}
	}
}


//Collision functions
void Game::Player_CoinsCollision()
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (sqrt(pow((coins[i].getPosition().x - player.getPosition().x), 2) + pow((coins[i].getPosition().y - player.getPosition().y), 2)) < player.getPlayerRadius() * 1.5)
		{
			Score++;
			coins.erase(coins.begin() + i);
		}
	}
}

//Collision between Player and walls
void Game::Wall_PlayerCollision(int wall_number)
{
	if (player.getPosition().x > walls[wall_number].getPosition().x - walls[wall_number].getWallSize() / 2 and player.getPosition().x < walls[wall_number].getPosition().x + walls[wall_number].getWallSize() / 2)
	{
		if (player.getPosition().y > walls[wall_number].getPosition().y)
		{
			if (player.getPosition().y - walls[wall_number].getPosition().y < player.getPlayerRadius() + walls[wall_number].getWallSize() / 2)
			{
				player.SetPlayerYPosition(walls[wall_number].getPosition().y + player.getPlayerRadius() + walls[wall_number].getWallSize() / 2);
			}
		}
		else
		{
			if (walls[wall_number].getPosition().y - player.getPosition().y < player.getPlayerRadius() + walls[wall_number].getWallSize() / 2)
			{
				player.SetPlayerYPosition(walls[wall_number].getPosition().y - player.getPlayerRadius() - walls[wall_number].getWallSize() / 2);
			}
		}
	}

	if (player.getPosition().y > walls[wall_number].getPosition().y - walls[wall_number].getWallSize() / 2 and player.getPosition().y < walls[wall_number].getPosition().y + walls[wall_number].getWallSize() / 2)
	{
		if (player.getPosition().x > walls[wall_number].getPosition().x)
		{
			if (player.getPosition().x - walls[wall_number].getPosition().x < player.getPlayerRadius() + walls[wall_number].getWallSize() / 2)
			{
				player.SetPlayerXPosition(walls[wall_number].getPosition().x + player.getPlayerRadius() + walls[wall_number].getWallSize() / 2);
			}
		}
		else
		{
			if (walls[wall_number].getPosition().x - player.getPosition().x < player.getPlayerRadius() + walls[wall_number].getWallSize() / 2)
			{
				player.SetPlayerXPosition(walls[wall_number].getPosition().x - player.getPlayerRadius() - walls[wall_number].getWallSize() / 2);
			}
		}
	}
}

//Collision between bullets and walls
void Game::Wall_BulletCollision(int wall_number)
{
	//Bullet collision with walls
	for (int i = 0; i < bullets.size(); i++)
	{
		float distanceX = bullets[i].getBulletPosition().x - std::max(walls[wall_number].getPosition().x - walls[wall_number].getWallSize() / 2, std::min(bullets[i].getBulletPosition().x, walls[wall_number].getPosition().x + walls[wall_number].getWallSize() / 2));
		float distanceY = bullets[i].getBulletPosition().y - std::max(walls[wall_number].getPosition().y - walls[wall_number].getWallSize() / 2, std::min(bullets[i].getBulletPosition().y, walls[wall_number].getPosition().y + walls[wall_number].getWallSize() / 2));
		float distanceSquared = distanceX * distanceX + distanceY * distanceY;

		if (distanceSquared < (bullets[i].getBulletSize() * bullets[i].getBulletSize())) {
			bullets.erase(bullets.begin() + i);
		}
	}
}


//ImGui Part

//Main imgui render function
void Game::ImGuiRender()
{
	ImGuiHeathAndPoinsWindow();
}

//Top left window with Points and Health
void Game::ImGuiHeathAndPoinsWindow()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 3.0f);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowBgAlpha(0.33);
	ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Points: %i", Score);
	ImGui::Text("Health: %i", player.getHealth());
	ImGui::End();
	ImGui::PopStyleColor(1);
	ImGui::PopStyleVar(1);
}


//Constructor
//Constructor will load all textures and will store it in memory, so 
//it will not have to be load every time when new object will be created
Game::Game(sf::RenderWindow& window, bool& changeState, int& level, int& Score) : window(window), changeState(changeState), level(level), Score(Score), player(sf::Vector2f(0, 0)), CoinText("Resources/coin.png")
{
	//time
	srand(time(NULL));
	//level
	LoadLevel(level);
	//set texture
	CoinText.setSmooth(false);
	//imgui
	ImGui::GetIO().FontGlobalScale = 1.5;
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

		//Button pressed
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (keyPressed->button == sf::Mouse::Button::Right)
			{
				MovePlayer = true;
			}

			if (keyPressed->button == sf::Mouse::Button::Left)
			{
				if (TimeSincePlayerShoot > player.getCooldown())    //if Time since last player shoot is greater than cooldown than player is allowed to shoot
				{
					sf::Vector2f Pos = player.getPosition();
					bullets.emplace_back(Pos, CurrentMousePos, WindowXSize, WindowYSize);
					TimeSincePlayerShoot = 0.0f;   //reset time
				}
			}

			//FOR TEST ONLY
			if (keyPressed->button == sf::Mouse::Button::Middle)
			{
				Score = 10;
				player.TakeDamage(101);
			}
		}

		//Button released
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

	//bullets move
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].MoveBullet(dt);
	}

	//check if bullets is outside map - if yes than erase
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].CheckBullet())
		{
			bullets.erase(bullets.begin() + i);
		}
	}

	CoinSpawningControl(dt);

	//Check walls collision
	for (int i = 0; i < walls.size(); i++)
	{
		Wall_PlayerCollision(i);
		Wall_BulletCollision(i);
	}

	//Collision with coins
	Player_CoinsCollision();

	//Check if player is alive
	if (player.getHealth() <= 0)
	{
		changeState = true;
	}

	//Increase time since player shoot
	TimeSincePlayerShoot = TimeSincePlayerShoot + dt;
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
	ImGuiRender();
	ImGui::SFML::Render(window);
	window.display();
}