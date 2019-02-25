#include "pch.h"
#include "Entity.h"

Entity::Entity(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position)
{
	this->m_sprite = m_sprite;
	this->m_size = m_size;
	this->m_position = m_position;
	this->m_sprite.setPosition(m_position);
	this->m_border.setOrigin(this->m_position);
	this->m_border.setSize(sf::Vector2f(this->m_sprite.getGlobalBounds().width, this->m_sprite.getGlobalBounds().height));
	this->m_border.setOutlineColor(sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));
	this->m_border.setOutlineThickness(1);
	this->m_border.setFillColor(sf::Color(0, 0, 0, 0));
}