/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GAME_LAYER_H__
#define _COMPONENTS_VIEW_GAME_LAYER_H__

#include "../Component.h"
#include "GameView.h"
#include "GridView.h"
#include "cocos2d.h"
#include <memory>
#include <vector>

namespace Components
{
  namespace View
  {
    class GameLayer: public cocos2d::Layer, public Component {
    public:
      DEFINE_COMPONENT(GameLayer);

      static GameLayer* create();

      void addGameView(GameView* child);

      void setBackground(std::string backgroundId);
      void modificationBackground(cocos2d::Color3B color);

      void setGridView(size_t width, size_t height, size_t cellSize);

      typedef SIAUtils::Delegate<size_t, size_t, cocos2d::Vec2> DClickCell;
      SIAUtils::FriendEvent<GameLayer, size_t, size_t, cocos2d::Vec2> clickCell;

    private:
      GameLayer();

      virtual void onEnter() override;
      virtual void onExit() override;

      virtual bool onTouchBegan(cocos2d::Touch*     touch, cocos2d::Event* unused_event) override;
      virtual void onTouchMoved(cocos2d::Touch*     touch, cocos2d::Event* unused_event) override;
      virtual void onTouchEnded(cocos2d::Touch*     touch, cocos2d::Event* unused_event) override;
      virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;

      
    private:
      GridView* m_grid;
      cocos2d::Sprite* m_background;
      cocos2d::Layer* m_area;
    };
  };
};


#endif // _COMPONENTS_VIEW_GAME_LAYER_H__
