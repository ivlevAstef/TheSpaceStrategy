#include "Entities_Graph.h"

using namespace Models;


Entities::Graph::Graph(const Entities& parent) : m_parent(parent) {
}

bool Entities::Graph::add(EntityPtr pEntity) {
  return true;
}

void Entities::Graph::update(EntityPtr pEntity) {

}

bool Entities::Graph::erase(EntityPtr pEntity) {
  return true;
}

void Entities::Graph::update() {

}

std::vector<EntityPtr> Entities::Graph::findAround(EntityPtr pEntity, float radius) {
  return std::vector<EntityPtr>();
}

void Entities::Graph::connect(EntityPtr pEntity) {

}

void Entities::Graph::connect(EntityPtr pEntity, EntityPtr pEntityTo) {

}

void Entities::Graph::disconnect(EntityPtr pEntity) {

}

void Entities::Graph::reconnect(EntityPtr pEntity) {

}

void Entities::Graph::remember(EntityPtr pEntity) {

}

void Entities::Graph::addGeneratorJoin(std::list<GeneratorPtr> pLinks) {

}

void Entities::Graph::removeGeneratorJoin(GeneratorJoinPtr pGeneratorJoin) {

}