// RESISTOR.H //
// perjo927 & linja919

// Resistorer har ett visst motstånd

#ifndef __RESISTOR_H__
#define __RESISTOR_H__

#include "Component.h"

class Resistor : public Component
{
public:
  Resistor(std::string, float, Connection&, Connection&);
  
  void moveCharge(float time_units);
  float getCurr() const;
  
private:
  float const m_resistance;
};

#endif

