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
void Game::ObjectSpawningControl(float dt)
{
	//Coins spawning (every 3 secons and no more than 10)
	TimeUntilEnemySpawn = TimeUntilEnemySpawn - dt;

	if (coins.size() < 10)
	{
		TimeUntilCoinSpawn = TimeUntilCoinSpawn - dt;
	}

	if (powerups.size() < 5)
	{
		TimeUntilPowerUpSpawn = TimeUntilPowerUpSpawn - dt;
	}

	if (TimeUntilCoinSpawn < 0.0f and coins.size() < 10)
	{
		int PosX = rand() % 32;
		int PosY = rand() % 18;

		SpawnObjectAlgorithm(PosX, PosY, ObjectType::CoinType, 0);

		TimeUntilCoinSpawn = 6.0f;
	}

	if (TimeUntilEnemySpawn < 0.0f and enemies.size() < 14)
	{
		int PosX = rand() % 32;
		int PosY = rand() % 18;

		SpawnObjectAlgorithm(PosX, PosY, ObjectType::EnemyType, 0);

		TimeUntilEnemySpawn = NextEnemySpawnAfter;

		if (NextEnemySpawnAfter >= 4.1f)      //new enemy will spawn faster
		{
			NextEnemySpawnAfter = NextEnemySpawnAfter - 0.2f;
		}
	}
	else if(TimeUntilEnemySpawn < 0.0f)
	{
		//If it is not possible to add other enemy, then reset timer
		TimeUntilEnemySpawn = NextEnemySpawnAfter;
	}

	if (TimeUntilPowerUpSpawn < 0.0f and powerups.size() <= 5)
	{
		int PosX = rand() % 32;
		int PosY = rand() % 18;

		SpawnObjectAlgorithm(PosX, PosY, ObjectType::PowerUpType, 0);

		TimeUntilPowerUpSpawn = rand() % 10 + 5;
	}
}

//Check if coin doesn't collide with wall and spawns if not
bool Game::SpawnObject(int PosX, int PosY, ObjectType Object)
{
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].getPosition() == sf::Vector2f(25 + PosX * 50, 25 + PosY * 50))
		{
			return false;
		}
	}

	//SpawnCoin
	if (Object == ObjectType::CoinType)
	{
		//Check if any coin is here
		for (int i = 0; i < coins.size(); i++)
		{
			if (coins[i].getPosition() == sf::Vector2f(25 + PosX * 50, 25 + PosY * 50))
			{
				//if any coin is in this position then
				return false;
			}
		}

		//if not spawn a new coin
		Coin coin(CoinText, sf::Vector2f(25 + PosX * 50, 25 + PosY * 50));
		coins.emplace_back(coin);
		return true;
	}
	//SpawnEnemy
	else if (Object == ObjectType::EnemyType)
	{
		//when we want to spawn enemy we need to check its distance to player
		float dx = player.getPosition().x - 25 + PosX * 50;
		float dy = player.getPosition().y - 25 + PosY * 50;

		//the distance can't be less than 200
		if (sqrt(pow(dx * dx, 2) + pow(dy * dy, 2)) < 200)
		{
			return false;
		}

		int EnemyType = rand() % 4;
		if (EnemyType == 0 or EnemyType == 1)
		{
			BaseEnemy* enemy = new NormalEnemy(sf::Vector2f(25 + PosX * 50, 25 + PosY * 50));
			enemies.push_back(enemy);
		}
		else if (EnemyType == 2)
		{
			BaseEnemy* enemy = new FastEnemy(sf::Vector2f(25 + PosX * 50, 25 + PosY * 50));
			enemies.push_back(enemy);
		}
		else
		{
			BaseEnemy* enemy = new BigEnemy(sf::Vector2f(25 + PosX * 50, 25 + PosY * 50));
			enemies.push_back(enemy);
		}

		return true;
	}
	else if (Object == ObjectType::PowerUpType)
	{

		//check if any powerup is here
		for (int i = 0; i < powerups.size(); i++)
		{
			//if any powerup is here than return false
			if (powerups[i].getPowerupPos() == sf::Vector2f(25 + PosX * 50, 25 + PosY * 50))
			{
				return false;
			}
		}

		//if there isn't any powerup than spawn a new one
		//Pass only this texture, what will be used in PowerUp class
		int RandomPowerupPick = rand() % 7;
		if (RandomPowerupPick == 0 or RandomPowerupPick == 1 or RandomPowerupPick == 2)
		{
			//Change RandomPowerPick to 0 - 2 value so it matchs with powerup types
			RandomPowerupPick = 0;
			PowerUp powerup(sf::Vector2f(25 + PosX * 50, 25 + PosY * 50), RandomPowerupPick, fastText);
			powerups.emplace_back(powerup);
		}
		else if (RandomPowerupPick == 3 or RandomPowerupPick == 4 or RandomPowerupPick == 5)
		{
			RandomPowerupPick = 1;
			PowerUp powerup(sf::Vector2f(25 + PosX * 50, 25 + PosY * 50), RandomPowerupPick, ballText);
			powerups.emplace_back(powerup);
		}
		else
		{
			RandomPowerupPick = 2;
			PowerUp powerup(sf::Vector2f(25 + PosX * 50, 25 + PosY * 50), RandomPowerupPick, healText);
			powerups.emplace_back(powerup);
		}

		return true;
	}
}

