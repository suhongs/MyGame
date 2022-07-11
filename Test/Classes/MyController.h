//
//  MyMenuItem.hpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#pragma once

#include "cocos2d.h"

class MyController : public cocos2d::MenuItemLabel
{
private:
    bool isHolded_ = false;
    std::function<void()> holdCallback_;
    
public:
    static MyController* create(const std::string &text,int size, const cocos2d::ccMenuCallback& callback);
    
public:
    virtual void onEnter() override;
    virtual void update(float delta) override;
    
public:
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    
public:
    void setHoldCallback(std::function<void()> holdCallback) { holdCallback_ = holdCallback; }

public:
    void onTouchHold();
    
};
