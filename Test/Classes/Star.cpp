//
//  Star.cpp
//  Test-mobile
//
//  Created by clidev-rlatnghd1236 on 2022/07/05.
//

#include "Star.h"
#include "GameScene.h"

Star* Star::create(const std::string& filename)
{
    Star* pStar = new (std::nothrow) Star();
    if (pStar && pStar->init(filename))
    {
        pStar->autorelease();
        return pStar;
    }
    
    CC_SAFE_DELETE(Star);
    return nullptr;
}

bool Star::init(const std::string& filename)
{
    if(initWithFile(filename) == false)
        return false;
    
    setAnchorPoint(Vec2(0, 0));
    setPosition(posX, posY);
    
    return true;
}

void Star::onCollisionEnter(GameObject* pColObj)
{
    Player* pPlayer = dynamic_cast<Player*>(pColObj);
    if(pPlayer!=nullptr)
    {
        removeFromParent();
        
        GameScene* gameScene = (GameScene*)this->getParent()->getParent();
        gameScene->getPoint();
    }
    
}
