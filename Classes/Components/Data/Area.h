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
      DEFINE_COMPONENT(Area);

      static Area* create();

      void addEntity(Entity* pEntity);
      void removeEntity(Entity* pEntity);

      void update();

      static bool convert(const int x,const int y, float& toX, float& toY);

    private:
      std::vector<Entity*> m_pEntities;
    };
  };
};

#endif // _COMPONENTS_DATA_AREA_H__
