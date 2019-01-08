#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"
#include "Player.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mIsJump(false)
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

			std::shared_ptr<Block> se = std::make_shared<Block>();
			se->m_sprite = _Block[i][j];
			se->m_size = _TextureBlock.getSize();
			se->m_position = _Block[i][j].getPosition();
			EntityManager::m_Blocks.push_back(se);
		}
	}

	// Draw Echelles

	_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y);

		std::shared_ptr<Ladder> se = std::make_shared<Ladder>();
		se->m_sprite = _Echelle[i];
		se->m_size = _TextureEchelle.getSize();
		se->m_position = _Echelle[i].getPosition();
		EntityManager::m_Ladders.push_back(se);
	}

	// Draw Mario

	mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png"); // Mario_small.png");
	_sizeMario = mTexture.getSize();
	mPlayer.setTexture(mTexture);
	sf::Vector2f posMario;
	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - _sizeMario.y + 4;

	mPlayer.setPosition(posMario);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->m_sprite = mPlayer;
	player->m_size = mTexture.getSize();
	player->m_position = mPlayer.getPosition();
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

	Collide::putOnTheFloor(EntityManager::m_Player); //Is it the right place to put this ?
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;
	if (mIsJump) {
		if (!EntityManager::m_Player->IsOnLadder()) {
			sf::Clock clock;
			sf::Vector2f movement(0.f, 0.f);
			movement.y -= 110.0;
			EntityManager::m_Player->m_sprite.move(movement * elapsedTime.asSeconds());
		}
	}

	EntityManager::m_Player->m_sprite.move(movement * elapsedTime.asSeconds());
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
	}

	for (std::shared_ptr<Ladder> ladder : EntityManager::m_Ladders)
	{
		if (ladder->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(ladder->m_sprite);
	}

	mWindow.draw(EntityManager::m_Player->m_sprite);

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
	if (key == sf::Keyboard::Up) {
		if (EntityManager::m_Player->IsOnLadder()) {
			mIsMovingUp = isPressed;
		}
		else if (!EntityManager::m_Player->IsOnBlock()) {
			mIsMovingUp = isPressed;
		} else {
			mIsMovingUp = false;
		}
	}

	if (key == sf::Keyboard::Left && EntityManager::m_Player->IsOnBlock()) {
		mIsMovingLeft = isPressed;
	}
	else {
		mIsMovingLeft = false;
	}
	if (key == sf::Keyboard::Right && EntityManager::m_Player->IsOnBlock()) {
		mIsMovingRight = isPressed;
	}
	else {
		mIsMovingRight = false;
	}

	if (key == sf::Keyboard::Down && (!EntityManager::m_Player->IsOnBlock() ||
		EntityManager::m_Player->IsOnLadderAxis())) {
		mIsMovingDown = isPressed;
	}
	else {
		mIsMovingDown = false;
	}

	if (key == sf::Keyboard::Space)
	{
		if (EntityManager::m_Player->MarioCollideTheAboveBlock()) {
			mIsJump = false;
		}
		else {
			mIsJump = isPressed;
		}
	}
}
