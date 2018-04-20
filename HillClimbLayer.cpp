#include <cmath>
#include <map>
#include <chrono>
#include <iostream>

#include "cocos2d.h"
#include "HillClimbLayer.h"
#include "HillClimbUtility.h"
#include "HillClimbRoad.h"

namespace hillclimb {

    std::map<cocos2d::EventKeyboard::KeyCode,
             std::chrono::high_resolution_clock::time_point> HillClimbLayer::keys;

    bool HillClimbLayer::init() {
        if (!Layer::init()) {
            return false;
        }

        const auto director = cocos2d::Director::getInstance();
        const auto winSize = director->getWinSize();
        double winWidth = static_cast<double>(winSize.width);
        double winHeight = static_cast<double>(winSize.height);
    
        double spriteScale = DESIGN_RESOLUTION_SIZE.width / winWidth;
        this->carSprite = cocos2d::Sprite::create("car.png");
        this->carSprite->setScale(spriteScale, spriteScale);

        const auto carSize = this->carSprite->getContentSize();
        double carStartX = carSize.width / 2;
        this->carStartY = winSize.height / 2.0 + carSize.height;
        this->carSprite->setPosition(carStartX, carStartY);
        this->carSprite->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        this->addChild(this->carSprite, 0);
    
        this->car = std::make_shared<HillClimbCar>(carStartX, carStartY, spriteScale);
        
        this->road = std::make_shared<HillClimbRoad>(winWidth, winHeight);
        this->road->reset();
        this->generateRoadParts();

        auto eventListener = cocos2d::EventListenerKeyboard::create();
        director->getOpenGLView()->setIMEKeyboardState(true);
        eventListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
            if (keys.find(keyCode) == keys.end()){
                keys[keyCode] = std::chrono::high_resolution_clock::now();
            }
        };
        eventListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
            keys.erase(keyCode);
        };
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
        this->scheduleUpdate();
    
        return true;
    }

    bool HillClimbLayer::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
        if (keys.find(code) != keys.end())
            return true;
        return false;
    }

    void HillClimbLayer::generateRoadParts() {
        const int MIN_ROAD_SIZE = 2;
        int partCount = this->road->getPartCount();
        std::vector<Coordinates> partCoordPairs = this->road->getPartCoords();

        if (partCount < MIN_ROAD_SIZE)
            return;

        auto drawNode = cocos2d::DrawNode::create();
        drawNode->setName("drawNode");
        for (int i = 0; i < static_cast<int>(partCoordPairs.size()) - 1; ++i)
        {
            Coordinates beginCoords = partCoordPairs.at(i);
            Coordinates endCoords = partCoordPairs.at(i + 1);
            drawNode->drawLine(cocos2d::Point(beginCoords.x, beginCoords.y),
                    cocos2d::Point(endCoords.x, endCoords.y),
                    cocos2d::Color4F::WHITE);
        }
        this->addChild(drawNode);
    }

    void HillClimbLayer::deleteRoadParts() {
        this->removeChildByName("drawNode");
    }

    void HillClimbLayer::update(float dt) {
        cocos2d::Node::update(dt);
        if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
            this->car->updateThrottle(100.0);
        } else if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
            this->car->updateThrottle(-200.0);
        } else {
            this->car->updateThrottle(-10.0);
        }
        
        this->car->update(road, dt);
        
        double transition = this->car->getTransitionX(dt);
        
        /*Get car angle. Use std::fmod for it with STRAIGHT_ANGLE as divisor.
    
          Check if the car is touching the road AND if its angle is over or below some limit, to determine if it has crashed*/
        bool crashed = false;
        
        if (crashed || transition < -2.0) {
            this->car->reset(carStartY);
            this->road->reset();
        } else {
            this->road->move(transition);
        }

        this->deleteRoadParts();
        this->generateRoadParts();
        this->carSprite->setPositionY(this->car->getPositionY());
        //Set sprite rotation with setRotation(angle / STRAIGHT_ANGLE * 180);
    }

    cocos2d::Scene* HillClimbLayer::createScene() {
        auto scene = cocos2d::Scene::create();
        auto layer = HillClimbLayer::create();

        scene->addChild(layer);
        return scene;
    }
}
