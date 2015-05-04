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
    class Area;
    class Entity : public Component {
    private:
      friend class Area;
    public:
      DEFINE_COMPONENT(Entity);

      static Entity* create();

      inline void setCell(SIAUtils::Position pos) { m_cell = pos; }
      inline void setCell(int x, int y) { m_cell.x = x; m_cell.y = y; }

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
