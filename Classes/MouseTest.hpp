//
//  MouseTest.hpp
//  MyGame
//
//  Created by 朱黎华 on 2020/7/4.
//

#ifndef MouseTest_hpp
#define MouseTest_hpp

#include "Mouse.hpp"
#include "cocos2d.h"

USING_NS_CC;

class MouseTest{
public:
    void onMouseDown(EventMouse *event);
    void onMouseUp(EventMouse *event);
    void onMouseMove(EventMouse *event);
    void onMouseScroll(EventMouse *event);
    static MouseTest* getInstance(){
        static MouseTest* mousetest = new MouseTest();
        return mousetest;
    }
private:
    MouseTest();
};
#endif /* MouseTest_hpp */


