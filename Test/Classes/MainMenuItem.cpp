//
//  MainMenuItem.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/11.
//

#include "MainMenuItem.h"

MainMenuItem * MainMenuItem::create(const std::string &text, int size, const cocos2d::ccMenuCallback& callback)
{
    auto label = cocos2d::Label::createWithTTF(text, "fonts/Marker Felt.ttf", size);
    
    MainMenuItem *ret = new (std::nothrow) MainMenuItem();
    ret->initWithLabel(label, NULL);
    ret->autorelease();
    return ret;
}
