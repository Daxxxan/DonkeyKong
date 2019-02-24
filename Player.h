#pragma once
#include "pch.h"
#include "Collide.h"
#include "Entity.h"
#include "Ladder.h"

class Player : public Entity
{
public:
	const float movementSpeed = 1.f;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	bool mIsJump;
	bool disabledGravity = false;
	bool jump = false;
	int jumpHeight;

public:
	Player(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	~Player();

public:
	std::shared_ptr<Ladder> TheClosestLadderBehind();
	bool IsOnLadder();
	bool IsOnLadderAxis();
	bool IsOnBlock();
	bool IsUnderABlock();
	bool MarioCollideTheAboveBlock();
	void Move();
};