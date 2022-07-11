//
//  MyExit.cpp
//  Test
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#include "MyExit.h"
#include "cocos2d.h"
#include "GameScene.h"

MyExit::MyExit(GLfloat lineWidth)
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

MyExit* MyExit::create(GLfloat defaultLineWidth)
{
    MyExit* ret = new (std::nothrow) MyExit(defaultLineWidth);
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

bool MyExit::init()
{
    if(DrawNode::init() == false)
        return false;
    
    //
    return true;
}

cocos2d::Rect MyExit::getBoundingBox()
{
    cocos2d::Rect rec(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height);
    
    return rec;
}

void MyExit::onCollisionEnter(GameObject* pColObj)
{
    Player* pPlayer = dynamic_cast<Player*>(pColObj);
    if(pPlayer!=nullptr)
    {
        GameScene* gameScene = (GameScene*)pPlayer->getParent();
        gameScene->getNextStage();
    }
}
