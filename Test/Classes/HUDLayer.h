//
//  HUDLayer.hpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "MyController.h"

class HUDLayer : public cocos2d::Layer
{
public:
    static HUDLayer* create();
    virtual bool init();
    
public:
    void menuCallback(Ref* pSender);
    void menuSaveCallback(Ref* pSender);
    void backToMenuCallback(Ref* pSender);
    
public:
    void createMyController();
    void move(PlayerState state);
    
private:
    int score;
};
