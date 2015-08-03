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
#include <unordered_map>

namespace Models
{
  class EntityGrid {
  public:
    EntityGrid(size_t width, size_t height);

    bool add(EntityPtr pEntity);
    bool remove(EntityPtr pEntity);



    void update();

  private:
    void unsafeAdd(EntityPtr pEntity);

  private:
    size_t m_width;
    size_t m_height;

    struct CellHash {
      size_t width;

      std::size_t operator()(const Common::CellPos& pos) const {
        return width*pos.y + pos.x;
      }
    };

    typedef std::unordered_map<Common::CellPos, EntityPtr, CellHash> GridType;

    CellHash m_cellHash;
    GridType m_grid;

  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_GRID_H__
