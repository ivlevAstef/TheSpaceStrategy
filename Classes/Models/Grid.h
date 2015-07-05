//
//File: Grid.h
//Description: Class with for contains grid data and calculate.
//Author: Ivlev Alexander. Stef
//Created: 28/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_GRID_H__
#define _SIA_THE_SPACE_STRATEGY_GRID_H__

#include "EntityArray.h"
#include "Grid_Cell.h"

namespace Models
{
  class Grid {
  public:
    Grid(size_t width, size_t height) : m_width(0), m_height(0) {
      setSize(width, height);
    }

    void update(const EntityArray& entities);

    void setSize(size_t width, size_t height);

    const size_t width() const { return m_width; }
    const size_t height() const { return m_height; }

    void foreach(int x, int y, 
                 int width, int height, 
                 std::function<void(size_t x, size_t y, const Cell&)> cell) const;

  private:
    void cleanCells();

    Cell* getCell(int x, int y);

  private:
    size_t m_width;
    size_t m_height;

    std::vector<Cell> m_Cells;
  };

  typedef std::shared_ptr<Grid> GridPtr;
  typedef std::shared_ptr<const Grid> ConstGridPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_GRID_H__
