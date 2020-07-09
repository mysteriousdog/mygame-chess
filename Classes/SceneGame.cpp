//
//  SceneGame.cpp
//  ALL_BUILD
//
//  Created by 朱黎华 on 2020/7/8.
//

#include "SceneGame.hpp"

// constructer func of SceneGame
SceneGame::SceneGame(){
    
}

//to create a layer called SceneGame and a Scene ,add layer to Scene.
Scene* SceneGame::createScene(bool red){
    Scene* scene = Scene::create();
    
    SceneGame* layer = SceneGame::create(red);
    
    scene->addChild(layer);
    return scene;
}

// create a scenegame layer
SceneGame* SceneGame::create(bool red){
    
    auto pRet = new(std::nothrow) SceneGame();
    if(pRet && pRet->init(red)){
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

// init the SceneGame layer, red declare the user is redside or blackside
bool SceneGame::init(bool red){
    // use the super init first
    if(!Layer::init()){
        return false;
    }
    
    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseUp =  CC_CALLBACK_1(SceneGame::clickUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(SceneGame::clickDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // init the plate and stone offset
    this->_plateOffset = Vec2(0,2);
    this->_stoneOffset = Vec2(99,60);
    
    //init the distance between stones
    this->_d = 78;
    
    // init that no stone is selected
    _selectId = -1;
    
    //init the turn of player(player always get the first turn)
    _redTurn  = true;
    
    // init the player side
    _redSide = red;
    
    //init the game status
    this->status = STATUS::PLAYING;
    
    //init the win stone
    _winStoneId = -1;
    
    //init win picture
    _winWindow = Sprite::create("yingjiemian.png");
    addChild(_winWindow,1500);
    _winWindow->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    _winWindow->setVisible(false);
    
    // add desk sprite
    auto desk = Sprite::create("floor.jpg");
    this->addChild(desk,0);
    
    // set desk position and scale
    desk->setPosition(Vec2(visibleSize.width /2, visibleSize.height / 2));
    desk->setScaleX(visibleSize.width / desk->getContentSize().width);
    desk->setScaleY(visibleSize.height / desk->getContentSize().height);
    
     
    //add plate
    auto plate = Sprite::create("background.png");
    this->addChild(plate,1);
    
    plate->setPosition(Vec2(visibleSize.width /2 + _plateOffset.x, visibleSize.height / 2 + _plateOffset.y));
    //plate->setScale((visibleSize.height - _plateOffset.y*2 )/ plate->getContentSize().height);
    
    //init all the stone in plate(side and position is random, need to be reset)
    for(int i =0;i<32;i++){
        _s[i] = Stone::create(i, red);
        addChild(_s[i],2);
        
        _s[i]->setPosition(getStonePos(_s[i]));
        
        _s[i]->setVisible(true);
    }
    
    // selected png
    _selectSprite = Sprite::create("selected.png");
    
    //_selectSprite->setPositionZ(1000);
    
    _selectSprite->setScale(1.8f);
    _selectSprite->setVisible(false);
    addChild(_selectSprite,1000);
    
    
    return true;
    
}

// response click down
void SceneGame::clickDown(Event* e){
    
}

// response click up
void SceneGame::clickUp(Event *e){
    if(status == STATUS::PAUSE || status == STATUS::END){
        return;
    }
    EventMouse* event = (EventMouse*)e;
    std::string str = "click x & y: ";
    float _x = event->getCursorX();
    float _y = event->getCursorY();
    /*
    str += std::to_string(_x);
    str += " ";
    str += std::to_string(_y);
    CCLOG(str.c_str());
     */
    Vec2 cPos = Vec2(_x,_y);
    /*
    //judge if click a stone,if so show select png
    for(int i =0;i<32;i++){
        if(!_s[i]->getDead() && _s[i]->getBoundingBox().containsPoint(cPos)){
            setSelectId(i);
            break;
        }
    }
     */
    Vec2 stonePos;
    for(int x = 0;x<9;x++){
        for(int y = 0;y<10;y++){
            stonePos = getStonePos(x,y);
            if(cPos.getDistance(stonePos) <= _d/2){
                if(_selectId == -1){
                    setSelectId(getStone(x, y));
                }
                else{
                    moveStone(_selectId, getStone(x, y), x, y);
                }
                
            }
        }
    }
    
    
}

//used to get the real position of the point on plate
Rect SceneGame::getPlatePointRec(int x, int y){
    
    Vec2 vec =  Vec2(x * _d,y * _d) + _stoneOffset;
}

// get a stone position
Vec2 SceneGame::getStonePos(Stone* stone){
    int _x = stone->getX() * _d;
    int _y = stone->getY() * _d;
    
    return Vec2(_x,_y) + _stoneOffset;
}

//get a stone pos
Vec2 SceneGame::getStonePos(int x,int y){
    int _x = x * _d;
    int _y = y * _d;
    
    return Vec2(_x,_y) + _stoneOffset;
}

//get the stone id according to the x,y position
int SceneGame::getStone(int x, int y){
    Stone* s;
    
    for(int i=0;i<32;i++){
        s = _s[i];
        
        if(s->getX() == x && s->getY() == y && !s->getDead()){
            return s->getID();
        }
    }
    return -1;
}

//used to set the selected stone id, to show the selected png on the right pos
void SceneGame::setSelectId(int id){
    if(id == -1){
        return;
    }
    //if is not the right turn(player now cannot do playing things)
    /*
    if(_s[id]->getRed() != _redTurn){
        return;
    }
     */
    
    if((_redTurn && _s[id]->getRed() == _redSide) || (!_redTurn && _s[id]->getRed() != _redSide)){
        _selectId = id;
        
        _selectSprite->setVisible(true);
        
        _selectSprite->setPosition(_s[id]->getPosition());
    }
    
}

//used to move the Stone
void SceneGame::moveStone(int moveId, int killId, int x, int y){
    // if killstone is alive && in the same side of the owner side
    if(killId != -1 && _s[moveId]->getRed() == _s[killId]->getRed()){
        setSelectId(killId);
        return;
    }
    //judge if this move action can be done or not
    bool bCanMove = canMove(moveId,killId,x,y);
    
    if(bCanMove == false){
        return;
    }
    
    //record the step
    Step* step = Step::create(moveId, killId, _s[moveId]->getX(), _s[moveId]->getY(), x, y);
    _setps.pushBack(step);
    
    //transform the position data of move stone
    _s[moveId]->setX(x);
    _s[moveId]->setY(y);
    
    //do the movev action
    auto move = MoveTo::create(.5f, getStonePos(x,y));
    
    //auto call = CC_CALLFUNCND_SELECTOR(SceneGame::moveComplete);
    
    //auto call = CC_CALLBACK_1(SceneGame::moveComplete, this);
    
    auto call = CallFuncN::create(CC_CALLBACK_1(SceneGame::moveComplete, this, killId));
    
    auto seq = Sequence::create(move, call, NULL);
    _s[moveId]->setPositionZ(_s[moveId]->getPositionZ() + 1);
    
    _s[moveId]->runAction(seq);
    
}

//used to judge if a stone can move or not
bool SceneGame::canMove(int moveId, int killId, int x , int y){
    
    auto stone = _s[moveId];
    
    switch (stone->getType()) {
        case Stone::JIANG:
            return canMoveJIANG(moveId, killId,  x ,  y);
            break;
        case Stone::SHI:
            return canMoveSHI(moveId, killId,  x ,  y);
            break;
        case Stone::XIANG:
            return canMoveXIANG(moveId, killId,  x ,  y);
            break;
        case Stone::MA:
            return canMoveMA(moveId, killId,  x ,  y);
            break;
        case Stone::CHE:
            return canMoveCHE(moveId, killId,  x ,  y);
            break;
        case Stone::PAO:
            return canMovePAO(moveId, killId,  x ,  y);
            break;
        case Stone::BING:
            return canMoveBING(moveId, killId,  x ,  y);
            break;
        default:
            break;
    }
    
    return true;
    
}

//complete the move stone process
void SceneGame::moveComplete(Node* moveStone, int killId){
    
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    
    if(killId != -1){
        _s[killId]->setDead(true);
        
        _s[killId]->setVisible(false);
        
        if(Stone::JIANG == _s[killId]->getType()){
            CCLOG("you fucking win!");
            if(killId == 4){
                _winStoneId = 20;
            }
            else{
                _winStoneId = 4;
            }
            win();
            
        }
    }
    _selectId = -1;
    
    _selectSprite->setVisible(false);
    
    _redTurn = !_redTurn;
     
}


bool SceneGame::canMoveJIANG(int moveId, int killId, int x , int y){
    if(killId != -1){
        auto skill = _s[killId];
        // when is goning to kill the JIANG, the move action same as CHE
        if(skill->getType() == Stone::JIANG){
            return canMoveCHE(moveId, killId, x, y);
        }
    }
    // get the distance betwwen ower JIANG and the kill stone
    auto stone = _s[moveId];
    int mx = stone->getX();
    int my = stone->getY();
    
    int dis = abs(x - mx) + abs(y - my);
    
    // if the distance == 1 and the x is in house
    if(dis == 1){
        // if its redturn and y in house
        if( _redTurn && inBoundingArea(x, y, 3, 5, 0, 2)){
            return true;
        }
        // if its black turn and y in house
        if( !_redTurn && inBoundingArea(x, y, 3, 5, 7, 9)){
            return true;
        }
    }
    return false;
}

bool SceneGame::canMoveSHI(int moveId, int killId, int x , int y){
    auto s = _s[moveId];
    int mx = s->getX();
    int my = s->getY();
    if(inDiagonal(mx, my, x, y)){
        if(_redTurn && inBoundingArea(x, y, 3, 5, 0, 2)){
            return true;
        }
        if(!_redTurn && inBoundingArea(x, y, 3, 5, 7, 9)){
            return true;
        }
    }
    return false;
}

bool SceneGame::canMoveXIANG(int moveId, int killId, int x , int y){
    auto s = _s[moveId];
    int mx = s->getX();
    int my = s->getY();
    if(inDiagonal(mx, my, x, y, 2) && getStone(x-1,y-1) == -1){
        if(_redTurn && inBoundingArea(x, y, 0, 8, 0, 4)){
            return true;
        }
        if(!_redTurn && inBoundingArea(x, y, 0, 8, 5, 9)){
            return true;
        }
    }
    return false;
}

bool SceneGame::canMoveMA(int moveId, int killId, int x , int y){
    auto s = _s[moveId];
    int mx = s->getX();
    int my = s->getY();
    
    if(getAbsDistance(mx, my, x, y) == 3){
        if(x - mx == 1 && y - my == 2 && getStone(mx, my+1) == -1){
            return true;
        }
        if(x - mx == 2 && y - my == 1 && getStone(mx+1, my) == -1){
            return true;
        }
        if(x - mx == 2 && y - my == -1 && getStone(mx+1, my) == -1){
            return true;
        }
        if(x - mx == 1 && y - my == -2 && getStone(mx, my-1) == -1){
            return true;
        }
        if(x - mx == -1 && y - my == -2 && getStone(mx, my-1) == -1){
            return true;
        }
        if(x - mx == -2 && y - my == -1 && getStone(mx-1, my) == -1){
            return true;
        }
        if(x - mx == -2 && y - my == 1 && getStone(mx-1, my) == -1){
            return true;
        }
        if(x - mx == -1 && y - my == 2 && getStone(mx, my+1) == -1){
            return true;
        }
    }
    return false;
}

bool SceneGame::canMoveCHE(int moveId, int killId, int x , int y){
    auto stone = _s[moveId];
    int mx = stone->getX();
    int my = stone->getY();
    
    // if not in the same coord,return false
    if(x != mx && y != my){
        return false;
    }
    
    if(getStonesCount(x, y, mx, my) !=0){
        return false;
    }
    return true;
    
}

bool SceneGame::canMovePAO(int moveId, int killId, int x , int y){
    //if like CHE, just move like it
    if(canMoveCHE(moveId, killId, x, y) && killId == -1){
        return true;
    }
    // if can do not in the CHE move mode
    auto stone = _s[moveId];
    int mx = stone->getX();
    int my = stone->getY();
    // if in same x ,not in CHE mode
    if(x == mx && killId != -1 && getStonesCount(mx, my, x, y) == 1){
        return true;
    }
    if(y == my && killId != -1 && getStonesCount(mx, my, x, y) == 1){
        return true;
    }
    return false;
}

bool SceneGame::canMoveBING(int moveId, int killId, int x , int y){
    //when BING in its own side, it can only move forward,
    // when BING in enemys plate , it can move forward,left and right, no back
    auto stone = _s[moveId];
    int mx = stone->getX();
    int my = stone->getY();
    if(_redTurn){
        if(inBoundingArea(mx, my, 0, 8, 3, 4) && x == mx && y - my == 1){
            return true;
        }
        if(inBoundingArea(mx, my, 0, 8, 5, 9)){
            if(x == mx && y - my == 1){
                return true;
            }
            if(y == my && abs(x - mx) == 1){
                return true;
            }
        }
        return false;
    }
    if(!_redTurn){
        if(inBoundingArea(mx, my, 0, 8, 5, 6) && x == mx && y - my == -1){
            return true;
        }
        if(inBoundingArea(mx, my, 0, 8, 0, 4)){
            if(x == mx && y - my == -1){
                return true;
            }
            if(y == my && abs(x - mx) == 1){
                return true;
            }
        }
        return false;
    }
    return false;
}

int SceneGame::getStonesCount(int x,int y,int mx,int my){
    if(x == mx){
        // -1 means coincide
        if(y == my){
            return -1;
        }
        int minY = y > my ? my:y;
        int maxY = y > my ? y:my;
        int count = 0;
        for(int i = minY +1;i<maxY;i++){
            if(getStone(x, i) != -1){
                count++;
            }
        }
        return count;
    }
    if( y == my){
        // -1 means coincide
        if(x == mx){
            return -1;
        }
        int minX = x > mx ? mx:x;
        int maxX = x > mx ? x:mx;
        int count = 0;
        for(int i = minX +1;i<maxX;i++){
            if(getStone(i, y) != -1){
                count++;
            }
        }
        return count;
    }
    // -2 means not in same coord
    return -2;
}

// judge x,y in the area or not,used to judge canmove or not(JIANG,SHI,XIANG)
bool SceneGame::inBoundingArea(int x, int y, int minX, int maxX, int minY, int maxY){
    if(x >= minX && x <= maxX && y >= minY && y <= maxY){
        return true;
    }
    return false;
}

//judge two point si in diagonal or not, the absDistance control the distance in x(or y)
bool SceneGame::inDiagonal(int moveX , int moveY, int killX, int killY,int absDistance){
    if(abs(killX - moveX)  == absDistance && abs(killY - moveY) == absDistance){
        return true;
    }
    return false;
}

// get the absDistance of two point in plate
int SceneGame::getAbsDistance(int moveX , int moveY, int killX, int killY){
    return abs(moveX - killX) + abs(moveY - killY);
}

//show the menue,winWindow,stop game
void SceneGame::showWinWindow(Node* Target){
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    Sprite* s;
    if(_winStoneId == 4){
        s = Sprite::create(Stone::stonePic[0]);
    }
    else if(_winStoneId == 20){
        s = Sprite::create(Stone::stonePic[7]);
    }
    else{
        s= nullptr;
        CCLOG("ERROR in winid");
        return;
    }
    s->setPosition(Vec2(VisibleSize.width/2 , VisibleSize.height / 2 - 50));
    s->setScale(1.8);
    s->setVisible(true);
    addChild(s,2000);
    _winWindow->setVisible(true);
    
    
}

//end game,showthe winner,show the game menu
void SceneGame::win(){
    status = STATUS::END;
    //_s[_winStoneId]->setPositionZ(2001);
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    auto moveto = MoveTo::create(1.2f, Vec2(VisibleSize.width/2 , VisibleSize.height / 2 - 50));
    auto call = CallFuncN::create(CC_CALLBACK_1(SceneGame::showWinWindow, this));
    
    auto seq = Sequence::create(moveto, call, NULL);
    _s[_winStoneId]->runAction(seq);
    
}
