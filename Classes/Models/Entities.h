//
//File: Entities.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 20:37 30/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITIES_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITIES_H__

#include "Utils/NonCopyable.h"
#include "Entity.h"
#include <vector>
#include <functional>

namespace Models
{
  class Entities : SIA::NonCopyable {
  public:
    class Array;
    class Grid;
    class Graph;
    friend class Array;
    friend class Grid;
    friend class Graph;
  public:
    Entities(size_t width, size_t heigth, size_t maxCount);

    bool add(EntityPtr pEntity);
    void update(EntityPtr pEntity);
    bool erase(EntityPtr pEntity);

    void update();

    /*unsafe*/
    const Array& getArray() const { return *(m_pArray.get()); }
    const Grid& getGrid() const { return *(m_pGrid.get()); }
    const Graph& getGraph() const { return *(m_pGraph.get()); }

  private:
    std::unique_ptr<Array> m_pArray;
    std::unique_ptr<Grid> m_pGrid;
    std::unique_ptr<Graph> m_pGraph;


    //std::vector<EntityPtr> m_pEntities;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITIES_H__
