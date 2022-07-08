//
//  CustomSaveSlot.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/07.
//

#include "CustomSaveSlots.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "LevelLayer.h"
#include "MyTag.h"

CustomSaveSlots* CustomSaveSlots::create()
{
    CustomSaveSlots *ret = new (std::nothrow) CustomSaveSlots();
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

bool CustomSaveSlots::init()
{
    cocos2d::Layer::init();
    
    cocos2d::Label* labelSlot[6];
    cocos2d::MenuItemLabel* itemSlot[6];
    for(int i = 0 ; i < 6; i++)
    {
        labelSlot[i] = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("Slot %d", i+1), "fonts/Marker Felt.ttf", 24);
        itemSlot[i] = cocos2d::MenuItemLabel::create(labelSlot[i], CC_CALLBACK_1(CustomSaveSlots::menuCallback, this));
        itemSlot[i]->setTag(i);
    }
    auto menu = cocos2d::Menu::create(itemSlot[0], itemSlot[1], itemSlot[2], itemSlot[3], itemSlot[4], itemSlot[5], NULL);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(cocos2d::Vec2(0, 0));
    menu->setPosition(cocos2d::Vec2(400, 150));
    this->addChild(menu);
    
    return true;
}

void CustomSaveSlots::menuCallback(Ref *pSender)
{
    cocos2d::MenuItemLabel* item = (cocos2d::MenuItemLabel*) pSender;
    GameScene* gameScene = GameScene::create();
    LevelLayer* levelScene = (LevelLayer*)gameScene->getChildByTag(GameSceneTag::LEVELSCENE);
    gameScene->gameMode = GameModeTag::CUSTOM;
    
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
    Director::getInstance()->replaceScene(gameScene);
}
