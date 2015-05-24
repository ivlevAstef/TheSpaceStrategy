/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_DATA_AREA_H__
#define _COMPONENTS_DATA_AREA_H__

#include "../Component.h"
#include "Entity.h"

#include <vector>

namespace Components
{
  namespace Data
  {
    class Area: public ComponentRef {
    public:
      static const size_t sDefaultWidth = 32;
      static const size_t sDefaultHeight = 32;

    public:
      DEFINE_COMPONENT(Area);

      Area() : m_width(0), m_height(0) {
        setSize(sDefaultWidth, sDefaultHeight);
      }

      static Area* create();

      bool addEntity(Entity* pEntity);
      void removeEntity(Entity* pEntity);

      void update();

      void setSize(size_t width, size_t height);

      inline size_t width() const { return m_width; }
      inline size_t height() const { return m_height; }

    private:
      bool addPhysicEntity(Entity* pEntity);
      void removePhysicEntity(Entity* pEntity);
      bool checkEntityPosition(const SIAUtils::Point2D<size_t>& position);
      void clearCells();
      void calculateRealPosFor(Entity* pEntity);

      void updateEnergy();


    private:
      size_t m_width;
      size_t m_height;

      std::vector<Entity*> m_pEntities;

      struct Cell {
        std::vector<Entity*> pPhysicalEntities;
        Entity* pPylon;

        Cell();

        bool addEntity(Entity* pEntity);
        void removeEntity(Entity* pEntity);
      };


      std::vector<Cell> m_cells;
    };
  };
};

#endif // _COMPONENTS_DATA_AREA_H__
