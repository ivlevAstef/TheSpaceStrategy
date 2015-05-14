/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GAME_LAYER_H__
#define _COMPONENTS_VIEW_GAME_LAYER_H__

#include "../Component.h"
#include "GameView.h"
#include "GridView.h"
#include "Common/GameTouchEvents.h"
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

    private:
      GameLayer();

      virtual void onEnter() override;
      virtual void onExit() override;

      bool onTouchBegan(cocos2d::Touch*     touch, cocos2d::Event* unused_event);
      void onTouchMoved(cocos2d::Touch*     touch, cocos2d::Event* unused_event);
      void onTouchEnded(cocos2d::Touch*     touch, cocos2d::Event* unused_event);
      void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
      void onMouseDown(cocos2d::Event* event);
      void onMouseMoved(cocos2d::Event* event);
      void onMouseUp(cocos2d::Event* event);

#endif

      void move(cocos2d::Vec2 move);
      
      bool createData(cocos2d::Touch* touch, Common::GameTouchData& data);
    private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
      cocos2d::Vec2 m_previousCursorLocation;
#endif

      class AreaLayer: public cocos2d::Layer {
      public:
        static AreaLayer* create();

      private:
        void visitGameView(cocos2d::Node* node, cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags);
        virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
      };

      GridView* m_grid;
      cocos2d::Sprite* m_background;
      AreaLayer* m_area;
    };
  };
};


#endif // _COMPONENTS_VIEW_GAME_LAYER_H__
