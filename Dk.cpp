#include "Dk.h"
#include "EntityManager.h"



Dk::Dk(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position)
	: Entity::Entity(m_sprite, m_size, m_position)
{
	
}


Dk::~Dk()
{
}

void Dk::spawnBarrel() {
	sf::Time timeSinceLastSpawn = this->spawner.getElapsedTime();
	if (timeSinceLastSpawn.asSeconds() >= 4.) {
		sf::Vector2f position(this->m_position.x, this->m_position.y);
		this->spawner.restart();
		EntityManager::m_Barrels.push_back(std::make_shared<Barrel>(this->_Barrel, this->_sizeBarrel, position));
		printf("Barrel spawned at (%lf, %lf)\n", this->m_position.x, this->m_position.y);
	}
}