//
//  Stone.cpp
//  MyGame
//
//  Created by 朱黎华 on 2020/7/1.
//

#include "Stone.hpp"

Stone::Stone(){};

// the init pos of all the red stones
Stone::InitPos Stone::_initPos[16] = {
    {0,0,Stone::CHE},
    {1,0,Stone::MA},
    {2,0,Stone::XIANG},
    {3,0,Stone::SHI},
    {4,0,Stone::JIANG},
    {5,0,Stone::SHI},
    {6,0,Stone::XIANG},
    {7,0,Stone::MA},
    {8,0,Stone::CHE},
    {1,2,Stone::PAO},
    {7,2,Stone::PAO},
    {0,3,Stone::BING},
    {2,3,Stone::BING},
    {4,3,Stone::BING},
    {6,3,Stone::BING},
    {8,3,Stone::BING},
};

// the picture of all the red stones
const std::string Stone::stonePic[14] = {
    "rshuai.png",
    "rshi.png",
    "rxiang.png",
    "rche.png",
    "rma.png",
    "rpao.png",
    "rbing.png",
    
    "bjiang.png",
    "bshi.png",
    "bxiang.png",
    "bche.png",
    "bma.png",
    "bpao.png",
    "bzu.png"
};

//return the instance of stone after init with id and red
Stone* Stone::create(int id,bool red){
    Stone *s = new Stone();
    s->init(id, red);
    s->autorelease();
    return s;
}

//reset the pos and the status od live of a stone according to its id and color
void Stone::reset(bool red){
    //init a stone of alive
    this->setDead(false);
    
    // if players choose red side
    if(red){
        // if the stone is red
        if(_id < 16){
            this->setX(_initPos[_id]._x);
            this->setY(_initPos[_id]._y);
        }
        //if the stone is black
        else{
            this->setX(8 - _initPos[_id-16]._x);
            this->setY(9 - _initPos[_id-16]._y);
        }
    }
    //if player choose the black side
    else{
        // if the color of this stone is red
        if(_id < 16){
            this->setX(8 - _initPos[_id]._x);
            this->setY(9 - _initPos[_id]._y);
        }
        // if the color of this stone is black
        else{
            this->setX(_initPos[_id-16]._x);
            this->setY(_initPos[_id-16]._y);
        }
    }
}

// init the status of stone, red means the side of players playing,
//true means read-side ,0 means black-side
bool Stone::init(int id, bool red){
    _id = id;
    // init the color of the stone
    _red = _id < 16;
    // init the type
    if(_id < 16){
        setType(_initPos[_id]._type);
    }
    else{
        setType(_initPos[_id - 16]._type);
    }
    
    //get the picId of a stone
    int picId = (_red ? 0:1) * 7 + _type;
    //init the stone with the picture
    Sprite::initWithFile(stonePic[picId]);
    
    //set the scale of stone in scene
    setScale(1.8f);
    
    //init the live and pos of the stone
    reset(red);
    
    return true;
    
}

