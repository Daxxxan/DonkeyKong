#pragma once
#include "pch.h"
#include "Block.h"
class Player;

class Collide
{
public:
	Collide();
	~Collide();

public:
	static bool BottomFirstSpriteCollideTopSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static bool TopFirstSpriteCollideBottomSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static bool LeftFirstSpriteCollideRightSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static bool RightFirstSpriteCollideLeftSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static bool FirstSpriteBetweenRigtAndLeftSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static bool FirstSpriteBetweenTopAndBottomSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static bool BottomFirstSpriteBetweenTopAndBottomSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite);
	static void putOnTheFloor(std::shared_ptr<Player> p);

private:
	static bool IsEqual(float firstNumber, float secondNumber);
	static bool IsBetween(float firstNumber, float secondNumber, float thirdNumber);
	static std::shared_ptr<Block> GetTheNearestBlockUnderPlayer(std::shared_ptr<Player> p);
	static double GetDistance(sf::Sprite s1, sf::Sprite s2);
};

