#include "Object.h"
#include "logger/SIAUtils_Logger.h"

using namespace Objects;

Components::Component* Object::getComponent(const char* name) {
  auto findRes = m_components.find(name);

  SIA_CHECK_ZERO(findRes == m_components.end(), WRN);

  return findRes->second;
}

void Object::addComponent(Components::Component* component) {
  SIA_CHECK_RET(component == nullptr, WRN);

  SIA_LOG_INFO("Add component: %s", component->componentName());
  m_components[component->componentName()] = component;
}

void Object::eraseComponent(Components::Component* component) {
  SIA_CHECK_RET(component == nullptr, WRN);

  SIA_LOG_INFO("Erase component: %s", component->componentName());

  auto find = m_components.find(component->componentName());
  
  SIA_CHECK_RET(find == m_components.end(), WRN);
  
  m_components.erase(find);
}