//
//  HUDLayer.cpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#include "HUDLayer.h"
#include "MyController.h"
#include "GameScene.h"
#include "LevelLayer.h"
#include "Player.h"
#include "MyTag.h"
#include "MenuScene.h"
#include "cocos2d.h"
#include "EndingScene.h"

HUDLayer* HUDLayer::create()
{
    HUDLayer *ret = new (std::nothrow) HUDLayer();
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

bool HUDLayer::init()
{
    Layer::init();
    
    cocos2d::Label* labelLevel;
    labelLevel = cocos2d::Label::createWithTTF("Level : 1", "fonts/Marker Felt.ttf", 10);
    labelLevel->setPosition(cocos2d::Vec2(200, 306));
    labelLevel->setAnchorPoint(cocos2d::Vec2(0, 0));
    this->addChild(labelLevel);
    labelLevel->setTag(HUDLayerTag::LABELLEVEL);
    
    cocos2d::Label* labelScore = cocos2d::Label::createWithTTF("Score : 0", "fonts/Marker Felt.ttf", 10);
    labelScore->setPosition(cocos2d::Vec2(400, 306));
    labelScore->setAnchorPoint(cocos2d::Vec2(0, 0));
    
    this->addChild(labelScore);
    labelScore->setTag(HUDLayerTag::LABELSCORE);
    
    auto labelUp = cocos2d::Label::createWithTTF("up", "fonts/Marker Felt.ttf", 24);
    auto labelDown = cocos2d::Label::createWithTTF("down", "fonts/Marker Felt.ttf", 24);
    auto labelLeft = cocos2d::Label::createWithTTF("left", "fonts/Marker Felt.ttf", 24);
    auto labelRight = cocos2d::Label::createWithTTF("right", "fonts/Marker Felt.ttf", 24);
    auto labelSave = cocos2d::Label::createWithTTF("save", "fonts/Marker Felt.ttf", 10);
    auto labelMenu = cocos2d::Label::createWithTTF("menu", "fonts/Marker Felt.ttf", 10);
    
    MyController* itemUp = MyController::create(labelUp,NULL);
    MyController* itemDown = MyController::create(labelDown, NULL);
    MyController* itemLeft = MyController::create(labelLeft, NULL);
    MyController* itemRight = MyController::create(labelRight, NULL);
    MyController* itemSave = MyController::create(labelSave, NULL);
    MyController* itemMenu = MyController::create(labelMenu, CC_CALLBACK_1(HUDLayer::menuCallback, this));
    
    itemRight->setHoldCallback(CC_CALLBACK_0(HUDLayer::move, this, PlayerState::RIGHT_MOVE));
    itemUp->setHoldCallback(CC_CALLBACK_0(HUDLayer::move, this, PlayerState::UP_MOVE));
    itemDown->setHoldCallback(CC_CALLBACK_0(HUDLayer::move, this, PlayerState::DOWN_MOVE));
    itemLeft->setHoldCallback(CC_CALLBACK_0(HUDLayer::move, this, PlayerState::LEFT_MOVE));
    itemSave->setCallback(CC_CALLBACK_1(HUDLayer::menuSaveCallback, this));
    itemMenu->setCallback(CC_CALLBACK_1(HUDLayer::backToMenuCallback, this));
    
    auto menu = Menu::create(itemUp, itemDown, itemLeft, itemRight, itemSave, itemMenu, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setPosition(0, 0);
    this->addChild(menu);
    
    itemUp->setPosition(Vec2(100, 70));
    itemDown->setPosition(Vec2(100, 20));
    itemLeft->setPosition(Vec2(60, 50));
    itemRight->setPosition(Vec2(150, 50));
    itemSave->setPosition(Vec2(30, 290));
    itemSave->setAnchorPoint(cocos2d::Vec2(0, 0));
    itemMenu->setPosition(Vec2(30, 306));
    itemMenu->setAnchorPoint(cocos2d::Vec2(0, 0));
    
    return true;
}

void HUDLayer::menuCallback(Ref *pSender)
{
    
}

void HUDLayer::menuSaveCallback(Ref *pSender)
{
    GameScene* gameScene = (GameScene*)this->getParent();
    LevelLayer* levelScene = (LevelLayer*)gameScene->getChildByTag(GameSceneTag::LEVELSCENE);
    Player* player = gameScene->player;
    int score = gameScene->getScore();
    if (gameScene->gameMode == GameModeTag::CUSTOM)
        gameScene->level = 2;
    int playerPosX = player->getPosition().x;
    int playerPosY = player->getPosition().y;
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dSCORE", gameScene->slot).c_str(), score);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dPLAYERX", gameScene->slot).c_str(), playerPosX);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dPLAYERY", gameScene->slot).c_str(), playerPosY);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dLEVEL", gameScene->slot).c_str(), gameScene->level);
    
    for(int i = 0 ; i < 5; i++)
    {
        if(levelScene->getChildByTag(i+LevelSceneTag::STAR1) != nullptr)
        {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dSTAR%dX", gameScene->slot, i+1).c_str(), levelScene->getChildByTag(i+LevelSceneTag::STAR1)->getPosition().x);
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dSTAR%dY", gameScene->slot, i+1).c_str(), levelScene->getChildByTag(i+LevelSceneTag::STAR1)->getPosition().y);
        } 
        else
        {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dSTAR%dX", gameScene->slot, i+1).c_str(), -1);
        }
    }
    
    for(int i = 0; i < 5; i++)
    {
        if(levelScene->getChildByTag(i+LevelSceneTag::BOMB1) != nullptr)
        {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dBOMB%dX", gameScene->slot, i+1).c_str(), levelScene->getChildByTag(i+LevelSceneTag::BOMB1)->getPosition().x);
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dBOMB%dY", gameScene->slot, i+1).c_str(), levelScene->getChildByTag(i+LevelSceneTag::BOMB1)->getPosition().y);
        }
        else
        {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%dBOMB%dX", gameScene->slot, i+1).c_str(), -1);
        }
    }
    
    UserDefault::getInstance()->flush();
}

void HUDLayer::backToMenuCallback(Ref *pSender)
{
    Director::getInstance()->replaceScene(MenuScene::create());
}

void HUDLayer::move(PlayerState state)
{
    GameScene* gameScene = (GameScene*)this->getParent();
    auto player = gameScene->player;
    player->move(state);
}

void HUDLayer::setLabelText(int target, const std::string &text)
{
    switch (target)
    {
        case HUDLayerTag::LABELSCORE:   ((Label*)this->getChildByTag(HUDLayerTag::LABELSCORE))->setString(text);    break;
        case HUDLayerTag::LABELLEVEL:   ((Label*)this->getChildByTag(HUDLayerTag::LABELLEVEL))->setString(text);    break;
    }
}
