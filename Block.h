#pragma once
#include "pch.h"
#include "Entity.h"

class Block : public Entity
{
public:
	Block(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	~Block(); 
};

