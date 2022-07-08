//
//  CustomSaveSlot.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/07.
//

#pragma once

#include "cocos2d.h"

class CustomSaveSlots : public cocos2d::Layer
{
public:
    static CustomSaveSlots* create();
    virtual bool init() override;
    void menuCallback(Ref* pSender);
    
private:
    
};
