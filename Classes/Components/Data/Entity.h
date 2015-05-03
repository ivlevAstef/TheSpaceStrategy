/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_DATA_ENTITY_H__
#define _COMPONENTS_DATA_ENTITY_H__

#include "../Component.h"
#include "math/SIAUtils_Point2D.h"
#include <memory>

namespace Components
{
  namespace Data
  {
    class Entity : public Component {
    private:
      static const int CELL_POSITION_X = 100;
      static const int CELL_POSITION_Y = 100;
    public:
      DEFINE_COMPONENT(Entity);

      static Entity* create();

      inline void setCell(SIAUtils::Position pos) {
        m_cell = pos;
        m_real.x = CELL_POSITION_X * pos.x;
        m_real.y = CELL_POSITION_Y * pos.y;
      }
      inline void setCell(int x, int y) {
        m_cell.x = x; m_cell.y = y;
        m_real.x = CELL_POSITION_X * x;
        m_real.y = CELL_POSITION_Y * y;
      }
      inline const SIAUtils::Position& cell() const {
        return m_cell;
      }

      inline const SIAUtils::Position& pos() const {
        return m_real;
      }

    protected:
      SIAUtils::Position m_cell;
      SIAUtils::Position m_real;
    };
  };
};

#endif // _COMPONENTS_DATA_ENTITY_H__
