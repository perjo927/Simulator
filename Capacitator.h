// CAPACITATOR.H //
// perjo927 & linja919

// Kondensatorer har en viss kapacitans och en nuvarande laddning

#ifndef __CAPACITATOR_H__
#define __CAPACITATOR_H__

#include "Component.h"

class Capacitator : public Component
{
public:
  Capacitator(std::string, float, Connection&, Connection&);
  
  void moveCharge(float time_units);
  float getCurr() const;

private:
  float const m_capacity;
  float m_charge;
};

#endif


