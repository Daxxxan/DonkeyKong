#pragma once
#include "pch.h"

#define ECHELLE_COUNT 4
#define COIN_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

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

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Texture	mTexture;
	sf::Sprite	mPlayer;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;

	sf::Texture textureDk;
	sf::Vector2u sizeDk;
	sf::Sprite	spriteDk;

	std::size_t	mStatisticsNumFrames;

	sf::Texture	_TextureEchelle;
	sf::Sprite	_Echelle[ECHELLE_COUNT];
	sf::Texture	_TextureCoin;
	sf::Sprite	_Coin[COIN_COUNT];
	sf::Texture	_TextureBlock;
	sf::Sprite	_Block[BLOCK_COUNT_X][BLOCK_COUNT_Y];
	sf::Texture	_TextureWeapon;
	sf::Sprite	_Weapon;
	sf::Vector2u _sizeBlock;
	sf::Vector2u _sizeMario;
};