//Spawn coin
//PosX and PosY is a place where we check if we can spawn coin
//Iteration is a recursion's number
void Game::SpawnObjectAlgorithm(int PosX, int PosY, ObjectType Object, int Iteration = 0)
{
	//In first iteration we check one place
	if (Iteration == 0)
	{
		if (!SpawnObject(PosX, PosY, Object))
		{
			SpawnObjectAlgorithm(PosX, PosY, Object, 1);
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

		if (SpawnObject(BiggerPosX, PosY, Object))
		{
			return;
		}

		int SmallerPosX = PosX - Iteration;
		if (SmallerPosX < 0)
		{
			SmallerPosX = 0;
		}

		if (SpawnObject(SmallerPosX, PosY, Object))
		{
			return;
		}
		
		int BiggerPosY = PosY + Iteration;
		if (BiggerPosY > 18)
		{
			BiggerPosY = 18;
		}

		if (SpawnObject(PosX, BiggerPosY, Object))
		{
			return;
		}

		int SmallerPosY = PosY - Iteration;
		if (SmallerPosY < 0)
		{
			SmallerPosY = 0;
		}

		if (SpawnObject(PosX, SmallerPosY, Object))
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
			SpawnObjectAlgorithm(PosX, PosY, Object, Iteration);
		}
	}
}


//Collision functions
void Game::Player_CoinsCollision()
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (sqrt(pow((coins[i].getPosition().x - player.getPosition().x), 2) + pow((coins[i].getPosition().y - player.getPosition().y), 2)) < player.getPlayerRadius() + coins[i].getRadius())
		{
			Score++;
			coins.erase(coins.begin() + i);
			i--;
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
			i--;
		}
	}
}

