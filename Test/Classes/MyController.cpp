//
//  MyMenuItem.cpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#include "MyController.h"
#include "GameScene.h"


MyController * MyController::create(const std::string &text, int size, const cocos2d::ccMenuCallback& callback)
{
    auto label = cocos2d::Label::createWithTTF(text, "fonts/Marker Felt.ttf", size);
    
    MyController *ret = new (std::nothrow) MyController();
    ret->initWithLabel(label, NULL);
    ret->autorelease();
    return ret;
}

void MyController::onEnter()
{
    cocos2d::MenuItemLabel::onEnter();
    
    scheduleUpdate();
}

void MyController::update(float delta)
{
    if(isHolded_)
    {
        onTouchHold();
    }
}

void MyController::activate()
{
    MenuItemLabel::activate();
}

void MyController::selected()
{
    MenuItemLabel::selected();
    
    isHolded_ = true;
}

void MyController::unselected()
{
    MenuItemLabel::unselected();
    
    isHolded_ = false;
}

void MyController::onTouchHold()
{
    if(holdCallback_)
    {
        holdCallback_();
    }
}

