#include "EntityManager.h"

std::shared_ptr<Player> EntityManager::m_Player;
std::vector<std::shared_ptr<Ladder>> EntityManager::m_Ladders;
std::vector<std::shared_ptr<Block>> EntityManager::m_Blocks;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}
