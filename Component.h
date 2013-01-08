//// COMPONENT.H (ingen CC) ////
// perjo927 & linja919

//  Resistorer, Batterier, Kondensatorer 
//  Dessa  komponenter är sammankopplade via kopplingspunkter. 

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Connection.h"

#include <string>
#include <cmath> // för fabs()

class Component
{  
public:
  Component(std::string name, Connection& ca, Connection& cb) :
  m_name(name), m_connection_a(&ca), m_connection_b(&cb) {}
  virtual ~Component() {}

   Component(Component const&) = delete; 
   Component& operator=(Component const&) = delete; 
  
  virtual void moveCharge(float time_units) = 0;
  virtual float getCurr() const = 0;
  
  float getVolt() const
  {return (fabs(m_connection_a->getCharge() - m_connection_b->getCharge()));}
  std::string getName() { return m_name; }

protected:
  std::string m_name;
  Connection* m_connection_a = nullptr; 
  Connection* m_connection_b = nullptr;
};

#endif


