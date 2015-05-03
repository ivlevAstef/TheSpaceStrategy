/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GAME_VIEW_H__
#define _COMPONENTS_VIEW_GAME_VIEW_H__

#include "cocos2d.h"
#include "../Component.h"
#include <string>
#include <memory>

namespace Components
{
  namespace View
  {
    class GameView: public cocos2d::Node, public Component {
    public:
      DEFINE_COMPONENT(GameView);

      static GameView* create(std::string viewId);

    private:
      GameView(std::string viewId);

    private:
      cocos2d::Sprite* sprite;
    };
  };
};


#endif // _COMPONENTS_VIEW_GAME_VIEW_H__
