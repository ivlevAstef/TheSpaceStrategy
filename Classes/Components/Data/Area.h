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
    class Area : public Component {
    public:
      static const size_t defaultWidth = 64;
      static const size_t defaultHeight = 64;

      static const size_t cellSize = 100;
    public:
      DEFINE_COMPONENT(Area);

      Area() : m_width(0), m_height(0) {
        setSize(defaultWidth, defaultHeight);
      }

      static Area* create();

      bool addEntity(Entity* pEntity);
      void removeEntity(Entity* pEntity);

      void update();

      void setSize(size_t width, size_t height);

      static bool convert(const int x,const int y, float& toX, float& toY);


    private:
      bool addPhysicEntity(Entity* pEntity);
      bool checkEntityPosition(const SIAUtils::Position& position);
      void clearCells();
      void recalculateCells();

    private:
      size_t m_width;
      size_t m_height;

      std::vector<Entity*> m_pEntities;

      struct Cell {
        static const size_t width = 100;
        static const size_t height = 100;
        static const size_t maxPhysicalEntity = 4;

        std::vector<Entity*> pPhysicalEntities;

        bool addEntity(Entity* pEntity);
      };


      std::vector<Cell> m_cells;
    };
  };
};

#endif // _COMPONENTS_DATA_AREA_H__
