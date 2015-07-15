//
//File: EnergyGenerator.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 9:03 21/5/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENERGY_GENERATOR_H__
#define _SIA_THE_SPACE_STRATEGY_ENERGY_GENERATOR_H__

#include "IProperty.h"

namespace Properties
{
  class EnergyGenerator: public IProperty {
  public:
    DEFINE_PROPERTY(EnergyGenerator);

    static IPropertyPtr create(double generatedEnergyInSec) {
      return IPropertyPtr(new EnergyGenerator(generatedEnergyInSec));
    }

    double generatedEnergy() const { return m_generatedEnergyInSec; }

  private:
    EnergyGenerator(double generatedEnergyInSec) {
      m_generatedEnergyInSec = generatedEnergyInSec;
    }

  private:
    double m_generatedEnergyInSec;
  };

  typedef std::shared_ptr<EnergyGenerator> EnergyGeneratorPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_ENERGY_GENERATOR_H__
