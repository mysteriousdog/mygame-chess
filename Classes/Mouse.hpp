//
//  Mouse.hpp
//  ALL_BUILD
//
//  Created by 朱黎华 on 2020/7/7.
//

#ifndef Mouse_hpp
#define Mouse_hpp

#include "cocos2d.h"
USING_NS_CC;

class Mouse{
public:
    
    static Mouse* getInstance(){
        static Mouse *m = new Mouse();
        return m;
    }
    CC_SYNTHESIZE(float, _x, X);
    CC_SYNTHESIZE(float, _y, Y);
    CC_SYNTHESIZE(float, _downx, DownX);
    CC_SYNTHESIZE(float, _downy, DownY);
    CC_SYNTHESIZE(float, _upx, UpX);
    CC_SYNTHESIZE(float, _upy, UpY);
private:
    Mouse();
};


#endif /* Mouse_hpp */
