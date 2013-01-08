//// RESISTOR.CC ////
// perjo927 & linja919

#include "Resistor.h"

using namespace std;

Resistor::Resistor(string name, float resistance,
                   Connection&  ca, Connection& cb) :
  Component(name, ca, cb), m_resistance(resistance) {}

/* En resistor flyttar laddningspartiklar från sin
   mest positiva kopplingspunkt  till sin minst positiva
   kopplingspunkt. */
  
/*  Antag att resistansen är 2.0 Ohm och vi simulerar i
    steg om  0.1 tidsenheter.
    Om laddningen på sida a är 5.0 och laddnigen på sida b 
    är 9.0 så är spänningen över resistorn 9.0−5.0 = 4.0.
 
    Nu flyttas 4.0/2.0 * 0.1 laddningspartiklar från sida b
    (som ju har högst laddning) till sida a. */
  
void Resistor::moveCharge(float time_units)
{
  Connection* c_max = nullptr; 
  Connection* c_min = nullptr;

  // Hitta mest positiva laddning
  if ( m_connection_a->getCharge() > m_connection_b->getCharge())
  {
    c_max = m_connection_a;
    c_min = m_connection_b;
  }
  else
  {
    c_max = m_connection_b;
    c_min = m_connection_a;
  }

  float max = c_max->getCharge();
  float min = c_min->getCharge(); 
  float volts = max - min;
  float particles = (volts / m_resistance ) * time_units;

  c_max->setCharge(max - particles);
  c_min->setCharge(min + particles);

  c_max = nullptr;
  c_min = nullptr;
}

// Strömmen genom en resistor fås genom att dela spänningen över 
// resistorn med dess resistans.
float Resistor::getCurr() const
{
  return getVolt() / m_resistance;
}
