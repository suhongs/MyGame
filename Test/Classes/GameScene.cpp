/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Star.h"
#include "ui/CocosGUI.h"
#include "MyController.h"
#include "MyExit.h"
#include "MyTag.h"
#include "HUDLayer.h"
#include "LevelLayer.h"
#include "string.h"
#include "GameObject.h"
#include "EndingScene.h"


USING_NS_CC;

GameScene* GameScene::create()
{
    GameScene *ret = new (std::nothrow) GameScene();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    hudLayer_ = HUDLayer::create();
    hudLayer_->setTag(GameSceneTag::HUDLAYER);
    this->addChild(hudLayer_);
    
    levelLayer_ = LevelLayer::create();
    levelLayer_->setTag(GameSceneTag::LEVELSCENE);
    this->addChild(levelLayer_);
    
    this->player = Player::create("HelloWorld.png", 100, 200);
    this->player->setTag(GameSceneTag::PLAYER);
    this->addChild(player);

    scheduleUpdate();
    
    return true;
}

void GameScene::update(float dt)
{
    collisionUpdate();
}

void GameScene::collisionUpdate()
{
    Vector<Node*> vecNodeLeft = levelLayer_->getChildren();
    vecNodeLeft.pushBack(player);
    
    Vector<Node*> vecNodeRight = levelLayer_->getChildren();
    vecNodeRight.pushBack(player);
    
    for(int i = 0; i < vecNodeLeft.size()-1; i++)
    {
        GameObject* pGameLeft = dynamic_cast<GameObject*>(vecNodeLeft.at(i));
        if(pGameLeft == nullptr)
            continue;
        for(int j = i+1; j < vecNodeLeft.size(); j++)
        {
            GameObject* pGameRight = dynamic_cast<GameObject*>(vecNodeRight.at(j));
            if(pGameRight == nullptr)
                continue;
            
            // 충돌체크
            bool isCollision = checkCollision(pGameLeft, pGameRight);
            if(false == isCollision)
                continue;

            pGameLeft->onCollisionEnter(pGameRight);
            pGameRight->onCollisionEnter(pGameLeft);
        }
    }
}

bool GameScene::checkCollision(GameObject* pLeft, GameObject* pRight)
{
    Rect rectPLeft = pLeft->getBoundingBox();
    Rect rectPRight = pRight->getBoundingBox();
    
    if(rectPLeft.intersectsRect(rectPRight))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GameScene::getScore()
{
    return this->score;
}

void GameScene::getPoint()
{
    this->setScore(this->getScore()+10);
    
    ((Label*)(hudLayer_->getChildByTag(HUDLayerTag::LABELSCORE)))->setString("Score : " + std::to_string(score));
}

void GameScene::setScore(int score)
{
    this->score = score;
}

void GameScene::getNextStage()
{
    level++;
    removeChild(levelLayer_);
    levelLayer_ = LevelLayer::create();
    levelLayer_->setTag(GameSceneTag::LEVELSCENE);
    ((Label*)(hudLayer_->getChildByTag(HUDLayerTag::LABELLEVEL)))->setString("Level " + std::to_string(level));
    this->addChild(levelLayer_);
}

void GameScene::endGame()
{
    Director::getInstance()->replaceScene(EndingScene::create());
}
