#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"
#include "Player.h"
#include "Coin.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

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

	//Define level json
	json level = {
		{
			"player", {
				{"x", 80},
				{"y", 500}
			}
		},
		{
			"dk", {
				{"x", 650},
				{"y", 41}
			}
		},
		{
			"blocks" , {
				{{"x", 210}, {"y", 110}},
				{{"x", 280}, {"y", 110}},
				{{"x", 350}, {"y", 110}},
				{{"x", 420}, {"y", 110}},
				{{"x", 490}, {"y", 110}},
				{{"x", 560}, {"y", 110}},
				{{"x", 630}, {"y", 110}},
				{{"x", 700}, {"y", 110}},

				{{"x",  70}, {"y", 220}},
				{{"x", 140}, {"y", 220}},
				{{"x", 210}, {"y", 220}},
				{{"x", 280}, {"y", 220}},
				{{"x", 350}, {"y", 220}},

				{{"x", 210}, {"y", 330}},
				{{"x", 280}, {"y", 330}},
				{{"x", 350}, {"y", 330}},
				{{"x", 420}, {"y", 330}},
				{{"x", 490}, {"y", 330}},

				{{"x",  70}, {"y", 440}},
				{{"x", 140}, {"y", 440}},
				{{"x", 210}, {"y", 440}},
				{{"x", 280}, {"y", 440}},

				{{"x", 490}, {"y", 440}},
				{{"x", 560}, {"y", 440}},
				{{"x", 630}, {"y", 440}},
				{{"x", 700}, {"y", 440}},

				{{"x",  70}, {"y", 550}},
				{{"x", 140}, {"y", 550}},
				{{"x", 210}, {"y", 550}},
				{{"x", 280}, {"y", 550}},
				{{"x", 350}, {"y", 550}},
				{{"x", 420}, {"y", 550}},
				{{"x", 490}, {"y", 550}},
				{{"x", 560}, {"y", 550}},
				{{"x", 630}, {"y", 550}},
				{{"x", 700}, {"y", 550}}
			},
		},
		{
			"ladders", {
				{{"x", 280}, {"y", 143}},
				{{"x", 350}, {"y", 253}},
				{{"x", 250}, {"y", 363}},
				{{"x", 500}, {"y", 363}},
				{{"x", 600}, {"y", 473}}
			}
		},
		{
			"coins", {
				{{"x",  90}, {"y", 180}},
				{{"x",  80}, {"y", 400}},
				{{"x", 700}, {"y", 400}},
				{{"x", 450}, {"y", 510}}
			}
		}
	};

	// Draw blocks
	_TextureBlock.loadFromFile("Media/Textures/Block.png");
	_sizeBlock = _TextureBlock.getSize();
	_Block.setTexture(_TextureBlock);

	auto blocks = level["blocks"].get<std::vector<json>>();
	for (json block : blocks)
	{
		_Block.setPosition(block["x"].get<float>(), block["y"].get<float>());
		std::shared_ptr<Block> sb = std::make_shared<Block>(_Block, _TextureBlock.getSize(), _Block.getPosition());
		EntityManager::m_Blocks.push_back(sb);
	}

	// Draw Echelles
	_TextureLadder.loadFromFile("Media/Textures/Echelle.png");
	_Ladder.setTexture(_TextureLadder);

	auto ladders = level["ladders"].get<std::vector<json>>();
	for (json ladder : ladders)
	{
		_Ladder.setPosition(ladder["x"].get<float>(), ladder["y"].get<float>());
		std::shared_ptr<Ladder> sl = std::make_shared<Ladder>(_Ladder, _TextureLadder.getSize(), _Ladder.getPosition());
		EntityManager::m_Ladders.push_back(sl);
	}
	
	// Draw Coin
	_TextureCoin.loadFromFile("Media/Textures/Piece.PNG");
	_Coin.setTexture(_TextureCoin);

	auto coins = level["coins"].get<std::vector<json>>();
	for (json coin : coins)
	{
		_Coin.setPosition(coin["x"].get<float>(), coin["y"].get<float>());
		std::shared_ptr<Coin> sc = std::make_shared<Coin>(_Coin, _TextureCoin.getSize(), _Coin.getPosition());
		EntityManager::m_Coin.push_back(sc);
	}

	//Draw Donkey Kong
	textureDk.loadFromFile("Media/Textures/dk.png");
	sizeDk = textureDk.getSize();
	spriteDk.setTexture(textureDk);
	sf::Vector2f posDk;
	posDk.x = level["dk"]["x"].get<float>();
	posDk.y = level["dk"]["y"].get<float>();

	spriteDk.setPosition(posDk);
	std::shared_ptr<Dk> dk = std::make_shared<Dk>(spriteDk, textureDk.getSize(), spriteDk.getPosition());
	EntityManager::m_Dk = dk;

	// Draw Mario

	mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png");
	_sizeMario = mTexture.getSize();
	mPlayer.setTexture(mTexture);
	sf::Vector2f posMario;
	posMario.x = level["player"]["x"].get<float>();
	posMario.y = level["player"]["y"].get<float>();

	mPlayer.setPosition(posMario);

	//Draw player
	std::shared_ptr<Player> player = std::make_shared<Player>(mPlayer, mTexture.getSize(), mPlayer.getPosition());
	EntityManager::m_Player = player;

	//Prepare Barrel drawing
	dk->_TextureBarrel.loadFromFile("Media/Textures/barrel.png");
	dk->_sizeBarrel = dk->_TextureBarrel.getSize();
	dk->_Barrel.setTexture(dk->_TextureBarrel);

	// Draw Statistic Font 
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	//Draw endgame
	mEndGame.setFont(mFont);
	mEndGame.setPosition(120.f, 120.f);
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
}

