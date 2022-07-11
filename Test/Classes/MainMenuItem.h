//
//  MainMenuItem.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/11.
//

#pragma once
#include "cocos2d.h"

class MainMenuItem : public cocos2d::MenuItemLabel
{
public:
    static MainMenuItem* create(const std::string &text,int size, const cocos2d::ccMenuCallback& callback);
    
};
