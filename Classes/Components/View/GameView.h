/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_VIEW_GAME_VIEW_H__
#define _COMPONENTS_VIEW_GAME_VIEW_H__

#include "cocos2d.h"
#include "../Component.h"
#include "math/SIAUtils_Point2D.h"
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

      inline void setCell(SIAUtils::Position pos) {
        m_pos = pos;
      }
      inline void setCell(int x, int y) {
        m_pos.x = x; m_pos.y = y;
      }
      inline const SIAUtils::Position& cell() const {
        return m_pos;
      }


    private:
      GameView(std::string viewId);

    private:
      SIAUtils::Position m_pos;

      cocos2d::Sprite* sprite;
    };
  };
};


#endif // _COMPONENTS_VIEW_GAME_VIEW_H__
