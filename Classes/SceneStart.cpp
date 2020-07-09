//
//  SceneStart.cpp
//  MyGame
//
//  Created by 朱黎华 on 2020/7/6.
//

#include "SceneStart.hpp"


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* SceneStart::createScene(){
    Scene* scene = Scene::create();
    SceneStart* layer = SceneStart::create();
    scene->addChild(layer);
    return scene;
}

bool SceneStart::init(){
    Layer::init();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto* bk = Sprite::create("background.png");
    if (bk == nullptr)
    {
        problemLoading("'background.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        bk->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        
        // add the sprite as a child to this layer
        addChild(bk,1);
    }
    
    
    
    
    Sprite* bkr  = Sprite::create("bkg2.png");
    addChild(bkr,2);
    Sprite* bkb = Sprite::create("bkg1.png");
    addChild(bkb,2);
    
    bkr->setPosition(Vec2(visibleSize.width/2 - 100,visibleSize.height/2));
    bkb->setPosition(Vec2(visibleSize.width/2 + 100,visibleSize.height/2));
    
    bkr->setScale(1.8);
    bkb->setScale(1.8);
    
    _red = bkr;
    _black = bkb;
    
    //add mouseclick listener
    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseUp =  CC_CALLBACK_1(SceneStart::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(SceneStart::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    
    return true;
    
}


void SceneStart::onMouseDown(EventMouse *event){
    //CCLOG("hsjashajhsj");
}
void SceneStart::onMouseUp(EventMouse *event){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // get the vec2 of click ponit
    Vec2 clickPt = Vec2(event->getCursorX(),event->getCursorY());
    bool bClickStone = false;
    /*
    std::string str = "click x & y: ";
    str += std::to_string(event->getCursorX());
    str += "  ";
    str += std::to_string(event->getCursorY());
    CCLOG(str.c_str());
    //init the stone click status is false
    
    
     78.25
     78 \ 29
    str = "original x & y";
    auto x = _red->getPositionX();
    auto y = _red->getPositionY();
    auto rect = _red->getBoundingBox();
    str += std::to_string(rect.origin.x);
    str += "  ";
    str += std::to_string(rect.origin.y);
    CCLOG(str.c_str());
     */
    // if the click point inside the red stone
    if(_red->getBoundingBox().containsPoint(clickPt)){
        //set the select stone is red
        this->_selected = true;
        
        // set the click status of stone is true
        bClickStone = true;
    }
    //if black side
    else if(_black->getBoundingBox().containsPoint(clickPt)){
        // select black stone
        this->_selected = false;
        bClickStone = true;
    }
    
    // if click the start stone show the animation and trans the scene to play
    if(bClickStone){
        //animation of move stones
        
        auto moveto1 = MoveTo::create(1, Vec2(visibleSize.width/2,visibleSize.height/2));
        auto moveto2 = MoveTo::create(1, Vec2(visibleSize.width/2,visibleSize.height/2));
        
        auto rotate1 = RotateBy::create(1, 360);
        auto rotate2 = RotateBy::create(1, -360);
        
        auto spawn1 = Spawn::create(moveto1, rotate1, NULL);
        auto spawn2 = Spawn::create(moveto2, rotate2, NULL);
        
        _red->runAction(spawn1);
        _black->runAction(spawn2);
        
        scheduleUpdate();
        
    }
}

void SceneStart::update(float){
    float x1 = _red->getPositionX();
    float x2 = _black->getPositionX();
    //if the distance between _red and _black is smaller than the contentsize of stones
    // do the scene replace
    if(abs(x1 - x2) <= _red->getCenterRect().size.width){
        Director::getInstance()->replaceScene(SceneGame::createScene(this->_selected));
        //CCLOG("what the fuck!");
    }
}
