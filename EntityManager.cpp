#include "EntityManager.h"

std::shared_ptr<Player> EntityManager::m_Player;
std::shared_ptr<Dk> EntityManager::m_Dk;
std::vector<std::shared_ptr<Ladder>> EntityManager::m_Ladders;
std::vector<std::shared_ptr<Coin>> EntityManager::m_Coin;
std::vector<std::shared_ptr<Block>> EntityManager::m_Blocks;
std::vector <std::shared_ptr<Barrel>> EntityManager::m_Barrels;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}
