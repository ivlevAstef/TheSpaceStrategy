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
      static const size_t sDefaultWidth = 32;
      static const size_t sDefaultHeight = 32;

      static const size_t sCellSize = 100;
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

      static bool convert(const int x,const int y, float& toX, float& toY);


      inline size_t width() const { return m_width; }
      inline size_t height() const { return m_height; }
      inline size_t cellSize() const { return sCellSize; }

    private:
      bool addPhysicEntity(Entity* pEntity);
      void removePhysicEntity(Entity* pEntity);
      bool checkEntityPosition(const SIAUtils::Position& position);
      void clearCells();
      void calculateRealPosFor(Entity* pEntity);

      void updateEnergy();


    private:
      size_t m_width;
      size_t m_height;

      std::vector<Entity*> m_pEntities;

      struct Cell {
        static const size_t width = 100;
        static const size_t height = 100;
        static const size_t maxPhysicalEntity = 4;

        std::vector<Entity*> pPhysicalEntities;
        Entity* pPylon;

        Cell() : pPylon(nullptr) {
          pPhysicalEntities.resize(maxPhysicalEntity, nullptr);
        }

        bool addEntity(Entity* pEntity);
        void removeEntity(Entity* pEntity);
      };


      std::vector<Cell> m_cells;
    };
  };
};

#endif // _COMPONENTS_DATA_AREA_H__
