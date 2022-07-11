//
//  Star.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#include "Star.h"
#include "GameScene.h"
#include "LevelLayer.h"
#include "cocos2d.h"

Star::Star(GLfloat lineWidth)
: _lineWidth(lineWidth)
, _defaultLineWidth(lineWidth)
{
    _blendFunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        /** listen the event that renderer was recreated on Android/WP8 */
        this->setupBuffer();
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}

Star* Star::create(GLfloat defaultLineWidth)
{
    Star* ret = new (std::nothrow) Star(defaultLineWidth);
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

bool Star::init()
{
    if(DrawNode::init() == false)
        return false;
    
    Vec2 rec[3];
    rec[0] = Vec2(-10, -10);
    rec[1] = Vec2(10, -10);
    rec[2] = Vec2(0, 10);
    
    drawPolygon(rec, 3, Color4F::YELLOW, 1, Color4F::YELLOW);
    
    setContentSize(Size(20, 20));
    setAnchorPoint(Vec2(0,0));
    
    return true;
}

cocos2d::Rect Star::getBoundingBox()
{
    cocos2d::Rect rec(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height);
    
    return rec;
}


void Star::onCollisionEnter(GameObject* pColObj)
{
    Player* pPlayer = dynamic_cast<Player*>(pColObj);
    if(pPlayer!=nullptr)
    {
        GameScene* gameScene = (GameScene*)pPlayer->getParent();
        gameScene->getPoint();
        removeFromParent();
    }
}
