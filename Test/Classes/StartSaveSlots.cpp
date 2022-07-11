//
//  SaveSlot.cpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#include "StartSaveSlots.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "string.h"
#include "LevelLayer.h"
#include "MyTag.h"

StartSaveSlots* StartSaveSlots::create()
{
    StartSaveSlots *ret = new (std::nothrow) StartSaveSlots();
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

bool StartSaveSlots::init()
{
    cocos2d::Layer::init();
    
    makeSlot();
    
    return true;
}

void StartSaveSlots::makeSlot()
{
    cocos2d::Label* labelSlot[6];
    cocos2d::MenuItemLabel* itemSlot[6];
    auto menu = cocos2d::Menu::create(NULL);
    
    for(int i = 0 ; i < 6; i++)
    {
        labelSlot[i] = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("Slot %d", i+1), "fonts/Marker Felt.ttf", 24);
        itemSlot[i] = cocos2d::MenuItemLabel::create(labelSlot[i], CC_CALLBACK_1(StartSaveSlots::menuCallback, this));
        itemSlot[i]->setTag(i);
        menu->addChild(itemSlot[i]);
    }
    
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(cocos2d::Vec2(0, 0));
    menu->setPosition(cocos2d::Vec2(400, 150));
    this->addChild(menu);
}

void StartSaveSlots::menuCallback(Ref *pSender)
{
    cocos2d::MenuItemLabel* item = (cocos2d::MenuItemLabel*) pSender;
    GameScene* gameScene = GameScene::create();
    
    if(item->getString().c_str() == StringUtils::format("Slot 1"))
    {
        gameScene->slot = 1;
    }
    else if (item->getString().c_str() == StringUtils::format("Slot 2"))
    {
        gameScene->slot = 2;
    }
    else if (item->getString().c_str() == StringUtils::format("Slot 3"))
    {
        gameScene->slot = 3;
    }
    else if (item->getString().c_str() == StringUtils::format("Slot 4"))
    {
        gameScene->slot = 4;
    }
    else if (item->getString().c_str() == StringUtils::format("Slot 5"))
    {
        gameScene->slot = 5;
    }
    else if (item->getString().c_str() == StringUtils::format("Slot 6"))
    {
        gameScene->slot = 6;
    }
    LevelLayer* levelScene = (LevelLayer*)gameScene->getChildByTag(GameSceneTag::LEVELSCENE);
    for(int i = 0 ; i < 10; i++)
    {
        levelScene->getEventDispatcher()->removeEventListener(levelScene->listener[i]);
    }
    Director::getInstance()->replaceScene(gameScene);
}