//Collision between enemies and walls
void Game::Wall_EnemesCollision(int wall_number)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getEnemyPosition().x > walls[wall_number].getPosition().x - walls[wall_number].getWallSize() / 2 and enemies[i]->getEnemyPosition().x < walls[wall_number].getPosition().x + walls[wall_number].getWallSize() / 2)
		{
			if (enemies[i]->getEnemyPosition().y > walls[wall_number].getPosition().y)
			{
				if (enemies[i]->getEnemyPosition().y - walls[wall_number].getPosition().y < enemies[i]->getEnemyRadius() + walls[wall_number].getWallSize() / 2)
				{
					enemies[i]->setYPos(walls[wall_number].getPosition().y + player.getPlayerRadius() + walls[wall_number].getWallSize() / 2);
					enemies[i]->ChooseRandomRotation();
				}
			}
			else
			{
				if (walls[wall_number].getPosition().y - enemies[i]->getEnemyPosition().y < enemies[i]->getEnemyRadius() + walls[wall_number].getWallSize() / 2)
				{
					enemies[i]->setYPos(walls[wall_number].getPosition().y - player.getPlayerRadius() - walls[wall_number].getWallSize() / 2);
					enemies[i]->ChooseRandomRotation();
				}
			}
		}

		if (enemies[i]->getEnemyPosition().y > walls[wall_number].getPosition().y - walls[wall_number].getWallSize() / 2 and enemies[i]->getEnemyPosition().y < walls[wall_number].getPosition().y + walls[wall_number].getWallSize() / 2)
		{
			if (enemies[i]->getEnemyPosition().x > walls[wall_number].getPosition().x)
			{
				if (enemies[i]->getEnemyPosition().x - walls[wall_number].getPosition().x < enemies[i]->getEnemyRadius() + walls[wall_number].getWallSize() / 2)
				{
					enemies[i]->setXPos(walls[wall_number].getPosition().x + player.getPlayerRadius() + walls[wall_number].getWallSize() / 2);
					enemies[i]->ChooseRandomRotation();
				}
			}
			else
			{
				if (walls[wall_number].getPosition().x - enemies[i]->getEnemyPosition().x < enemies[i]->getEnemyRadius() + walls[wall_number].getWallSize() / 2)
				{
					enemies[i]->setXPos(walls[wall_number].getPosition().x - player.getPlayerRadius() - walls[wall_number].getWallSize() / 2);
					enemies[i]->ChooseRandomRotation();
				}
			}
		}
	}
}

void Game::Player_BulletsCollision(int* bulletNum)
{
	if (sqrt(pow(bullets[*bulletNum].getBulletPosition().x - player.getPosition().x, 2) +
		pow(bullets[*bulletNum].getBulletPosition().y - player.getPosition().y, 2)) <
		player.getPlayerRadius() + bullets[*bulletNum].getBulletSize())
	{
		player.TakeDamage(bullets[*bulletNum].getDamage());
		bullets.erase(bullets.begin() + *bulletNum);
		*bulletNum = *bulletNum - 1;
	}
}

void Game::Enemies_BulletsCollision(int* bulletNum)
{
	for (int x = 0; x < enemies.size(); x++)
	{
		if (sqrt(pow(bullets[*bulletNum].getBulletPosition().x - enemies[x]->getEnemyPosition().x, 2) +
			pow(bullets[*bulletNum].getBulletPosition().y - enemies[x]->getEnemyPosition().y, 2)) <
			enemies[x]->getEnemyRadius() + bullets[*bulletNum].getBulletSize())
		{
			enemies[x]->TakeDamage(bullets[*bulletNum].getDamage());
			if (enemies[x]->getEnemyHealth() <= 0)
			{
				enemies.erase(enemies.begin() + x);
				x = x - 1;
			}
			else
			{
				//if enemy not die then it will rotate and check from where bullet comes (because bullets has player's position when he shot, enemy will go in that direction)
				enemies[x]->RotateToPoint(bullets[*bulletNum].getShooterPosition());
			}
			bullets.erase(bullets.begin() + *bulletNum);
			*bulletNum = *bulletNum - 1;
		}
	}
}

void Game::Player_PowerupsCollision()
{
	for (int i = 0; i < powerups.size(); i++)
	{
		if(sqrt(pow(player.getPosition().x - powerups[i].getPowerupPos().x, 2) +
			pow(player.getPosition().y - powerups[i].getPowerupPos().y, 2)) <
				powerups[i].getRadius() + player.getPlayerRadius())
		{
			if (powerups[i].getType() == 0)
			{
				player.GrantPlayerSpeed();
			}
			else if (powerups[i].getType() == 1)
			{
				player.GrantPlayerQuickfire();
			}
			else if (powerups[i].getType() == 2)
			{
				//check if player's health is > 0 to not rise him from dead by accident
				if (player.getHealth() > 0)
				{
					player.RestoreHealth();
				}
			}

			powerups.erase(powerups.begin() + i);
			i--;
		}
	}
}

