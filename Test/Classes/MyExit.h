//
//  MyExit.hpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class MyExit : public cocos2d::DrawNode, public GameObject
{
public:
    MyExit(GLfloat lineWidth);
    static MyExit* create(GLfloat defaultLineWidth = cocos2d::DEFAULT_LINE_WIDTH);
    virtual bool init() override;
    virtual cocos2d::Rect getBoundingBox() override;
    virtual void onCollisionEnter(GameObject* pColObj) override;
    
public:
    GLfloat _lineWidth = 0.0f;
    GLfloat _defaultLineWidth = 0.0f;
};
