#pragma once
#include "pch.h"
#include "Collide.h"
#include "Entity.h"
#include "Ladder.h"

class Player : public Entity
{
public:
	Player();
	~Player();

public:
	std::shared_ptr<Ladder> TheClosestLadderBehind();
	bool IsOnLadder();
	bool IsOnLadderAxis();
	bool IsOnBlock();
	bool IsUnderABlock();
};