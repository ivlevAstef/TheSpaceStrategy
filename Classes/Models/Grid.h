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

#include "Entity.h"

#include <functional>
#include <vector>

namespace Models
{
  class Grid {
  public:
    Grid(size_t width, size_t height) : m_width(0), m_height(0) {
      setSize(width, height);
    }

    void update(const std::vector<EntityPtr>& pEntities);

    void setSize(size_t width, size_t height);

  private:
    size_t m_width;
    size_t m_height;
  };

  typedef std::shared_ptr<Grid> GridPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_GRID_H__
