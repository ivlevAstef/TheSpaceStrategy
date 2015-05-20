/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GAME_VIEW_H__
#define _COMPONENTS_VIEW_GAME_VIEW_H__

#include "cocos2d.h"
#include "../Component.h"
#include "event/Event.h"
#include <string>
#include <memory>

namespace Components
{
  namespace View
  {
    class GameView: public cocos2d::Node, public Component {
    public:
      DEFINE_COMPONENT(GameView);
      DEFINE_COCOS2DX_COMPONENT

      static GameView* create(std::string viewId);
      bool hasPoint(const cocos2d::Vec2& pos);
      bool hasPointWithSelect(const cocos2d::Vec2& pos);

    private:
      GameView(std::string viewId);

    public:
      typedef SIAUtils::Delegate<GameView*> DSelect;

      SIAUtils::FriendEvent<GameView, GameView*> select;

    private:
      cocos2d::Sprite* sprite;
    };

  };
};


#endif // _COMPONENTS_VIEW_GAME_VIEW_H__
