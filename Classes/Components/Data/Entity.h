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
      ~Entity();

      static Entity* create(Features* features);

      void setCellPos(SIAUtils::Point2D<size_t> pos);
      void setPos(SIAUtils::Point2D<float> pos);

      inline void setCellPos(size_t x, size_t y) { setCellPos({x, y}); }
      inline void setPos(float x, float y) { setPos({x, y}); }

      inline const SIAUtils::Point2D<size_t>& cell() const {
        return m_cell;
      }

      inline const SIAUtils::Point2D<float>& pos() const {
        return m_pos;
      }

      inline bool physical() const { return (*m_features)[m_physical]; }
      inline bool energy() const { return (*m_features)[m_energy]; }

      EntityType type() const;
      inline Features& features() { return *m_features; }

    protected:
      SIAUtils::Point2D<size_t> m_cell;
      SIAUtils::Point2D<float> m_pos;

      Features::Cache m_physical;
      Features::Cache m_energy;
      Features::Cache m_entityType;

      Features* m_features;
    };
  };
};

#endif // _COMPONENTS_DATA_ENTITY_H__
