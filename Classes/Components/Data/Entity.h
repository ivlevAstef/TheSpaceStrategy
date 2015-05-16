/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_DATA_ENTITY_H__
#define _COMPONENTS_DATA_ENTITY_H__

#include "../Component.h"
#include "math/SIAUtils_Point2D.h"
#include "Common/Features.h"
#include <memory>

namespace Components
{
  namespace Data
  {
    class Area;
    class Entity : public Component {
    public:
      enum EntityType {
        MainBase,
        Pylon
      };
    private:
      friend class Area;
    public:
      DEFINE_COMPONENT(Entity);

      Entity();

      static Entity* create();
      static void free(Entity* pEntity);

      inline void setCell(SIAUtils::Position pos) { m_cell = pos; }
      inline void setCell(int x, int y) { m_cell.x = x; m_cell.y = y; }

      inline const SIAUtils::Position& cell() const {
        return m_cell;
      }

      inline const SIAUtils::Position& pos() const {
        return m_real;
      }

      inline bool physical() const { return m_features.Bool(m_physical); }
      inline bool generator() const { return m_features.Bool(m_generator); }
      inline bool energy() const { return m_features.Bool(m_energy); }

      EntityType type() const;
      inline Common::Features& features() { return m_features; }

    protected:
      SIAUtils::Position m_cell;
      SIAUtils::Position m_real;

      Common::Features::Cache m_physical;
      Common::Features::Cache m_generator;
      Common::Features::Cache m_energy;
      Common::Features::Cache m_entityType;

      Common::Features m_features;
    };
  };
};

#endif // _COMPONENTS_DATA_ENTITY_H__
