//
//File: EnergyState.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 18:56 9/9/2015
//Copyright (c) SIA 2015. All Right Reserved.
//


#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_ENERGY_STATE_H__
#define _SIA_THE_SPACE_STRATEGY_ENERGY_STATE_H__

#include "IProperty.h"

namespace Properties
{
  class EnergyState: public IProperty {
  public:
    DEFINE_PROPERTY(EnergyState);

    static IPropertyPtr create() {
      return IPropertyPtr(new EnergyState());
    }

    bool connected() const {
      return m_connected;
    }

    double range() const {
      return m_range;
    }

    void setRange(double range) {
      m_range = range;
    }

    void connect() {
      m_connected = true;
    }

    void disconnect() {
      m_connected = false;
    }

  private:
    EnergyState() = default;

  private:
    bool m_connected = false;
    double m_range = 0.0;
  };

  typedef std::shared_ptr<EnergyState> EnergyStatePtr;
};

#endif // _SIA_THE_SPACE_STRATEGY_ENERGY_STATE_H__
