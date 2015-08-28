#include "EntityEnergyGraph.h"

using namespace Models;


void EntityEnergyGraph::setGrid(EntityGrid* pEntityGrid) {
  m_pEntityGrid = pEntityGrid;
}

bool EntityEnergyGraph::add(EntityPtr pEntity) {

}

bool EntityEnergyGraph::update(EntityPtr pEntity) {

}

bool EntityEnergyGraph::erase(EntityPtr pEntity) {

}

void EntityEnergyGraph::update() {

}

std::vector<EntityPtr> EntityEnergyGraph::findAround(EntityPtr pEntity, float radius) {

}

void EntityEnergyGraph::connect(EntityPtr pEntity) {

}

void EntityEnergyGraph::connect(EntityPtr pEntity, EntityPtr pEntityTo) {

}

void EntityEnergyGraph::disconnect(EntityPtr pEntity) {

}

void EntityEnergyGraph::reconnect(EntityPtr pEntity) {

}

void EntityEnergyGraph::remember(EntityPtr pEntity) {

}

void EntityEnergyGraph::addGeneratorJoin(std::list<GeneratorPtr> pLinks) {

}

void EntityEnergyGraph::removeGeneratorJoin(GeneratorJoinPtr pGeneratorJoin) {

}