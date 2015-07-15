/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_VIEW_GAME_VIEW_H__
#define _SIA_THE_SPACE_STRATEGY_VIEW_GAME_VIEW_H__

#include "SIAEvent.h"

#include "cocos2d.h"
#include "Common/Cocos2dDefines.h"
#include <string>
#include <memory>

namespace Views
{
  class GameView: public cocos2d::Node {
  public:
    COCOS2D_FUNC1(GameView, std::string);
    bool init(std::string viewId);
    
    bool hasPoint(const cocos2d::Vec2& pos);
    bool hasPointWithSelect(const cocos2d::Vec2& pos);    

  public:
    typedef SIA::Delegate<GameView*> DSelect;

    SIA::FriendEvent<GameView, GameView*> select;

  private:
    cocos2d::Sprite* sprite;
  };

};


#endif // _SIA_THE_SPACE_STRATEGY_VIEW_GAME_VIEW_H__
