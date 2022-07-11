//
//  Bomb.hpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#pragma once
#include "cocos2d.h"
#include "GameScene.h"

class Bomb : public cocos2d::DrawNode , public GameObject
{
public:
    Bomb(GLfloat lineWidth);
    static Bomb* create(GLfloat defaultLineWidth = cocos2d::DEFAULT_LINE_WIDTH);
    virtual bool init() override;

    virtual cocos2d::Rect getBoundingBox() override;
    virtual void onCollisionEnter(GameObject* pColObj) override;
    
public:
    GLfloat _lineWidth = 0.0f;
    GLfloat _defaultLineWidth = 0.0f;
};
