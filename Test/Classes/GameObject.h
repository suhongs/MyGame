//
//  GameObject.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/08.
//

#pragma once

#include "cocos2d.h"

class GameObject
{
    
public:
    virtual void onCollisionEnter(GameObject* pObj);
};
