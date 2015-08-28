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

#include "Entity.h"
#include "EntityArray.h"
#include "EntityGrid.h"
#include "EntityEnergyGraph.h"

#include <functional>
#include <vector>

namespace Models
{
  class Area {
  public:
    Area(size_t width, size_t height) : m_grid(width, height) {
      m_energyGraph.setGrid(&m_grid);
    }

    bool addEntity(EntityPtr pEntity);
    bool eraseEntity(EntityPtr pEntity);

    void update();

    inline size_t width() const { return m_grid.width(); }
    inline size_t height() const { return m_grid.height(); }

  private:
    bool setupEntity(EntityPtr pEntity);

  private:

    EntityArray m_entities;
    EntityGrid m_grid;
    EntityEnergyGraph m_energyGraph;
  };

  typedef std::shared_ptr<Area> AreaPtr;
  typedef std::shared_ptr<const Area> ConstAreaPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_AREA_H__
