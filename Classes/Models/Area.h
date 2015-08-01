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
#include "EntityArray.h"

#include <functional>
#include <vector>

namespace Models
{
  class Area {
  public:
    Area(size_t width, size_t height) {
      m_pGrid = GridPtr(new Grid(width, height));
    }

    bool addEntity(EntityPtr pEntity);
    bool eraseEntity(EntityPtr pEntity);

    void update();

    inline IGridDrawPtr grid() { return std::static_pointer_cast<IGridDraw>(m_pGrid); }

  private:
    bool setupEntity(EntityPtr pEntity);

  private:
    GridPtr m_pGrid;

    EntityArray m_entities;
  };

  typedef std::shared_ptr<Area> AreaPtr;
  typedef std::shared_ptr<const Area> ConstAreaPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_AREA_H__
