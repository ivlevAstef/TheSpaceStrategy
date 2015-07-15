//
//File: PropertyContainer.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 13:26 22/6/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_PROPERTY_CONTAINTER_H__
#define _SIA_THE_SPACE_STRATEGY_PROPERTY_CONTAINTER_H__

#include <map>
#include <memory>
#include "IProperty.h"

namespace Properties
{
  class PropertyContainer {
  public:
    template<typename PropertyType>
    std::shared_ptr<PropertyType> as() const {
      IPropertyPtr property = as(PropertyType::sPropertyName());
      return std::static_pointer_cast<PropertyType>(property);
    }

    template<typename PropertyType>
    bool is() const {
      return is(PropertyType::sPropertyName());
    }

    bool is(const char* name) const;
    IPropertyPtr as(const char* name) const;

    PropertyContainer& operator+=(IPropertyPtr property);
    PropertyContainer& operator-=(IPropertyPtr property);

  private:
    std::map<std::string, IPropertyPtr> m_properties;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_PROPERTY_CONTAINTER_H__
