#pragma once
#include "Entity.h"

class Barrel : public Entity
{
public:
	const float movementSpeed = 1.;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

public:
	Barrel(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	virtual ~Barrel();

public:
	void move();
	static void moveAll();
};

