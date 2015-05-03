/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GAME_LAYER_H__
#define _COMPONENTS_VIEW_GAME_LAYER_H__

#include "../Component.h"
#include "GameView.h"
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

    private:
      GameLayer();
    };
  };
};


#endif // _COMPONENTS_VIEW_GAME_LAYER_H__