//This function will check if enemy's vision is blocked by walls
void Game::EnemyVisionLimitedbyWalls(int enemyNum)
{	
	//Player_AI_X_DIFFERENCE will have a player.getPosition().x - enemies[enemyNum]->getEnemyPosition().x value to control if it is 0 or no
	float Player_AI_X_Difference = player.getPosition().x - enemies[enemyNum]->getEnemyPosition().x;

	//if enemy and player are on the same x position
	if (abs(Player_AI_X_Difference) < 0.0001f)
	{
		for (int i = 0; i < walls.size(); i++)
		{
			//check if there is wall between enemy and player
			if ((walls[i].getPosition().x > enemies[enemyNum]->getEnemyPosition().x and walls[i].getPosition().x < player.getPosition().x) or
				(walls[i].getPosition().x < enemies[enemyNum]->getEnemyPosition().x and walls[i].getPosition().x > player.getPosition().x))
			{
				//check if wall is in the same y level (or at least part of the wall)
				if ((walls[i].getPosition().y + walls[i].getWallSize()/2) <= player.getPosition().y and (walls[i].getPosition().y - walls[i].getWallSize()/2) >= player.getPosition().y)
				{
					return;
				}
			}
		}
	}
	else
	{
		float a = (player.getPosition().y - enemies[enemyNum]->getEnemyPosition().y) / Player_AI_X_Difference;

		//in case if a is too close to 0 and game could round it to 0
		if (std::abs(a) < 0.0001)
		{
			if (a < 0)
			{
				a = -0.0001;
			}
			else
			{
				a = 0.0001;
			}
		}

		float b = enemies[enemyNum]->getEnemyPosition().y - a * enemies[enemyNum]->getEnemyPosition().x;

		for (int i = 0; i < walls.size(); i++)
		{
			//Only walls closer than player needs to be checked
			if (sqrt(pow(walls[i].getPosition().x - enemies[enemyNum]->getEnemyPosition().x, 2) + pow(walls[i].getPosition().y - enemies[enemyNum]->getEnemyPosition().y, 2)) >=
				sqrt(pow(player.getPosition().x - enemies[enemyNum]->getEnemyPosition().x, 2) + pow(player.getPosition().y - enemies[enemyNum]->getEnemyPosition().y, 2)))
			{
				continue;
			}

			//get X point
			float wallX = walls[i].getPosition().x - walls[i].getWallSize()/2;
			//Calculate Y on y = a*x + b with wallX
			float wallY = a * wallX + b;
			//if Y is on wall's side than we have a collision
			if (wallY >= walls[i].getPosition().y - walls[i].getWallSize()/2 and
				wallY <= walls[i].getPosition().y + walls[i].getWallSize()/2)
			{
				return;
			}

			wallX = walls[i].getPosition().x + walls[i].getWallSize()/2;
			wallY = a * wallX + b;
			if (wallY >= walls[i].getPosition().y - walls[i].getWallSize() / 2 and
				wallY <= walls[i].getPosition().y + walls[i].getWallSize() / 2)
			{
				return;
			}

			wallY = walls[i].getPosition().y - walls[i].getWallSize()/2;
			wallX = (wallY - b)/a;
			if (wallX >= walls[i].getPosition().x - walls[i].getWallSize() / 2 and
				wallX <= walls[i].getPosition().x + walls[i].getWallSize() / 2)
			{
				return;
			}

			wallY = walls[i].getPosition().y + walls[i].getWallSize() / 2;
			wallX = (wallY - b)/a;
			if (wallX >= walls[i].getPosition().x - walls[i].getWallSize() / 2 and
				wallX <= walls[i].getPosition().x + walls[i].getWallSize() / 2)
			{
				return;
			}
		}
	}

	//when enemy sees player than rotate and shoot
	enemies[enemyNum]->EnemySawPlayer();
	enemies[enemyNum]->RotateToPoint(player.getPosition());
	if (enemies[enemyNum]->getCooldown() <= 0)
	{
		bullets.emplace_back(enemies[enemyNum]->getEnemyPosition(), player.getPosition(), WindowXSize, WindowYSize, enemies[enemyNum]->getDamage(), false, 400);
		enemies[enemyNum]->ResetCooldown();

		if (RunSound == true)
		{
			sound.play();
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
Game::Game(sf::RenderWindow& window, bool& changeState, int& level, int& Score, int G, int B, bool RunMusic, bool RunSound) : window(window), changeState(changeState), level(level), Score(Score), player(sf::Vector2f(0, 0), G, B), CoinText("Resources/coin.png"), sound(soundbuffer), healText("Resources/heal.png"), fastText("Resources/fast.png"), ballText("Resources/balls.png")
{
	//time
	srand(time(NULL));
	//level
	LoadLevel(level);
	//set texture
	CoinText.setSmooth(false);
	healText.setSmooth(false);
	fastText.setSmooth(false);
	ballText.setSmooth(false);
	//imgui
	ImGui::GetIO().FontGlobalScale = 1.5;
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

	//Music and sound effect
	if (RunMusic == true)
	{
		music.openFromFile("Music/TheBuilder.mp3");
		music.setLooping(true);
		music.play();
	}

	this->RunSound = RunSound;
	if (RunSound == true)
	{
		soundbuffer.loadFromFile("Music/bop.mp3");
		sound.setBuffer(soundbuffer);
	}
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
					bullets.emplace_back(player.getPosition(), CurrentMousePos, WindowXSize, WindowYSize, player.getDamage(), true, 400);
					TimeSincePlayerShoot = 0.0f;   //reset time

					if (RunSound == true)
					{
						sound.play();
					}
				}
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

	//Enemies move
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->LowerCooldown(dt);
		bool IsItSee = enemies[i]->IsEnemySeePlayer(player.getPosition());

		//if enemy can see player we check if there is any wall between enemy or player
		if (IsItSee == true)
		{
			//this function check if wall blocks enemy or not
			EnemyVisionLimitedbyWalls(i);
		}

		//move enemy
		enemies[i]->MoveEnemy(WindowXSize, WindowYSize, dt);
	}

	//bullets move
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].MoveBullet(dt);
	}

	//check if bullets is outside map - if yes than erase
	//and also check if it has collision with players or enemies
	for (int i = 0; i < bullets.size(); i++)
	{
		//check if bullets are in game map
		if (bullets[i].CheckBullet())
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
		else
		{
			//check collision with enemies if IsPlayer is true
			//else check collision with player
			if (bullets[i].getIsPlayers() == true)
			{
				Enemies_BulletsCollision(&i);
			}
			else
			{
				Player_BulletsCollision(&i);
			}
		}
	}

	//before implementing heal power up you need to check if player has 0 or less hp unless you want to rise him from dead
	Player_PowerupsCollision();

	//Collision with coins
	Player_CoinsCollision();

	ObjectSpawningControl(dt);

	//Check walls collision
	for (int i = 0; i < walls.size(); i++)
	{
		Wall_PlayerCollision(i);
		Wall_BulletCollision(i);
		Wall_EnemesCollision(i);
	}

	//Check if player is alive
	if (player.getHealth() <= 0)
	{
		changeState = true;
	}

	player.CountQuickfireTimer(dt);
	player.CountSpeedTimer(dt);

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

	for (int i = 0; i < powerups.size(); i++)
	{
		powerups[i].drawPowerUp(window);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].DrawBullet(window);
	}

	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].DrawWall(window);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->drawEnemy(window);

		//draw enemy health bar
		float ActualHealth = enemies[i]->getEnemyHealth();
		if (ActualHealth == 0)
		{
			continue;
		}

		float MaxHealth = enemies[i]->getMaxHealth();

		std::string name = "enemy" + std::to_string(i);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(ImVec2(enemies[i]->getEnemyPosition().x - 15, enemies[i]->getEnemyPosition().y - 3));
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::ProgressBar(ActualHealth / MaxHealth, ImVec2(30, 6), "");
		ImGui::End();
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(1);
	}

	player.DrawPlayer(window);
	
	ImGuiRender();
	ImGui::SFML::Render(window);
	window.display();
}