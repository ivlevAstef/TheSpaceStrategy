//
//File: Entities_Grid.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:36 31/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//


#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITIES_GRID_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITIES_GRID_H__

#include "Entities.h"
#include <vector>
#include <list>

namespace Models
{
  class Entities::Grid : SIA::NonCopyable {
  public:
    Grid(const Entities&, size_t width, size_t height);

    bool add(EntityPtr pEntity);
    void update(EntityPtr pEntity);
    bool erase(EntityPtr pEntity);

    void update();

    std::list<EntityPtr> get(const Common::CellPos& cell) const;
    std::list<EntityPtr> getUNSAFE(const Common::CellPos& cell) const;
    std::list<EntityPtr> collision(const EntityPtr& pEntity) const;
    std::list<EntityPtr> getAround(const Common::EntityPos& pos, double range) const;

    inline size_t width() const {
      return m_width;
    }
    inline size_t height() const {
      return m_height;
    }

  private:
    void unsafeAdd(EntityPtr pEntity);
    inline int getIndex(const Common::CellPos& cell) const {
      return m_width * cell.y + cell.x;
    }

    std::vector<Common::CellPos> heldCell(const Common::EntityPos& pos, const Common::EntitySize& size) const;

  private:
    const Entities& m_parent;

    size_t m_width;
    size_t m_height;

    typedef std::vector<std::list<EntityPtr>> GridType;

    GridType m_grid;

  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITIES_GRID_H__
