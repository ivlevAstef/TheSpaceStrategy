//
//File: EntityEnergyGraph.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 17:51 16/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__
#define _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__

#include "EntityGrid.h"
#include <vector>
#include <list>

namespace Models
{
  class EntityEnergyGraph {
  public:
    void setGrid(EntityGrid* pEntityGrid);

    bool add(EntityPtr pEntity);
    bool update(EntityPtr pEntity);
    bool erase(EntityPtr pEntity);

    void update();

  private:
    std::vector<EntityPtr> findAround(EntityPtr pEntity, float radius);

    void connect(EntityPtr pEntity);
    void connect(EntityPtr pEntity, EntityPtr pEntityTo);
    void disconnect(EntityPtr pEntity);
    void reconnect(EntityPtr pEntity);
    void remember(EntityPtr pEntity);

  private:
    struct Generator {
      EntityPtr pEntity;
      std::list<EntityPtr> pEquivalents;
      float power;
      float storage;
    };
    typedef std::shared_ptr<Generator> GeneratorPtr;

    struct GeneratorJoin {
      std::list<GeneratorPtr> pLinks;
      int retainCount;
    };
    typedef std::shared_ptr<GeneratorJoin> GeneratorJoinPtr;

    struct PointerJoin {
      EntityPtr pEntity;
      GeneratorJoinPtr pGenerator;
      int depth;
      int maxConnected;
      float power;
    };
    typedef std::shared_ptr<PointerJoin> PointerJoinPtr;

    std::list<EntityPtr> m_pUnused;

    std::map<EntityPtr, GeneratorPtr> m_Generators;
    std::map<EntityPtr, PointerJoinPtr> m_Joins;

    std::list<GeneratorJoinPtr> m_pGeneratorJoins;

    EntityGrid* m_pEntityGrid;

  private:
    void addGeneratorJoin(std::list<GeneratorPtr> pLinks);
    void removeGeneratorJoin(GeneratorJoinPtr pGeneratorJoin);
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_ENTITY_ENERGY_GRAPH_H__
