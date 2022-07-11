//
//  ResumeSaveSlot.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#pragma once
#include "cocos2d.h"

class ResumeSaveSlots : public cocos2d::Layer
{
public:
    static ResumeSaveSlots* create();
    virtual bool init() override;
    void menuCallback(Ref* pSender);
    
public:
    void makeSlots();
    
private:
};
