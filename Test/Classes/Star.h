//
//  Star.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#pragma once

USING_NS_CC;

#include "GameScene.h"

class Star : public cocos2d::Sprite, public GameObject
{
public:
    static Star* create(const std::string& filename);
    bool init(const std::string& filename);
    
public:
    virtual void onCollisionEnter(GameObject* pColObj) override;
};
