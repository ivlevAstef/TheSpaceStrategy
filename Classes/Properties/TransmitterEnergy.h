//
//File: TransmitterEnergy.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 9:27 25/6/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_TRANSMITTER_ENERGY_H__
#define _SIA_THE_SPACE_STRATEGY_TRANSMITTER_ENERGY_H__

#include "IProperty.h"

namespace Properties
{
  class TransmitterEnergy: public IProperty {
  public:
    DEFINE_PROPERTY(TransmitterEnergy);

    static IPropertyPtr create(double transmissionRange) {
      return IPropertyPtr(new TransmitterEnergy(transmissionRange));
    }

    double transmissionRange() const { return m_transmissionRange; }

  private:
    TransmitterEnergy(double transmissionRange) {
      m_transmissionRange = transmissionRange;
    }

  private:
    double m_transmissionRange;
  };

  typedef std::shared_ptr<TransmitterEnergy> TransmitterEnergyPtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_TRANSMITTER_ENERGY_H__
