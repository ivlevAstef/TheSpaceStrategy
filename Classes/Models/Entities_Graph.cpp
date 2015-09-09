#include "Entities_Graph.h"
#include "Entities_Grid.h"

#include "Common/ModelMath.h"

#include "Properties/EnergyGenerator.h"
#include "Properties/EnergyState.h"
#include "Properties/TransmitterEnergy.h"
#include "SIALogger.h"

SIASetModuleName(Models);

using namespace Models;


Entities::Graph::Graph(const Entities& parent) : m_parent(parent) {
  m_maxRange = 0;
}

bool Entities::Graph::add(EntityPtr pEntity) {
  SIAAssert(pEntity);

  if (m_data.count(pEntity) > 0) {
    SIAError("Already add entity to graph.");
    return false;
  }

  if (!pEntity->prop().is<Properties::EnergyState>()) {
    SIAInfo("It's not energyState entity.");
    return true;
  }


  auto pointerJoin = PointerJoinPtr(new PointerJoin());
  pointerJoin->isGenerator = false;
  pointerJoin->isJoin = false;
  pointerJoin->isLeaf = false;

  if (pEntity->prop().is<Properties::TransmitterEnergy>()) {
    double range = pEntity->prop().as<Properties::TransmitterEnergy>()->transmissionRange();

    if (pEntity->prop().is<Properties::EnergyGenerator>()) {
      pointerJoin->power = pEntity->prop().as<Properties::EnergyGenerator>()->generatedEnergy();
      pointerJoin->depth = 0;
      pointerJoin->range = range;
      pointerJoin->isGenerator = true;
      pEntity->prop().as<Properties::EnergyState>()->connect();
    } else {
      pointerJoin->power = 0;
      pointerJoin->depth = sUndefinedDepth;
      pointerJoin->range = range;
      pointerJoin->isJoin = true;
    }

    m_maxRange = (range > m_maxRange) ? range : m_maxRange;

    pEntity->prop().as<Properties::EnergyState>()->setRange(range);
  } else {
    pointerJoin->power = 0;
    pointerJoin->depth = sUndefinedDepth;
    pointerJoin->range = 0;
    pointerJoin->isLeaf = true;
  }

  m_data[pEntity] = pointerJoin;

  return connect(pEntity);
}

void Entities::Graph::update(EntityPtr pEntity) {

}

bool Entities::Graph::erase(EntityPtr pEntity) {
  if (0 < m_data.count(pEntity)) {
    auto pointerJoin = m_data.at(pEntity);
    if (pointerJoin->isGenerator || pointerJoin->isJoin) {
      disconnect(pEntity);
    }

    m_data.erase(pEntity);

    return true;
  }

  return false;
}

void Entities::Graph::update() {

}


bool Entities::Graph::connect(EntityPtr pEntity) {
  auto pointerJoin = m_data.at(pEntity);
  auto entities = m_parent.getGrid().getAround(pEntity, m_maxRange);

  if (pointerJoin->isLeaf || pointerJoin->isJoin) {
    int minDepth = findMinDepth(pEntity, entities);
    setDepth(minDepth, pointerJoin, pEntity);
  }

  if (pointerJoin->isGenerator || pointerJoin->isJoin) {
    reconnectAll(entities, pointerJoin->depth);
  }

  return true;
}

void Entities::Graph::disconnect(EntityPtr pEntity) {
  auto pointerJoin = m_data.at(pEntity);
  int safeDepth = pointerJoin->depth;
  pointerJoin->depth = sUndefinedDepth;

  auto entities = m_parent.getGrid().getAround(pEntity, m_maxRange);

  int minDepth = sUndefinedDepth;

  for (auto pEnt : entities) {
    auto pJoinIter = m_data.at(pEnt);

    if (sUndefinedDepth == pJoinIter->depth) {
      continue;
    }

    if (!checkRange(pEntity, pEnt, pJoinIter->range)) {
      continue;
    }

    if (pJoinIter->depth > safeDepth) {
      disconnect(pEnt);
    }

    if (pJoinIter->isJoin || pJoinIter->isGenerator) {
      minDepth = pJoinIter->depth < minDepth ? pJoinIter->depth : minDepth;
    }
  }

  setDepth(minDepth, pointerJoin, pEntity);
}

int Entities::Graph::findMinDepth(EntityPtr pEntity, const std::list<EntityPtr>& entities) const {
  int minDepth = sUndefinedDepth;

  for (auto pEnt : entities) {
    if (0 < m_data.count(pEnt)) {
      auto pJoinIter = m_data.at(pEnt);

      if (!checkRange(pEntity, pEnt, pJoinIter->range)) {
        continue;
      }


      int curDepth = pJoinIter->depth;
      minDepth = (minDepth < curDepth) ? minDepth : curDepth;
    }
  }

  return minDepth;
}

void Entities::Graph::reconnectAll(const std::list<EntityPtr>& entities, int depth) {
  for (auto pEnt : entities) {
    if (0 < m_data.count(pEnt)) {
      auto pointerJoin = m_data.at(pEnt);

      if (depth < pointerJoin->depth) {
        connect(pEnt);
      }
    }
  }
}

void Entities::Graph::setDepth(int minAroundDepth, PointerJoinPtr join, EntityPtr pEntity) {
  SIAAssert(pEntity->prop().is<Properties::EnergyState>());

  if (minAroundDepth != sUndefinedDepth) {
    join->depth = minAroundDepth + 1;

    pEntity->prop().as<Properties::EnergyState>()->connect();
  } else {
    join->depth = sUndefinedDepth;

    pEntity->prop().as<Properties::EnergyState>()->disconnect();
  }
}

bool Entities::Graph::checkRange(EntityPtr pEntity, EntityPtr pEntity2, double range) const {
  return Common::ModelMath::distance2(pEntity->pos(), pEntity2->pos()) < (range * range);
}