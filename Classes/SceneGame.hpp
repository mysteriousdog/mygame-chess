//
//  SceneGame.hpp
//  ALL_BUILD
//
//  Created by 朱黎华 on 2020/7/8.
//

#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "cocos2d.h"
#include "Stone.hpp"

USING_NS_CC;

class Step : public Ref{
public:
    int _moveid;
    int _killid;
    int _xFrom;
    int _yFrom;
    int _xTo;
    int _yTo;
    
    static Step* create(int moveid, int killid, int xFrom, int yFrom, int xTo, int yTo){
        Step* step = new Step;
        step->_moveid = moveid;
        step->_killid = killid;
        step->_xFrom = xFrom;
        step->_yFrom = yFrom;
        step->_xTo = xTo;
        step->_yTo = yTo;
        
        step->autorelease();
        
        return step;
    }
};

class SceneGame : public Layer{
public:
    SceneGame();
    
    ~SceneGame(){
    }
    
    static Scene* createScene(bool red);
    
    bool init(bool red);
    
    static SceneGame* create(bool red);
    
    Vec2 _plateOffset;
    
    Vec2 _stoneOffset;
    
    // means the distance between stones
    float _d;
    
    //repesent its player side turn or not, it will be init to true in init()
    bool _redTurn;
    
    // reps the player side, true is red ,otherwise black
    bool _redSide;
    
    int _selectId;
    
    // all stones in plate
    Stone* _s[32];
    
    //the selected picture
    Sprite* _selectSprite;
    
    //the winside stone
    int _winStoneId;
    
    //the win picture
    Sprite* _winWindow;
    
    //record all the steps in vector
    Vector<Step*> _setps;
    
    enum STATUS{
        PLAYING,
        PAUSE,
        END,
    };

    //the status of game
    STATUS status;
    
    void clickDown(Event* e);
    
    void clickUp(Event* e);
    
    //get a stone pos
    Vec2 getStonePos(Stone* stone);
    
    //get a stone pos
    Vec2 getStonePos(int x,int y);
    
    // used to get the stone id according to x,y
    int getStone(int x, int y);
    
    //used to set the selected stone id, to show the selected png on the right pos
    void setSelectId(int id);
    
    //used to get the real position of the point on plate
    Rect getPlatePointRec(int x, int y);
    
    //used to move the Stone
    void moveStone(int moveId, int killId, int x, int y);
    
    //used to judge if a stone can move or not
    bool canMove(int moveId, int killId, int x , int y);
    
    //complete the move stone process
    void moveComplete(Node* moveStone, int killId);
    
    bool canMoveJIANG(int moveId, int killId, int x , int y);
    
    bool canMoveSHI(int moveId, int killId, int x , int y);
    
    bool canMoveXIANG(int moveId, int killId, int x , int y);
    
    bool canMoveMA(int moveId, int killId, int x , int y);
    
    bool canMoveCHE(int moveId, int killId, int x , int y);
    
    bool canMovePAO(int moveId, int killId, int x , int y);
    
    bool canMoveBING(int moveId, int killId, int x , int y);
    
    int getStonesCount(int x,int y,int mx,int my);
    
    // judge x,y in the area or not,used to judge canmove or not(JIANG,SHI,XIANG)
    bool inBoundingArea(int x, int y, int minX, int maxX, int minY, int maxY);\
    
    //judge two point si in diagonal or not, the absDistance/2 control the distance of diagonal in x(or y)
    bool inDiagonal(int moveX , int moveY, int killX, int killY,int absDistance = 1);
    
    // get the absDistance of two point in plate
    int getAbsDistance(int moveX , int moveY, int killX, int killY);
    
    //end game,showthe winner,show the game menu
    void win();
    
    //show the menue,winWindow,stop game
    void showWinWindow(Node* Target);
    
    
    /*
    bool visible;
    
    void SetRealPos(Stone* s);
    
    bool getClickPos(Vec2 pt, int &x, int &y);
    
    int getStoneCount(int xo, int yo,int x,int y);
     */
    
};
#endif /* SceneGame_hpp */
