//
//File: PropertyContainer.cpp
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 13:29 22/6/2015
//Copyright (c) SIA 2015. All Right Reserved.
//
#include "PropertyContainer.h"
#include "SIALogger.h"

using namespace Properties;

IPropertyPtr PropertyContainer::as(const char* name) const {
  auto findRes = m_properties.find(name);

  if (findRes == m_properties.end()) {
    SIAWarning("Can't find property with name %s.", name);
    return IPropertyPtr(nullptr);
  }

  return findRes->second;
}

bool PropertyContainer::is(const char* name) const {
  SIAAssert(name);
  return m_properties.find(name) != m_properties.end();
}

PropertyContainer& PropertyContainer::operator+=(IPropertyPtr property) {
  SIACheckRetValue(property.get() == nullptr, *this);

  SIAInfo("Add property: %s.", property->propertyName());
  m_properties[property->propertyName()] = property;

  return *this;
}

PropertyContainer& PropertyContainer::operator-=(IPropertyPtr property) {
  SIACheckRetValue(property.get() == nullptr, *this);

  SIAInfo("Erase property: %s.", property->propertyName());

  auto find = m_properties.find(property->propertyName());

  SIACheckRetValue(find == m_properties.end(), *this);

  m_properties.erase(find);

  return *this;
}