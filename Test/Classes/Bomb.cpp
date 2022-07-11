//
//  Bomb.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/06.
//

#include "Bomb.h"

Bomb::Bomb(GLfloat lineWidth)
: cocos2d::DrawNode(lineWidth)
{

}

Bomb* Bomb::create(GLfloat defaultLineWidth)
{
    Bomb* ret = new (std::nothrow) Bomb(defaultLineWidth);
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool Bomb::init()
{
    if(DrawNode::init() == false)
        return false;
    
    Vec2 rec[3];
    rec[0] = Vec2(-10, -10);
    rec[1] = Vec2(10, -10);
    rec[2] = Vec2(0, 10);
    
    drawPolygon(rec, 3, Color4F::RED, 1, Color4F::RED);
    
    setContentSize(Size(20, 20));
    setAnchorPoint(Vec2(0,0));
    
    return true;
}

cocos2d::Rect Bomb::getBoundingBox()
{
    cocos2d::Rect rec(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height);
    
    return rec;
}


void Bomb::onCollisionEnter(GameObject* pColObj)
{
    Player* pPlayer = dynamic_cast<Player*>(pColObj);
    if(pPlayer!=nullptr)
    {
        GameScene* gameScene = (GameScene*)pPlayer->getParent();
        gameScene->endGame();
    }
}
