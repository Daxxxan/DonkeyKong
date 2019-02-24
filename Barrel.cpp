#include "Barrel.h"
#include "EntityManager.h"
#include "Collide.h"



Barrel::Barrel(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position)
	: Entity::Entity(m_sprite, m_size, m_position)
{
}


Barrel::~Barrel()
{
}

void Barrel::move()
{
	sf::Vector2f movement(0.f, 0.f);
	if (this->moveDown)
		movement.y += this->movementSpeed;
	if (this->moveLeft)
		movement.x -= this->movementSpeed;
	if (this->moveRight)
		movement.x += this->movementSpeed;

	this->m_sprite.move(movement);
}

void Barrel::moveAll()
{
	for (std::shared_ptr<Barrel> barrel : EntityManager::m_Barrels)
	{
		bool isOnABlock = false;

		for (std::shared_ptr<Block> block : EntityManager::m_Blocks)
		{
			if (block->m_sprite.getGlobalBounds().intersects(barrel->m_sprite.getGlobalBounds()))
			{
				isOnABlock = true;
				if (!barrel->moveLeft && !barrel->moveRight)
				{
					barrel->moveLeft = (std::rand() % 5) != 0;
					barrel->moveRight = !barrel->moveLeft;
				}
				barrel->move();
				break;
			}
		}

		if (!isOnABlock)
		{
			Collide::putOnTheFloor(barrel);
		}
	}
}