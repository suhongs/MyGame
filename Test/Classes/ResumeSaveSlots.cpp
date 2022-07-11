//
//  ResumeSaveSlot.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#include "ResumeSaveSlots.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "string.h"
#include "HUDLayer.h"
#include "Player.h"
#include "LevelLayer.h"
#include "MyTag.h"

ResumeSaveSlots* ResumeSaveSlots::create()
{
    ResumeSaveSlots *ret = new (std::nothrow) ResumeSaveSlots();
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

bool ResumeSaveSlots::init()
{
    cocos2d::Layer::init();
    
    makeSlots();
    
    return true;
}

void ResumeSaveSlots::makeSlots()
{
    cocos2d::Label* labelSlot[6];
    cocos2d::MenuItemLabel* itemSlot[6];
    auto menu = cocos2d::Menu::create(NULL);
    for(int i = 0 ; i < 6; i++)
    {
        labelSlot[i] = cocos2d::Label::createWithTTF(cocos2d::StringUtils::format("Slot %d", i+1), "fonts/Marker Felt.ttf", 24);
        itemSlot[i] = cocos2d::MenuItemLabel::create(labelSlot[i], CC_CALLBACK_1(ResumeSaveSlots::menuCallback, this));
        itemSlot[i]->setTag(i);
        menu->addChild(itemSlot[i]);
    }
    
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(cocos2d::Vec2(0, 0));
    menu->setPosition(cocos2d::Vec2(400, 150));
    this->addChild(menu);
}

void ResumeSaveSlots::menuCallback(Ref *pSender)
{
    cocos2d::MenuItemLabel* item = (cocos2d::MenuItemLabel*) pSender;
    GameScene* gameScene = (GameScene*)GameScene::create();
    HUDLayer* hudLayer = (HUDLayer*)gameScene->getChildByTag(GameSceneTag::HUDLAYER);
    LevelLayer* levelScene = (LevelLayer*)gameScene->getChildByTag(GameSceneTag::LEVELSCENE);
    Label* labelScore = (Label*)hudLayer->getChildByTag(HUDLayerTag::LABELSCORE);
    Label* labelLevel = (Label*)hudLayer->getChildByTag(HUDLayerTag::LABELLEVEL);
    
    for (int i = 0 ; i < 6; i++)
    {
        if (item->getString() == StringUtils::format("Slot %d", i+1))
        {
            if(UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dPLAYERX", i+1).c_str()) == 0.f)
            {
                Director::getInstance()->replaceScene(gameScene);
                return;
            }
                
            int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dSCORE", i+1).c_str());
            labelScore->setString("Score : " + std::to_string(score));
            gameScene->setScore(score);
            
            int level = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dLEVEL", i+1).c_str());
            labelLevel->setString("Level : " + std::to_string(level));
            gameScene->level = level;
            
            Player* player = gameScene->player;
            player->setPosition(UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dPLAYERX", i+1).c_str(), -1),
                                UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dPLAYERY", i+1).c_str(), -1));

            for(int j = 0 ; j < 5; j++)
            {
                if (UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dBOMB%dX", i+1, j+1).c_str()) == -1)
                {
                    levelScene->removeChild(levelScene->getChildByTag(j+LevelSceneTag::BOMB1));
                }
                else
                {
                    levelScene->getChildByTag(j+LevelSceneTag::BOMB1)->setPosition(UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dBOMB%dX", i+1, j+1).c_str()), UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dBOMB%dY", i+1, j+1).c_str()));
                }
                
                if (UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dSTAR%dX", i+1, j+1).c_str()) == -1)
                {
                    levelScene->removeChild(levelScene->getChildByTag(j+LevelSceneTag::STAR1));
                }
                else
                {
                    levelScene->getChildByTag(j+LevelSceneTag::STAR1)->setPosition(UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dSTAR%dX", i+1, j+1).c_str()), UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%dSTAR%dY", i+1, j+1).c_str()));
                }
                
            }
        }
    }
    for(int i = 0 ; i < 10; i++)
    {
        levelScene->getEventDispatcher()->removeEventListener(levelScene->listener[i]);
    }
    Director::getInstance()->replaceScene(gameScene);
}
