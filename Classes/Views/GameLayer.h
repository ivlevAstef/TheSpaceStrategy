/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_VIEW_GAME_LAYER_H__
#define _SIA_THE_SPACE_STRATEGY_VIEW_GAME_LAYER_H__

#include "GameView.h"

#include "cocos2d.h"

#include "Common/ViewMath.h"
#include "Models/Area.h"
#include <memory>
#include <vector>

namespace Views
{
  class GameLayer: public cocos2d::Layer {
  public:
    COCOS2D_FUNC1(GameLayer, Models::AreaPtr);
    bool init(Models::AreaPtr pArea);

    void draw(const Common::ViewMath& viewMath);

    void addGameView(GameView* child);
    void eraseGameView(GameView* child);

    void setBackground(std::string backgroundId);
    void modificationBackground(cocos2d::Color3B color);

  public:
    typedef SIA::Delegate<cocos2d::Vec2> DTouchBegan;
    SIA::FriendEvent<GameLayer, cocos2d::Vec2> touchBegan;

    typedef SIA::Delegate<cocos2d::Vec2> DTouchMoved;
    SIA::FriendEvent<GameLayer, cocos2d::Vec2> touchMoved;

    typedef SIA::Delegate<cocos2d::Vec2> DTouchEnded;
    SIA::FriendEvent<GameLayer, cocos2d::Vec2> touchEnded;

    typedef SIA::Delegate<cocos2d::Vec2> DMove;
    SIA::FriendEvent<GameLayer, cocos2d::Vec2> move;

    typedef SIA::Delegate<cocos2d::Vec2> DErase;
    SIA::FriendEvent<GameLayer, cocos2d::Vec2> erase;

  private:
    virtual void onEnter() override;
    virtual void onExit() override;

    bool onTouchBegan(cocos2d::Touch*     touch, cocos2d::Event* unused_event);
    void onTouchMoved(cocos2d::Touch*     touch, cocos2d::Event* unused_event);
    void onTouchEnded(cocos2d::Touch*     touch, cocos2d::Event* unused_event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    void onMouseDown(cocos2d::Event* event);
    void onMouseMoved(cocos2d::Event* event);
#else
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event);
#endif

      
  private:
    int m_touchesCount;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    cocos2d::Vec2 m_previousCursorLocation;
#endif

    Models::AreaPtr m_pAreaModel;

    cocos2d::Sprite* m_background;
    cocos2d::Layer* m_area;
    cocos2d::DrawNode* m_pAreaNode;
  };
};


#endif // _SIA_THE_SPACE_STRATEGY_VIEW_GAME_LAYER_H__
