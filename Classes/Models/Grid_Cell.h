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

    inline bool isEnergy() const { return m_energyNode.isEnergy; }
    inline bool isGenerator() const { return m_energyNode.isGenerator; }
    inline bool isTransmitter() const { return m_energyNode.isTransmitter; }

  private:
    struct EnergyNode {
      std::vector<EnergyNode*> joins;
      bool isTransmitter;
      bool isEnergy;
      bool isGenerator;
    };

    bool isJoined() const { return m_energyNode.isGenerator || m_energyNode.isTransmitter; }

    void addJoinIfNeed(Cell* checkCell) {
      if (checkCell && checkCell->isJoined()) {
        checkCell->m_energyNode.joins.push_back(&m_energyNode);
        m_energyNode.joins.push_back(&checkCell->m_energyNode);
      }
    }

    void clean() {
      m_energyNode.joins.clear();
      m_energyNode.isEnergy = false;
      m_energyNode.isTransmitter = false;
      m_energyNode.isGenerator = false;
    }

  private:
    EnergyNode m_energyNode;
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_GRID_CELL_H__
