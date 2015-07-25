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
#include "Common/EntityMutex.h"
#include "Grid_Cell.h"

namespace Models
{
  class IGridDraw {
  public:
    virtual void draw(std::function<void(const Grid& grid, double dt)> drawFunc) = 0;
  };

  class Grid : public IGridDraw {
  public:
    Grid(size_t width, size_t height) : m_width(0), m_height(0) {
      setSize(width, height);
    }

    Grid(const Grid&) = delete;

    void draw(std::function<void(const Grid& grid, double dt)> drawFunc) override;

    void update(const EntityArray& entities);

    void setSize(size_t width, size_t height);

    const size_t width() const { return m_width; }
    const size_t height() const { return m_height; }

    const Cell* getCell(int x, int y) const;

  private:
    void cleanCells();

    Cell* getCell(int x, int y);

    void distributeEnergyFrom(Cell::EnergyNode* node);

  private:
    size_t m_width;
    size_t m_height;

    std::vector<Cell> m_Cells;

    Common::EntityMutex m_mutex;
  };

  typedef std::shared_ptr<Grid> GridPtr;
  typedef std::shared_ptr<IGridDraw> IGridDrawPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_GRID_H__
