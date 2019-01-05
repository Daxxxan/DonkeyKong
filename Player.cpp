#include "Player.h"
#include "EntityManager.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::isOnLadder() {
	for (std::shared_ptr<Ladder> ladder : EntityManager::m_Ladders) {
		if (EntityManager::m_Player->m_sprite.getGlobalBounds()
			.intersects(ladder->m_sprite.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

bool Player::isOnBlock() {
	for (std::shared_ptr<Block> block : EntityManager::m_Blocks) {
		if (EntityManager::m_Player->m_sprite.getGlobalBounds()
			.intersects(block->m_sprite.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}