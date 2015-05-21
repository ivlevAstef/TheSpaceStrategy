/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_DATA_MODIFICATOR_ENERGY_GENERATOR_H__
#define _COMPONENTS_DATA_MODIFICATOR_ENERGY_GENERATOR_H__


#include "../../Component.h"
#include "../Features.h"

namespace Components
{
  namespace Data
  {
    namespace Modificator
    {
      class EnergyGenerator: public ComponentRef {
      private:
        friend class Area;
      public:
        DEFINE_COMPONENT(EnergyGenerator);

        static EnergyGenerator* create(Features* features, double generatedEnergy);

        EnergyGenerator(Features* features, double generatedEnergy);
        ~EnergyGenerator();

        void setGeneratedEnergy(double generatedEnergy);


        static bool isGenerator(const Features& features);
        static double getGeneratedEnergy(const Features& features);

      private:
        Features* m_features;
      };
    };
  };
};

#endif // _COMPONENTS_DATA_MODIFICATOR_ENERGY_GENERATOR_H__
