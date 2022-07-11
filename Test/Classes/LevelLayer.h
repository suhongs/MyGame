//
//  LevelScene.hpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#pragma once
#include "cocos2d.h"
#include "Star.h"

class LevelLayer : public cocos2d::Layer
{
public:
    cocos2d::DrawNode* star[5];
    cocos2d::DrawNode* bomb[5];
    cocos2d::EventListenerTouchOneByOne* listener[10];
    
public:
    static LevelLayer* create();
    virtual bool init() override;
    
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    void reZorder(cocos2d::DrawNode* pSender);
    
public:
    void makeStar();
    void makeBomb();
    void makeExit();
    
    
};
