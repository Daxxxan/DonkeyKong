#pragma once
#include "pch.h"

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

private:
	static bool IsEqual(float firstNumber, float secondNumber);
	static bool IsBetween(float firstNumber, float secondNumber, float thirdNumber);
};

