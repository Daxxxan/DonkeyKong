#pragma once
#include "pch.h"

class Entity
{
public:
	Entity(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	~Entity() { };

public:
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	sf::RectangleShape m_border;
	bool m_enabled = true;

	// Enemy only
	bool m_bLeftToRight = true;
	int m_times = 0;
};

