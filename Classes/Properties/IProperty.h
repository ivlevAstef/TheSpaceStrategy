//
//File: IProperty.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 9:23 28/4/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_IPROPERTY_H__
#define _SIA_THE_SPACE_STRATEGY_IPROPERTY_H__

#include <memory>

namespace Properties
{
  class IProperty {
  public:
    virtual const char* propertyName() const = 0;
  };

  typedef std::shared_ptr<IProperty> IPropertyPtr;

#define DEFINE_PROPERTY(CLASS) \
  static const char* sPropertyName() { return #CLASS; } \
  virtual const char* propertyName() const override { return #CLASS; }

};

#endif // _SIA_THE_SPACE_STRATEGY_IPROPERTY_H__
