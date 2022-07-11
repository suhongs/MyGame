//
//  Player.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/04.
//

#include "Player.h"
#include "GameScene.h"
#include "LevelLayer.h"
#include "HUDLayer.h"
#include "MyTag.h"
#include "EndingScene.h"
#include "GameObject.h"
#include "MyExit.h"

USING_NS_CC;

Player* Player::create(const std::string& filename, int posX, int posY)
{
    Player* pPlayer = new (std::nothrow) Player();
    if (pPlayer && pPlayer->init(filename, posX, posY))
    {
        pPlayer->autorelease();
        return pPlayer;
    }
    
    CC_SAFE_DELETE(pPlayer);
    return nullptr;
}

bool Player::init(const std::string& filename, int posX, int posY)
{
    if(initWithFile(filename) == false)
        return false;
    
    setAnchorPoint(Vec2(0, 0));
    setPosition(posX, posY);
    
    return true;
}

void Player::moveRight()
{
    this->setPosition(this->getPosition() + Vec2(2, 0));
}

void Player::moveLeft()
{
    this->setPosition(this->getPosition() + Vec2(-2, 0));
}

void Player::moveUp()
{
    this->setPosition(this->getPosition() + Vec2(0, 2));
}

void Player::moveDown()
{
    this->setPosition(this->getPosition() + Vec2(0, -2));
}

void Player::checkCollison()
{

}

void Player::resetPosition()
{
    this->setPosition(100, 200);
}

void Player::move(PlayerState state)
{
    switch (state)
    {
        case PlayerState::RIGHT_MOVE :  moveRight();    break;
        case PlayerState::LEFT_MOVE  :  moveLeft();     break;
        case PlayerState::UP_MOVE    :  moveUp();       break;
        case PlayerState::DOWN_MOVE  :  moveDown();     break;
        default:
            break;
    }
    
    this->checkCollison();
}

cocos2d::Rect Player::getBoundingBox()
{
//    AABB aabb = getAABB();
//    Rect ret(aabb._min.x, aabb._min.y, (aabb._max.x - aabb._min.x), (aabb._max.y - aabb._min.y));
//    return ret;
    cocos2d::Rect rec(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height);
    
    return rec;
}

void Player::onCollisionEnter(GameObject* pColObj)
{
    MyExit* myExit = dynamic_cast<MyExit*>(pColObj);
    if(myExit!=nullptr)
    {
        this->resetPosition();
    }
}
