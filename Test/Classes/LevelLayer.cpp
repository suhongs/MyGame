//
//  LevelScene.cpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#include "LevelLayer.h"
#include "Star.h"
#include "MyExit.h"
#include "MyTag.h"
#include "Bomb.h"
#include "GameScene.h"
#include "Player.h"

LevelLayer* LevelLayer::create()
{
    LevelLayer *ret = new (std::nothrow) LevelLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool LevelLayer::init()
{
    Layer::init();
    
    Vec2 rectangle[4];
    rectangle[0] = Vec2(-10, -10);
    rectangle[1] = Vec2(10, -10);
    rectangle[2] = Vec2(10, 10);
    rectangle[3] = Vec2(-10, 10);
    
    DrawNode* myExit = MyExit::create();
    myExit->drawPolygon(rectangle, 4, Color4F::WHITE, 1, Color4F::WHITE);
    myExit->setPosition(400, 200);
    myExit->setTag(LevelSceneTag::EXIT);
    this->addChild(myExit);
    
    makeStar();
    makeBomb();
    
    for(int i = 0 ; i < 10; i++)
    {
        listener[i] = EventListenerTouchOneByOne::create();
        listener[i]->setSwallowTouches(true);
        listener[i]->onTouchBegan = [=](Touch* touch, Event* event)
        {
            auto target = static_cast<DrawNode*>(event->getCurrentTarget());
            
            Point locationInNode = convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect(target->getPosition().x-10, target->getPosition().y-10, s.width, s.height);
            
            if (rect.containsPoint(locationInNode))
            {
                reZorder(target);
                target->setOpacity(180);
                
                return true;
            }
            return false;
        };
        
        listener[i]->onTouchMoved = [](Touch* touch, Event* event)
        {
            auto target = static_cast<cocos2d::DrawNode*>(event->getCurrentTarget());
            target->setPosition(target->getPosition()+touch->getDelta());
        };
        
        listener[i]->onTouchEnded = [=](Touch* touch, Event* event)
        {
            auto target = static_cast<DrawNode*>(event->getCurrentTarget());
            target->setOpacity(255);
        };
    }
    
    for(int i = 0 ; i < 5; i++)
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener[i], star[i]);
        if(bomb[i] !=nullptr)
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener[i+5], bomb[i]);
    }
    
    return true;
}

void LevelLayer::makeStar()
{
    for(int i = 0 ; i < 5; i++)
    {
        star[i] = Star::create("Star.png");
        star[i]->setTag(LevelSceneTag::STAR1+i);
        
        this->addChild(star[i]);
    }
}

void LevelLayer::makeBomb()
{
    Vec2 rec[3];
    rec[0] = Vec2(-10, -10);
    rec[1] = Vec2(10, -10);
    rec[2] = Vec2(0, 10);
    
    for(int i = 0 ; i < 5; i++)
    {
        bomb[i] = Bomb::create();
        bomb[i]->drawPolygon(rec, 3, Color4F::RED, 1, Color4F::RED);
        bomb[i]->setPosition(100 + rand()%350,50+ rand() % 200);
        bomb[i]->setContentSize(Size(20, 20));
        bomb[i]->setAnchorPoint(Vec2(0,0));
        this->addChild(bomb[i]);
        bomb[i]->setTag(i+LevelSceneTag::BOMB1);
    }
}

void LevelLayer::onEnter()
{
    Layer::onEnter();
    
    GameScene* gameScene = (GameScene*)getParent();
    
    if (gameScene->gameMode == GameModeTag::CUSTOM)
        return;
    
    if (gameScene->level == 2)
        return;
    
    
    
    
    
    
    
    
    
    
    for (int i = 0 ; i < 5; i++)
    {
        this->removeChild((Bomb*)this->getChildByTag(i+LevelSceneTag::BOMB1));
    }
}


void LevelLayer::onExit()
{
    for(int i = 0; i < 10; i++)
        _eventDispatcher->removeEventListener(listener[i]);
    Layer::onExit();
}

void LevelLayer::reZorder(cocos2d::DrawNode *pSender)
{
    for(int i = 0; i < 5; i++)
    {
        star[i]->setZOrder(0);
        bomb[i]->setZOrder(0);
    }
    pSender->setZOrder(1);
}