void Game::update(sf::Time elapsedTime)
{
	std::shared_ptr<Player> player = EntityManager::m_Player;
	if (!player->IsOnBlock() && !player->mIsJump && !player->disabledGravity)
	{
		if (!player->IsOnLadder() || (player->IsOnLadder() && player->jump)) {
			Collide::putOnTheFloor(EntityManager::m_Player);
		}
		return;
	}

	if (player->jumpHeight > 50) {
		player->mIsJump = false;
	}

	if (!player->jump) {
		if (player->IsOnLadder() && !player->IsOnBlock()) {
			player->mIsMovingLeft = false;
			player->mIsMovingRight = false;
		}
		if (player->IsOnLadderAxis() && player->mIsMovingDown) {
			player->mIsMovingLeft = false;
			player->mIsMovingRight = false;
		}
	}

	player->Move();
	EntityManager::m_Dk->spawnBarrel();
	Barrel::moveAll();
	isGameOver();
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

	for (std::shared_ptr<Coin> coin : EntityManager::m_Coin)
	{
		if (coin->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(coin->m_sprite);
	}

	for (std::shared_ptr<Barrel> barrel : EntityManager::m_Barrels)
	{
		if (barrel->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(barrel->m_sprite);
	}

	mWindow.draw(EntityManager::m_Player->m_sprite);
	mWindow.draw(EntityManager::m_Player->m_border);
	mWindow.draw(EntityManager::m_Dk->m_sprite);
	mWindow.draw(EntityManager::m_Dk->m_border);

	mWindow.draw(mStatisticsText);
	if (win && EntityManager::m_Player->invinsible) {
		mEndGame.setCharacterSize(160);
		mEndGame.setString("Cheater!");
	} else if(win) {
		mEndGame.setCharacterSize(160);
		mEndGame.setString("You won!");
	}
	else if (EntityManager::m_Player->isDead) {
		mEndGame.setCharacterSize(90);
		mEndGame.setString("Mario is dead !");
	}
	mWindow.draw(mEndGame);
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
	std::shared_ptr<Player> player = EntityManager::m_Player;
	if (key == sf::Keyboard::Up) {
		if (player->IsOnLadder()) {
			player->mIsMovingUp = isPressed;
			player->disabledGravity = true;
		}
		else if (!player->IsOnBlock()) {
			player->mIsMovingUp = isPressed;
			player->disabledGravity = true;
		} else {
			player->mIsMovingUp = false;
			player->disabledGravity = false;
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
		player->disabledGravity = true;
		player->mIsMovingDown = isPressed;
	}
	else if (player->IsOnBlock()) {
		player->disabledGravity = false;
		player->mIsMovingDown = false;
	}

	if (key == sf::Keyboard::Space)
	{
		if (player->IsOnBlock())
		{
			player->jump = true;
			player->mIsJump = true;
		}
	}

	if (key == sf::Keyboard::I)
	{
		player->invinsible = true;
	}
}

void Game::isGameOver()
{
	isPlayerDead();
	isPlayerGetCoin();
}

void Game::isPlayerDead()
{
	if (EntityManager::m_Player->invinsible) return;

	for (std::shared_ptr<Barrel> barrel : EntityManager::m_Barrels)
	{
		if (barrel->m_sprite.getGlobalBounds().intersects(EntityManager::m_Player->m_sprite.getGlobalBounds()))
		{
			EntityManager::m_Player->isDead = true;
		}
	}
}

bool Game::allCoinGet() {
	for (std::shared_ptr<Coin> coin : EntityManager::m_Coin)
	{
		if (coin->m_enabled) {
			return false;
		}
	}
	return true;
}

void Game::isPlayerGetCoin()
{
	for (int i = 0; i < EntityManager::m_Coin.size(); i++) {
		if (EntityManager::m_Coin[i]->m_sprite.getGlobalBounds().intersects(EntityManager::m_Player->m_sprite.getGlobalBounds()))
		{
			EntityManager::m_Coin[i]->m_enabled = false;
		}
	}

	if (allCoinGet()) {
		if(!EntityManager::m_Player->isDead)
			win = true;
	}
}
