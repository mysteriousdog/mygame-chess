//
//  Stone.hpp
//  MyGame
//
//  Created by 朱黎华 on 2020/7/1.
//

#ifndef Stone_hpp
#define Stone_hpp

#include <cocos2d.h>
//#include <string>
USING_NS_CC;

class Stone : public Sprite{
public:
    Stone();
    static Stone* create(int id, bool red);
    bool init(int id, bool red);
    void reset(bool red);
    enum TYPE{
        JIANG,
        SHI,
        XIANG,
        CHE,
        MA,
        PAO,
        BING
    };
    //record the original stone pos
    static struct InitPos{
        int _x;
        int _y;
        Stone::TYPE _type;
    }_initPos[16];
    
    //record the picture of the stones
    
    static const std::string stonePic[14];
    
    
    //设置_x,_y,_id,_dead,_red变量并且设置get、set方法
    CC_SYNTHESIZE(int, _x, X);
    CC_SYNTHESIZE(int, _y, Y)
    CC_SYNTHESIZE(int, _id, ID)
    CC_SYNTHESIZE(bool, _dead, Dead)
    CC_SYNTHESIZE(bool, _red, Red)
    CC_SYNTHESIZE(TYPE, _type, Type)
};

#endif /* Stone_hpp */
