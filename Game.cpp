#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"
#include "Player.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setFramerateLimit(160);

	// Draw blocks

	_TextureBlock.loadFromFile("Media/Textures/Block.png");
	_sizeBlock = _TextureBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			_Block[i][j].setTexture(_TextureBlock);
			_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

			std::shared_ptr<Block> se = std::make_shared<Block>(_Block[i][j], _TextureBlock.getSize(), _Block[i][j].getPosition());
			//se->m_sprite = _Block[i][j];
			//se->m_size = _TextureBlock.getSize();
			//se->m_position = _Block[i][j].getPosition();
			EntityManager::m_Blocks.push_back(se);
		}
	}

	// Draw Echelles

	_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y);

		//std::shared_ptr<Ladder> se = std::make_shared<Ladder>();
		std::shared_ptr<Ladder> se = std::make_shared<Ladder>(_Echelle[i], _TextureEchelle.getSize(), _Echelle[i].getPosition());
		//se->m_sprite = _Echelle[i];
		//se->m_size = _TextureEchelle.getSize();
		//se->m_position = _Echelle[i].getPosition();
		EntityManager::m_Ladders.push_back(se);
	}

	//Draw Donkey Kong
	textureDk.loadFromFile("Media/Textures/dk.png");
	sizeDk = textureDk.getSize();
	spriteDk.setTexture(textureDk);
	sf::Vector2f posDk;
	posDk.x = 600.f;
	posDk.y = BLOCK_SPACE - sizeDk.y + 2;

	spriteDk.setPosition(posDk);

	//std::shared_ptr<Dk> dk = std::make_shared<Dk>();
	std::shared_ptr<Dk> dk = std::make_shared<Dk>(spriteDk, textureDk.getSize(), spriteDk.getPosition());
	//dk->m_sprite = spriteDk;
	//dk->m_size = textureDk.getSize();
	//dk->m_position = spriteDk.getPosition();
	EntityManager::m_Dk = dk;

	// Draw Mario

	mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png"); // Mario_small.png");
	_sizeMario = mTexture.getSize();
	mPlayer.setTexture(mTexture);
	sf::Vector2f posMario;
	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - _sizeMario.y + 4;

	mPlayer.setPosition(posMario);

	//Draw player
	//std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Player> player = std::make_shared<Player>(mPlayer, mTexture.getSize(), mPlayer.getPosition());
	//player->m_sprite = mPlayer;
	//player->m_size = mTexture.getSize();
	//player->m_position = mPlayer.getPosition();
	EntityManager::m_Player = player;

	// Draw Statistic Font 

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}

	Collide::putOnTheFloor(EntityManager::m_Player);
}

void Game::update(sf::Time elapsedTime)
{
	if (EntityManager::m_Player->MarioCollideTheAboveBlock()) {
		EntityManager::m_Player->mIsJump = false;
	}
	EntityManager::m_Player->Move();
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Block> block : EntityManager::m_Blocks)
	{
		if (block->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(block->m_sprite);
		//mWindow.draw(block->m_border);
	}

	for (std::shared_ptr<Ladder> ladder : EntityManager::m_Ladders)
	{
		if (ladder->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(ladder->m_sprite);
		//mWindow.draw(ladder->m_border);
	}

	mWindow.draw(EntityManager::m_Player->m_sprite);
	mWindow.draw(EntityManager::m_Player->m_border);
	mWindow.draw(EntityManager::m_Dk->m_sprite);
	mWindow.draw(EntityManager::m_Dk->m_border);

	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}

	//
	// Handle collision
	//

	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		// Handle collision weapon enemies
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	printf("key : %d; isPressed : %d\n", key, isPressed);
	std::shared_ptr<Player> player = EntityManager::m_Player;
	if (key == sf::Keyboard::Up) {
		if (player->IsOnLadder()) {
			player->mIsMovingUp = isPressed;
		}
		else if (!player->IsOnBlock()) {
			player->mIsMovingUp = isPressed;
		} else {
			player->mIsMovingUp = false;
		}
	}

	if (key == sf::Keyboard::Left && player->IsOnBlock()) {
		player->mIsMovingLeft = isPressed;
	}
	
	if (key == sf::Keyboard::Right && player->IsOnBlock()) {
		player->mIsMovingRight = isPressed;
	}

	if (key == sf::Keyboard::Down && (!player->IsOnBlock() ||
		player->IsOnLadderAxis())) {
		player->mIsMovingDown = isPressed;
	}

	if (key == sf::Keyboard::Space)
	{
		if (player->IsOnBlock())
		{
			player->mIsJump = true;
		}
	}
}
