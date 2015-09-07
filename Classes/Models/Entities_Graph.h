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
    bool connect(EntityPtr pEntity, float range);
    void disconnect(EntityPtr pEntity);
    void remember(EntityPtr pEntity);

    void reconnectAll(const std::list<EntityPtr>& entities, int depth);
    int findMinDepth(const std::list<EntityPtr>& entities) const;
    void setDepth(EntityPtr pEntity, int depth);
  private:
    static const int sUndefinedDepth = 32000;

    struct Generator {
      //std::list<EntityPtr> pEquivalents;
      float power;
      float storage;
      double range;
    };
    typedef std::shared_ptr<Generator> GeneratorPtr;

    struct PointerJoin {
      int depth;
      int maxConnected;
      double range;
    };
    typedef std::shared_ptr<PointerJoin> PointerJoinPtr;

    struct PointerLeaf {
      int depth;
      float power;
      double range;
    };
    typedef std::shared_ptr<PointerLeaf> PointerLeafPtr;

    std::map<EntityPtr, PointerLeafPtr> m_Leafs;

    std::map<EntityPtr, GeneratorPtr> m_Generators;
    std::map<EntityPtr, PointerJoinPtr> m_Joins;

    const Entities& m_parent;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__
