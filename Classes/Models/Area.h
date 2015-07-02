//
//File: Area.h
//Description: Class with Area data (Store entities and size) 
//Author: Ivlev Alexander. Stef
//Created: 02/05/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_AREA_H__
#define _SIA_THE_SPACE_STRATEGY_AREA_H__

#include "Grid.h"
#include "Entity.h"

#include <functional>
#include <vector>

namespace Models
{
    class Area {
    public:
      Area(size_t width, size_t height) : m_grid(width, height) {
      }

      bool addEntity(EntityPtr pEntity);
      void removeEntity(EntityPtr pEntity);

      void update();

   private:
      void findEntityInCell(Common::CellPos pos, std::function<void (EntityPtr entity)> FindResultCallback);

      bool setupEntity(EntityPtr pEntity);

    private:
      Grid m_grid;

      std::vector<EntityPtr> m_pEntities;
    };

    typedef std::shared_ptr<Area> AreaPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_AREA_H__
