/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HUDLayer.h"
#include "Player.h"
#include "StartSaveSlots.h"
#include "LevelLayer.h"
#include "ResumeSaveSlots.h"
#include "CustomSaveSlots.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto labelStart = Label::createWithTTF("START", "fonts/Marker Felt.ttf", 24);
    auto labelResume = Label::createWithTTF("RESUME", "fonts/Marker Felt.ttf", 24);
    auto labelCustom = Label::createWithTTF("CUSTOM", "fonts/Marker Felt.ttf", 24);
    auto labelEnd = Label::createWithTTF("END", "fonts/Marker Felt.ttf", 24);
    
    
    auto itemStart = MenuItemLabel::create(labelStart, CC_CALLBACK_1(MenuScene::menuStartCallback, this));
    auto itemResume = MenuItemLabel::create(labelResume, CC_CALLBACK_1(MenuScene::menuResumeCallback, this));
    auto itemCustom = MenuItemLabel::create(labelCustom, CC_CALLBACK_1(MenuScene::menuCustomCallback, this));
    auto itemEnd = MenuItemLabel::create(labelEnd, CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    
    auto menu = Menu::create(itemStart, itemResume, itemCustom, itemEnd, NULL);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu);
    
    return true;
}


void MenuScene::menuStartCallback(Ref* pSender)
{
    if (this->getChildByTag(0)!=nullptr)
    {
        this->removeChild(getChildByTag(0));
        return;
    }
    
    if (this->getChildByTag(2) != nullptr)
    {
        this->removeChild(getChildByTag(2));
        return;
    }
    
    if (this->getChildByTag(1)!= nullptr)
    {
        this->removeChild(getChildByTag(1));
        return;
    }
    
    StartSaveSlots* saveSlot = StartSaveSlots::create();
    saveSlot->setTag(0);
    this->addChild(saveSlot);
    
    
    //Director::getInstance() ->replaceScene(GameScene::create());
}


void MenuScene::menuResumeCallback(Ref* pSender)
{
    if (this->getChildByTag(0)!=nullptr)
    {
        this->removeChild(getChildByTag(0));
        return;
    }
    
    if (this->getChildByTag(2) != nullptr)
    {
        this->removeChild(getChildByTag(2));
        return;
    }
    
    if (this->getChildByTag(1)!= nullptr)
    {
        this->removeChild(getChildByTag(1));
        return;
    }
    
    ResumeSaveSlots* saveSlot = ResumeSaveSlots::create();
    saveSlot->setTag(1);
    this->addChild(saveSlot);
}

void MenuScene::menuCustomCallback(Ref* pSender)
{    
    if (this->getChildByTag(0)!=nullptr)
    {
        this->removeChild(getChildByTag(0));
        return;
    }
    
    if (this->getChildByTag(2) != nullptr)
    {
        this->removeChild(getChildByTag(2));
        return;
    }
    
    if (this->getChildByTag(1)!= nullptr)
    {
        this->removeChild(getChildByTag(1));
        return;
    }
    
    CustomSaveSlots* saveSlot = CustomSaveSlots::create();
    saveSlot->setTag(2);
    this->addChild(saveSlot);
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}



