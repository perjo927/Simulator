//// CAPACITATOR.CC ////
// perjo927 & linja919

#include "Capacitator.h"

using namespace std;

Capacitator::Capacitator(string name, float capacity, Connection& ca, Connection& cb) :
  Component(name, ca, cb), m_capacity(capacity), m_charge(0) {}

/* En kondensator suger upp positiva laddningspartiklar från sin mest 
   positiva sida och lagrar dessa internt. Samtidigt suger den upp lika 
   många negativa laddningspartiklar från sin minst positiva  sida
   (vilket  innebär att den lägger till positiva laddningspartiklar där). */

/* Antag att kapacitancen är 0.8 Fahrad och vi simulerar i steg om 0.1 
   tidsenheter. Om laddningen på sida a är 5.0 och laddnigen på sida b är 9.0 
   så är skillnaden 9.0 − 5.0 = 4.0. Om vi har 3.0 lagrat sedan tidigare så 
   kommer vi nu lagra ytterligare 0.8 * (4.0−3.0) * 0.1.
   
   Dessa tas från sidan med högst laddning och läggs till både internt och
   på andra sidan. */

void Capacitator::moveCharge(float time_units)
{
  Connection* c_max= nullptr; 
  Connection* c_min = nullptr;

  // Hitta mest positiva laddning
  if (m_connection_a->getCharge() > m_connection_b->getCharge())
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
  float diff = max - min;
  float particles = m_capacity * (diff - m_charge) * time_units;

  m_charge += particles;
  c_max->setCharge(max - particles);
  c_min->setCharge(min + particles);

  c_max = nullptr;
  c_min = nullptr;
}

// Strömmen genom en kondensator approximerar vi med C(V −L)
// C är kapacitansen, V spänningen över kondensatorn och L laddningen
float Capacitator::getCurr() const
{
  return m_capacity * (getVolt() - m_charge);
}
