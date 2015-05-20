/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_DATA_ENTITY_H__
#define _COMPONENTS_DATA_ENTITY_H__

#include "../Component.h"
#include "math/SIAUtils_Point2D.h"
#include "Features.h"
#include <memory>

namespace Components
{
  namespace Data
  {
    class Area;
    class Entity: public ComponentRef {
    public:
      enum EntityType {
        MainBase,
        Pylon,
        GetterMineral,
        Minerals,
      };
    private:
      friend class Area;
    public:
      DEFINE_COMPONENT(Entity);

      Entity(Features* features);
      ~Entity() {

      }

      static Entity* create(Features* features);

      inline void setCell(SIAUtils::Position pos) { m_cell = pos; }
      inline void setCell(int x, int y) { m_cell.x = x; m_cell.y = y; }

      inline const SIAUtils::Position& cell() const {
        return m_cell;
      }

      inline const SIAUtils::Position& pos() const {
        return m_real;
      }

      inline bool physical() const { return m_features->Bool(m_physical); }
      inline bool generator() const { return m_features->Bool(m_generator); }
      inline bool energy() const { return m_features->Bool(m_energy); }

      EntityType type() const;
      inline Features& features() { return *m_features; }

    protected:
      SIAUtils::Position m_cell;
      SIAUtils::Position m_real;

      Features::Cache m_physical;
      Features::Cache m_generator;
      Features::Cache m_energy;
      Features::Cache m_entityType;

      Features* m_features;
    };
  };
};

#endif // _COMPONENTS_DATA_ENTITY_H__
