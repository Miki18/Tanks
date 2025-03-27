#include "Game.h"

//Constructor
Game::Game(sf::RenderWindow& window, bool& changeState) : window(window), changeState(changeState), player(sf::Vector2f(0, 0)), CoinText("Resources/coin.png")
{
	srand(time(NULL));
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

	player.TransformPlayer(CurrentMousePos, WindowXSize, WindowYSize, dt, MovePlayer);
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

	TimeUntilCoinSpawn = TimeUntilCoinSpawn - dt;
	if (TimeUntilCoinSpawn < 0.0f)
	{
		Coin coin(CoinText, sf::Vector2f(rand()%WindowXSize, rand()%WindowYSize));
		coins.emplace_back(coin);
		TimeUntilCoinSpawn = 3.0f;
	}

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
	player.DrawPlayer(window);
	ImGui::SFML::Render(window);
	window.display();
}