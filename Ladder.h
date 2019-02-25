#pragma once
#include "pch.h"
#include "Entity.h"

class Ladder : public Entity
{
public:
	Ladder(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	~Ladder();
};

