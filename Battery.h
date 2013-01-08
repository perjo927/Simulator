// BATTERY.H (ingen CC)//
// perjo927 & linja919

#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "Component.h"

/* Ser till att kopplingspunkten på plus-sidan får
   samma laddning som batteriet och kopplingen på
   minussidan får laddningen noll. 
   Batterier har en outtömlig laddning) */

class Battery : public Component
{
private:
  float const m_charge; // outtömlig laddning
  
public:
  Battery(std::string name, float charge,
          Connection& ca, Connection& cb) :
    Component(name, ca, cb), m_charge(charge) { }


  void moveCharge(float time_units) // ************
  {
    m_connection_a->setCharge(m_charge); // plus
    m_connection_b->setCharge(0); // minus
  }
  //Ett batteri låtsas vi alltid har strömmen noll
  float getCurr() const { return 0.0; }      
};

#endif

