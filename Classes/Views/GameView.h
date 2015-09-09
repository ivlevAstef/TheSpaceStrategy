/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_VIEW_GAME_VIEW_H__
#define _SIA_THE_SPACE_STRATEGY_VIEW_GAME_VIEW_H__

#include "SIAEvent.h"

#include "cocos2d.h"
#include "Common/Cocos2dDefines.h"

#include "Models/Entity.h"

#include <string>
#include <memory>

namespace Views
{
  class GameView: public cocos2d::Node {
  public:
    COCOS2D_FUNC2(GameView, std::string, Models::EntityPtr);
    bool init(std::string viewId, Models::EntityPtr pModel);
    
    bool hasPoint(const cocos2d::Vec2& pos);
    bool hasPointWithSelect(const cocos2d::Vec2& pos);

    void setEnergyState(bool connected);
    void setEnergyRange(cocos2d::Vec2 range, bool visible);

  public:
    typedef SIA::Delegate<GameView*> DSelect;

    SIA::FriendEvent<GameView, GameView*> select;

  private:
    Models::EntityPtr m_pModel;

    cocos2d::Sprite* m_sprite;
    cocos2d::DrawNode* m_energyRangeNode;
  };

};


#endif // _SIA_THE_SPACE_STRATEGY_VIEW_GAME_VIEW_H__
