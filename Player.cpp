#include "Player.h"
#include "EntityManager.h"

Player::Player(sf::Sprite m_sprite, sf::Vector2u m_size, sf::Vector2f m_position) 
	: Entity::Entity(m_sprite, m_size, m_position)
{
	this->mIsMovingUp = false;
	this->mIsMovingDown = false;
	this->mIsMovingRight = false;
	this->mIsMovingLeft = false;
	this->mIsJump = false;
	this->jumpHeight = 0;
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
	sf::Vector2f position = theClosestLadderBehindPlayer->m_position;

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

void Player::Move()
{
	//printf("Player direction : [up : %d, down : %d, left : %d, right : %d, jump : %d, jumpHeight : %d]\n", 
		//mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsJump, jumpHeight);
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= movementSpeed;
	if (mIsMovingDown)
		movement.y += movementSpeed;
	if (mIsMovingLeft)
		movement.x -= movementSpeed;
	if (mIsMovingRight)
		movement.x += movementSpeed;
	if (mIsJump) {
		//if (!EntityManager::m_Player->IsOnLadder()) {
			movement.y -= movementSpeed;
			this->jumpHeight++;
		//}
	}

	EntityManager::m_Player->m_sprite.move(movement);
}
