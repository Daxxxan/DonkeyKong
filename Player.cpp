#include "Player.h"
#include "EntityManager.h"

Player::Player()
{
}


Player::~Player()
{
}


std::shared_ptr<Ladder> Player::TheClosestLadderBehind() {
	std::shared_ptr<Ladder> theClosestLadderBehindPlayer = NULL;
	float topLadder = NULL;
	float bottomPlayer = NULL;

	for (std::shared_ptr<Ladder> ladder : EntityManager::m_Ladders) {
		topLadder = ladder->m_sprite.getGlobalBounds().top;
		bottomPlayer = EntityManager::m_Player->m_sprite.getGlobalBounds().top + EntityManager::m_Player->m_sprite.getGlobalBounds().height;

		if (topLadder > bottomPlayer) {
			if (theClosestLadderBehindPlayer == NULL) {
				theClosestLadderBehindPlayer = ladder;
			}

			if (topLadder - bottomPlayer < theClosestLadderBehindPlayer->m_sprite.getGlobalBounds().top - bottomPlayer ||
				theClosestLadderBehindPlayer->m_sprite.getGlobalBounds().top - bottomPlayer < 0) {
				theClosestLadderBehindPlayer = ladder;
				break;
			}
		}
	}
	return theClosestLadderBehindPlayer;
}

bool Player::IsOnLadder() {
	for (std::shared_ptr<Ladder> ladder : EntityManager::m_Ladders) {
		if( Collide::FirstSpriteBetweenRigtAndLeftSecondSprite(EntityManager::m_Player->m_sprite, 
			ladder->m_sprite) && 
			(Collide::FirstSpriteBetweenTopAndBottomSecondSprite(EntityManager::m_Player->m_sprite,
				ladder->m_sprite) ||
				Collide::BottomFirstSpriteBetweenTopAndBottomSecondSprite(EntityManager::m_Player->m_sprite,
				ladder->m_sprite)
			)
		) {
			return true;
		}
	}
	return false;
}

bool Player::IsOnLadderAxis()
{
	std::shared_ptr<Ladder> theClosestLadderBehindPlayer = Player::TheClosestLadderBehind();
	if (theClosestLadderBehindPlayer) {
		if (Collide::FirstSpriteBetweenRigtAndLeftSecondSprite(EntityManager::m_Player->m_sprite,
			theClosestLadderBehindPlayer->m_sprite)) {
			return true;
		}
	}
	return false;
}

bool Player::IsOnBlock() {
	for (std::shared_ptr<Block> block : EntityManager::m_Blocks) {
		if(Collide::BottomFirstSpriteCollideTopSecondSprite(EntityManager::m_Player->m_sprite,
			block->m_sprite)) {
			return true;
		}
	}
	return false;
}

bool Player::IsUnderABlock() {
	for (std::shared_ptr<Block> block : EntityManager::m_Blocks) {
		if (Collide::FirstSpriteBetweenTopAndBottomSecondSprite(EntityManager::m_Player->m_sprite,
			block->m_sprite) ||
			Collide::BottomFirstSpriteBetweenTopAndBottomSecondSprite(EntityManager::m_Player->m_sprite,
				block->m_sprite)) {
			return true;
		}
	}
	return false;
}

bool Player::MarioCollideTheAboveBlock() {
	for (std::shared_ptr<Block> block : EntityManager::m_Blocks) {
		if (Collide::TopFirstSpriteCollideBottomSecondSprite(EntityManager::m_Player->m_sprite, block->m_sprite)) {
			return true;
		}
	}
	return false;
}
