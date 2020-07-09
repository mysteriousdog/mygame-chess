//
//  SceneStart.hpp
//  MyGame
//
//  Created by 朱黎华 on 2020/7/6.
//

#ifndef SceneStart_hpp
#define SceneStart_hpp

#include "MouseTest.hpp"
#include "cocos2d.h"
#include "SceneGame.hpp"
USING_NS_CC;

class SceneStart : public Layer{
public:
    //used to created a scene we call startScene
    static Scene* createScene();
    
    //used to init the startscene
    bool init();
    
    //create func, used to create a object
    CREATE_FUNC(SceneStart);
    
    
    
    
    // corresponding to the start stone with red and black
    Sprite* _red;
    Sprite* _black;
    
    //@overwrite
    //update func in this layer
    void update(float);
    
    // judge the selected side is red or black
    bool _selected;
    
    // click listen func
    void onMouseDown(EventMouse *event);
    void onMouseUp(EventMouse *event);
};

#endif /* SceneStart_hpp */
