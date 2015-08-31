#include "Entities.h"
#include "Entities_Array.h"
#include "Entities_Grid.h"
#include "Entities_Graph.h"

#include "Utils/SIALogger.h"

SIASetModuleName(Models);

using namespace Models;

Entities::Entities(size_t width, size_t height, size_t maxCount) {
  m_pArray = std::unique_ptr<Array>(new Array(*this, maxCount));
  m_pGrid = std::unique_ptr<Grid>(new Grid(*this, width, height));
  m_pGraph = std::unique_ptr<Graph>(new Graph(*this));
}

bool Entities::add(EntityPtr pEntity) {
  if (!m_pArray->add(pEntity)) {
    SIAError("Can't add entity into array. already exist?");
    return false;
  }
  if (!m_pGrid->add(pEntity)) {
    SIAError("Can't add entity into grid. already exist?");
    m_pArray->erase(pEntity);
    return false;
  }

  if (!m_pGraph->add(pEntity)) {
    SIAError("Can't add entity into graph. already exist?");
    m_pGrid->erase(pEntity);
    m_pArray->erase(pEntity);
    return false;
  }

  return true;
}

void Entities::update(EntityPtr pEntity) {
  m_pArray->update(pEntity);
  m_pGrid->update(pEntity);
  m_pGraph->update(pEntity);
}

bool Entities::erase(EntityPtr pEntity) {
  bool success = m_pArray->erase(pEntity);
  success |= m_pGrid->erase(pEntity);
  success |= m_pGraph->erase(pEntity);

  return success;
}

void Entities::update() {
  m_pArray->update();
  m_pGrid->update();
  m_pGraph->update();
}