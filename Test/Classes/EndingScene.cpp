//
//  EndingScene.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/07.
//

#include "MenuScene.h"
#include "EndingScene.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* EndingScene::createScene()
{
    return EndingScene::create();
}

// on "init" you need to initialize your instance
bool EndingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto labelMenu = Label::createWithTTF("MENU", "fonts/Marker Felt.ttf", 24);
    auto labelEnd = Label::createWithTTF("END", "fonts/Marker Felt.ttf", 24);
    
    auto itemMenu = MenuItemLabel::create(labelMenu, CC_CALLBACK_1(EndingScene::menuResumeCallback, this));
    auto itemEnd = MenuItemLabel::create(labelEnd, CC_CALLBACK_1(EndingScene::menuCloseCallback, this));
    
    auto menu = Menu::create(itemMenu, itemEnd, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}

void EndingScene::menuResumeCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(MenuScene::createScene());
}


void EndingScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
