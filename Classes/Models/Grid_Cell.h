//
//File: GridCell.h
//Description: Grid Cell.
//Author: Ivlev Alexander. Stef
//Created: 05/07/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_GRID_CELL_H__
#define _SIA_THE_SPACE_STRATEGY_GRID_CELL_H__

namespace Models
{
  class Grid;
  class Cell {
    friend class Grid;
  public:

    inline bool isEnergy() const { return m_isEnergy; }
    inline bool isGenerator() const { return m_isGenerator; }
    inline bool isTransmitter() const { return m_isTransmitter; }

  private:
    void clean() {
      m_isEnergy = false;
      m_isTransmitter = false;
      m_isGenerator = false;
    }

  private:
    bool m_isEnergy;
    bool m_isGenerator;
    bool m_isTransmitter;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_GRID_CELL_H__
