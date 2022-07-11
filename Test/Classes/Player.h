//
//  Player.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/04.
//

#pragma once

#include "GameObject.h"

USING_NS_CC;


enum PlayerState
{
    IDLE,
    RIGHT_MOVE,
    LEFT_MOVE,
    UP_MOVE,
    DOWN_MOVE,
};

class Player : public cocos2d::Sprite, public GameObject
{
public:
    static Player* create(const std::string& filename, int posX, int posY);
    
private:
    bool init(const std::string& filename, int posX, int posY);

public:
    void move(PlayerState state);
    
private:
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void checkCollison();
    void resetPosition();
    
    virtual cocos2d::Rect getBoundingBox() override;
    virtual void onCollisionEnter(GameObject* pColObj) override;

};
