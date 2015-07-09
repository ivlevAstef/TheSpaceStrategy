#include "ComponentContainer.h"
#include "SIALogger.h"

using namespace Components;

IComponentPtr ComponentContainer::as(const char* name) {
  auto findRes = m_components.find(name);

  if (findRes == m_components.end()) {
    SIAWarning("Can't find component with name %s.", name);
    return IComponentPtr(nullptr);
  }

  return findRes->second;
}

bool ComponentContainer::is(const char* name) {
  SIAAssert(name);
  return m_components.find(name) != m_components.end();
}

void ComponentContainer::addComponent(IComponentPtr component) {
  SIACheckRet(component.get() == nullptr);

  SIAInfo("Add component: %s.", component->componentName());
  m_components[component->componentName()] = component;
}

void ComponentContainer::eraseComponent(IComponentPtr component) {
  SIACheckRet(component.get() == nullptr);

  SIAInfo("Erase component: %s.", component->componentName());

  auto find = m_components.find(component->componentName());

  SIACheckRet(find == m_components.end());

  m_components.erase(find);
}