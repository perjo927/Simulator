// CONNECTION.H (+CC)//
// perjo927 & linja919

#ifndef __CONNECTION_H__
#define __CONNECTION_H__

class Connection
{
/*  Varje komponent måste vara kopplad till två 
    (olika) kopplingspunkter. Varje kopplingspunkt
    representeras av en viss laddning och kan vara
    kopplad till oändligt många komponenter.
   
    Kopplingspunkterna behöver bara veta sin laddning,
    inte vad som är anslutet. */
  
private:
  float m_charge; 
  
public:
  Connection() : m_charge(0) {} 
  ~Connection() {} 

  float getCharge() const { return m_charge; }
  void setCharge(float const charge) { m_charge = charge; }
};

#endif
