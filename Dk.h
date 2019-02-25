#pragma once
#include "pch.h"
#include "Entity.h"
class Dk : public Entity {
public:
	sf::Clock spawner;
	sf::Vector2u _sizeBarrel;
	sf::Texture	_TextureBarrel;
	sf::Sprite	_Barrel;

public:
	Dk(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position);
	~Dk();
	void spawnBarrel();
};

