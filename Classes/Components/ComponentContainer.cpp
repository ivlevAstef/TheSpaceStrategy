#include "ComponentContainer.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components;

IComponentPtr ComponentContainer::as(const char* name) {
	auto findRes = m_components.find(name);

	if (findRes == m_components.end()) {
		SIA_LOG_WRN("Can't find component with name %s.", name);
		return IComponentPtr(nullptr);
	}

	return findRes->second;
}

bool ComponentContainer::is(const char* name) {
  return m_components.find(name) != m_components.end();
}

void ComponentContainer::addComponent(IComponentPtr component) {
	SIA_CHECK_RET(component == nullptr, WRN);

	SIA_LOG_INFO("Add component: %s", component->componentName());
	m_components[component->componentName()] = component;
}

void ComponentContainer::eraseComponent(IComponentPtr component) {
	SIA_CHECK_RET(component == nullptr, WRN);

	SIA_LOG_INFO("Erase component: %s", component->componentName());

	auto find = m_components.find(component->componentName());

	SIA_CHECK_RET(find == m_components.end(), WRN);

	m_components.erase(find);
}