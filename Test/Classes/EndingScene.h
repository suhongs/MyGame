//
//  EndingScene.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/07.
//

#pragma once
#include "cocos2d.h"

class EndingScene : public cocos2d::Scene
{
public:
    static Scene* createScene();
    virtual bool init() override;
    
    void menuResumeCallback(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EndingScene);
    
};

