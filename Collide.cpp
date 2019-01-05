#include "Collide.h"



Collide::Collide()
{
}


Collide::~Collide()
{
}

bool Collide::IsEqual(float firstNumber, float secondNumber) {
	return firstNumber == secondNumber;
}

bool Collide::IsBetween(float firstNumber, float secondNumber, float thirdNumber) {
	if (firstNumber == thirdNumber) {
		return false;
	}

	if (firstNumber > secondNumber && firstNumber < thirdNumber) {
		return true;
	}
	return false;
}

bool Collide::BottomFirstSpriteCollideTopSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float bottomFirstSprite = firstSprite.getGlobalBounds().top + firstSprite.getLocalBounds().height;
	float topSecondSprite = secondSprite.getGlobalBounds().top;

	if (Collide::IsEqual(bottomFirstSprite, topSecondSprite)) {
		return true;
	}
	else if (IsBetween(bottomFirstSprite, topSecondSprite - 5, topSecondSprite + 5)) {
		return true;
	}
	else {
		return false;
	}
}

bool Collide::TopFirstSpriteCollideBottomSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float topFirstSprite = firstSprite.getGlobalBounds().top;
	float BottomSecondSprite = secondSprite.getGlobalBounds().top + secondSprite.getLocalBounds().height;

	return Collide::IsEqual(topFirstSprite, BottomSecondSprite);
}

bool Collide::LeftFirstSpriteCollideRightSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float leftFirstSprite = firstSprite.getGlobalBounds().left;
	float rightSecondSprite = secondSprite.getGlobalBounds().left + secondSprite.getLocalBounds().width;

	return Collide::IsEqual(leftFirstSprite, rightSecondSprite);
}

bool Collide::RightFirstSpriteCollideLeftSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float rightFirstSprite = firstSprite.getGlobalBounds().left + firstSprite.getLocalBounds().width;
	float leftSecondSprite = secondSprite.getGlobalBounds().left;

	return Collide::IsEqual(rightFirstSprite, leftSecondSprite);
}

bool Collide::FirstSpriteBetweenRigtAndLeftSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float centerFirstSprite = firstSprite.getGlobalBounds().left + (firstSprite.getLocalBounds().width / 2);
	float leftSecondSprite = secondSprite.getGlobalBounds().left;
	float rightSecondSprite = secondSprite.getGlobalBounds().left + secondSprite.getLocalBounds().width;

	return Collide::IsBetween(centerFirstSprite, leftSecondSprite, rightSecondSprite);
}

bool Collide::FirstSpriteBetweenTopAndBottomSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float centerFirstSprite = firstSprite.getGlobalBounds().top + (firstSprite.getLocalBounds().height / 2);
	float topSecondSprite = secondSprite.getGlobalBounds().top;
	float bottomSecondSprite = secondSprite.getGlobalBounds().top + secondSprite.getLocalBounds().height;

	return Collide::IsBetween(centerFirstSprite, topSecondSprite, bottomSecondSprite);
}

bool Collide::BottomFirstSpriteBetweenTopAndBottomSecondSprite(sf::Sprite firstSprite, sf::Sprite secondSprite) {
	float bottomFirstSprite = firstSprite.getGlobalBounds().top + firstSprite.getLocalBounds().height;
	float topSecondSprite = secondSprite.getGlobalBounds().top;
	float bottomSecondSprite = secondSprite.getGlobalBounds().top + secondSprite.getLocalBounds().height;

	return Collide::IsBetween(bottomFirstSprite, topSecondSprite, bottomSecondSprite);
}


