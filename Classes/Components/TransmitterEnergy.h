//
//File:  TransmitterEnergy.h
//Description: Component respondent for Broadcast Energy.
//Author: Ivlev Alexander. Stef
//Created: 25/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_TRANSMITTER_ENERGY_H__
#define _SIA_THE_SPACE_STRATEGY_TRANSMITTER_ENERGY_H__

#include "IComponent.h"

namespace Components
{
  class TransmitterEnergy: public IComponent {
  public:
    DEFINE_COMPONENT(TransmitterEnergy);

    static IComponentPtr create(double transmissionRange) {
      return IComponentPtr(new TransmitterEnergy(transmissionRange));
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
