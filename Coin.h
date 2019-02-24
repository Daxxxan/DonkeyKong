#pragma once
#include "Entity.h"
class Coin :
	public Entity
{
public:
	Coin(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	~Coin();
};

