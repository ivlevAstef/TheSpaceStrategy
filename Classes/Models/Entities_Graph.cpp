#include "Entities_Graph.h"
#include "Entities_Grid.h"

#include "Properties/EnergyGenerator.h"
#include "Properties/TransmitterEnergy.h"
#include "SIALogger.h"

SIASetModuleName(Models);

using namespace Models;


Entities::Graph::Graph(const Entities& parent) : m_parent(parent) {
}

bool Entities::Graph::add(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (pEntity->prop().is<Properties::TransmitterEnergy>()) {
    double range = pEntity->prop().as<Properties::TransmitterEnergy>()->transmissionRange();

    if (pEntity->prop().is<Properties::EnergyGenerator>()) {
      if (m_Generators.count(pEntity) > 0) {
        SIAError("Already add entity to graph generators.");
        return false;
      }

      auto generator = GeneratorPtr(new Generator());
      generator->power = pEntity->prop().as<Properties::EnergyGenerator>()->generatedEnergy();
      generator->storage = 0;
      generator->range = range;

      m_Generators[pEntity] = generator;

      return connect(pEntity, generator->range);
    }


    if (m_Joins.count(pEntity) > 0) {
      SIAError("Already add entity to joins.");
      return false;
    }

    auto join = PointerJoinPtr(new PointerJoin());
    join->depth = -1;
    join->maxConnected = 1000;
    join->range = range;

    m_Joins[pEntity] = join;

    return connect(pEntity, join->range);
  }

  if (m_Leafs.count(pEntity) > 0) {
    SIAError("Already add entity to unused.");
    return false;
  }

  auto leaf = PointerLeafPtr(new PointerLeaf());
  leaf->depth = sUndefinedDepth;
  leaf->power = 0;
  leaf->range = Properties::TransmitterEnergy::sMaxTransmissionRange;

  m_Leafs[pEntity] = leaf;

  return connect(pEntity, leaf->range);
}

void Entities::Graph::update(EntityPtr pEntity) {

}

bool Entities::Graph::erase(EntityPtr pEntity) {
  return true;
}

void Entities::Graph::update() {

}


bool Entities::Graph::connect(EntityPtr pEntity, float range) {
  auto entities = m_parent.getGrid().getAround(pEntity->pos(), range);

  bool isGenerator = m_Generators.count(pEntity) > 0;
  bool isJoin = m_Joins.count(pEntity) > 0;
  bool isLeaf = m_Leafs.count(pEntity) > 0;

  int entityDepth = 0;

  if (isLeaf || isJoin) {
    int minDepth = findMinDepth(entities);
    if (minDepth != sUndefinedDepth) {
      entityDepth = minDepth + 1;
      setDepth(pEntity, entityDepth);
    } else {
      entityDepth = sUndefinedDepth;
    }
  }

  if (isGenerator || isJoin) {
    reconnectAll(entities, entityDepth + 1);
  }

  return true;
}

void Entities::Graph::disconnect(EntityPtr pEntity) {

}


void Entities::Graph::remember(EntityPtr pEntity) {

}

int Entities::Graph::findMinDepth(const std::list<EntityPtr>& entities) const {
  int minDepth = sUndefinedDepth;

  for (auto pEnt : entities) {
    if (m_Generators.count(pEnt) > 0) {
      return 0;
    }

    if (m_Joins.count(pEnt) > 0) {
      int curDepth = m_Joins.at(pEnt)->depth;
      minDepth = (minDepth < curDepth) ? minDepth : curDepth;
    }
  }

  return minDepth;
}

void Entities::Graph::setDepth(EntityPtr pEntity, int depth) {
  if (m_Joins.count(pEntity) > 0) {
    m_Joins.at(pEntity)->depth = depth;
  } else if (m_Leafs.count(pEntity) > 0) {
    m_Leafs.at(pEntity)->depth = depth;
  }
}

void Entities::Graph::reconnectAll(const std::list<EntityPtr>& entities, int depth) {
  for (auto pEnt : entities) {
    if (m_Joins.count(pEnt) > 0) {
      auto pJoin = m_Joins.at(pEnt);
      if (pJoin->depth > depth) {
        connect(pEnt, pJoin->range);
      }
    } else if (m_Leafs.count(pEnt) > 0) {
      auto pLeaf = m_Leafs.at(pEnt);
      if (pLeaf->depth > depth) {
        connect(pEnt, pLeaf->range);
      }
    }
  }
}