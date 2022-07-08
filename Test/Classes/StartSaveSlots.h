//
//  SaveSlot.hpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#pragma once

class StartSaveSlots : public cocos2d::Layer
{
public:
    static StartSaveSlots* create();
    virtual bool init() override;
    void menuCallback(Ref* pSender);
    
private:
    
};
