//
//File: Entities_Graph.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:36 31/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//


#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__

#include "Entities.h"
#include <list>
#include <map>

namespace Models
{
  class Entities::Graph : SIA::NonCopyable {
  public:
    Graph(const Entities&);

    bool add(EntityPtr pEntity);
    void update(EntityPtr pEntity);
    bool erase(EntityPtr pEntity);

    void update();

  private:
    bool connect(EntityPtr pEntity);
    void disconnect(EntityPtr pEntity);

    void reconnectAll(const std::list<EntityPtr>& entities, int depth);
    int findMinDepth(const std::list<EntityPtr>& entities) const;
  private:
    static const int sUndefinedDepth = 32000;

    struct PointerJoin {
      int depth;
      float power;
      double range;

      bool isGenerator;
      bool isJoin;
      bool isLeaf;
    };
    typedef std::shared_ptr<PointerJoin> PointerJoinPtr;

    std::map<EntityPtr, PointerJoinPtr> m_data;

    const Entities& m_parent;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__
