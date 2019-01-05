#pragma once

class Entity
{
public:
	Entity() { };
	~Entity() { };

public:
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	bool m_enabled = true;

	// Enemy only
	bool m_bLeftToRight = true;
	int m_times = 0;
};

