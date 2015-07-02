/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_COMPONENTS_CONTAINTER_H__
#define _SIA_THE_SPACE_STRATEGY_COMPONENTS_CONTAINTER_H__

#include <map>
#include <memory>
#include "IComponent.h"

namespace Components
{
	class ComponentContainer {
	public:
		template<typename ComponentType>
		std::shared_ptr<ComponentType> as() {
			IComponentPtr component = as(ComponentType::sComponentName());
      return std::static_pointer_cast<ComponentType>(component);
		}

    template<typename ComponentType>
    bool is() {
      return is(ComponentType::sComponentName());
    }

    bool is(const char* name);
		IComponentPtr as(const char* name);

	protected:
		void addComponent(IComponentPtr component);
		void eraseComponent(IComponentPtr component);

	private:
		std::map<std::string, IComponentPtr> m_components;
	};

};

#endif // _SIA_THE_SPACE_STRATEGY_COMPONENTS_CONTAINTER_H__
