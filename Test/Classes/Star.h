//
//  Star.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#pragma once

USING_NS_CC;

#include "GameScene.h"

class Star : public DrawNode, public GameObject
{
public:
    Star(GLfloat lineWidth);
    static Star* create(GLfloat defaultLineWidth = cocos2d::DEFAULT_LINE_WIDTH);
    virtual bool init() override;

    virtual cocos2d::Rect getBoundingBox() override;
    virtual void onCollisionEnter(GameObject* pColObj) override;
    
public:
    GLfloat _lineWidth = 0.0f;
    GLfloat _defaultLineWidth = 0.0f;
};
