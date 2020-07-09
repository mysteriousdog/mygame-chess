//
//  MouseTest.cpp
//  MyGame
//
//  Created by 朱黎华 on 2020/7/4.
//

#include "MouseTest.hpp"


MouseTest::MouseTest(){
    
}


void MouseTest::onMouseDown(EventMouse *event)
{
    // to illustrate the event....
    //EventMouse* e = (EventMouse*)event;
    auto *m = Mouse::getInstance();
    m->setDownX(event->getCursorX());
    m->setDownY(event->getCursorY());
}

void MouseTest::onMouseUp(EventMouse *event)
{
    // to illustrate the event....
    //EventMouse* e = (EventMouse*)event;
    auto *m = Mouse::getInstance();
    m->setUpX(event->getCursorX());
    m->setUpY(event->getCursorY());
}

void MouseTest::onMouseMove(EventMouse *event)
{
    // to illustrate the event....
    //EventMouse* e = (EventMouse*)event;
    /*
    std::string str = "MousePosition X:";
    str = str + std::to_string(event->getCursorX()) + " Y:" + std::to_string(event->getCursorY());
    CCLOG(str.c_str());
     */
    /*
    std::string str = "MousePosition X:";
    this->_x = event->getCursorX();
    this->_y = event->getCursorY();
    str = str + std::to_string(this->_x);
    CCLOG(str.c_str());
     */
}

void MouseTest::onMouseScroll(EventMouse *event)
{
    // to illustrate the event....
    //EventMouse* e = (EventMouse*)event;
    /*
    std::string str = "Mouse Scroll detected, X: ";
    str = str + std::to_string(event->getScrollX()) + " Y: " + std::to_string(event->getScrollY());
    CCLOG(str.c_str());
     */
}
