//
//File: EntityGrid.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 19:47 3/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_GRID_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_GRID_H__

#include "Entity.h"
#include <vector>
#include <list>

namespace Models
{
  class EntityGrid {
  public:
    EntityGrid(size_t width, size_t height);

    bool add(EntityPtr pEntity);
    bool erase(EntityPtr pEntity);
    bool update(EntityPtr pEntity);

    inline size_t width() const { return m_width; }
    inline size_t height() const { return m_height; }

  private:
    void unsafeAdd(EntityPtr pEntity);
    inline int getIndex(const Common::CellPos& cell) const { return m_width * cell.y + cell.x; }

  private:
    size_t m_width;
    size_t m_height;

    typedef std::vector<std::list<EntityPtr>> GridType;

    GridType m_grid;

  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_GRID_H__
