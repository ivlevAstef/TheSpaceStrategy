//
//File:  EnergyGenerator.h
//Description: Component respondent for generated energy.
//Author: Ivlev Alexander. Stef
//Created: 25/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENERGY_GENERATOR_H__
#define _SIA_THE_SPACE_STRATEGY_ENERGY_GENERATOR_H__

#include "IComponent.h"

namespace Components
{
  class EnergyGenerator: public IComponent {
  public:
		DEFINE_COMPONENT(EnergyGenerator);

    static IComponentPtr create(double generatedEnergyInSec) {
      return IComponentPtr(new EnergyGenerator(generatedEnergyInSec));
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
