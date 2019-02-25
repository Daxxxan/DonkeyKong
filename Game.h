#pragma once
#include "pch.h"

class Game
{
public:
	Game();
	~Game() { };
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void isGameOver();
	void isPlayerDead();
	bool allCoinGet();
	void isPlayerGetCoin();
	bool win = false;

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Texture	mTexture;
	sf::Sprite	mPlayer;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Text	mEndGame;
	sf::Time	mStatisticsUpdateTime;

	sf::Texture textureDk;
	sf::Vector2u sizeDk;
	sf::Sprite	spriteDk;

	std::size_t	mStatisticsNumFrames;

	sf::Texture	_TextureLadder;
	sf::Sprite	_Ladder;
	sf::Texture	_TextureCoin;
	sf::Sprite	_Coin;
	sf::Texture	_TextureBlock;
	sf::Sprite	_Block;
	sf::Texture	_TextureWeapon;
	sf::Sprite	_Weapon;
	sf::Vector2u _sizeBlock;
	sf::Vector2u _sizeMario;
};

