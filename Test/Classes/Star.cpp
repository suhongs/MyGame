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
