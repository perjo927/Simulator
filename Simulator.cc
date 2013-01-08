// ** SIMULATOR.CC ** //
// LiU-ID: perjo927 & linja919 IP1

#include <iostream>
#include <iomanip>
#include <vector>
#include <exception>

#include "Battery.h"
#include "Resistor.h"
#include "Capacitator.h"

using namespace std;

// Argument från kommandoraden:
// - Hur många iterationer som ska simuleras
// - Hur många iterationer(rader) som ska skrivas ut
// - Hur stort tidsintervall som simuleras i varje steg
// - Spänningen på batteriet
//  Om något av dessa saknas eller är ogiltigt skall programmet
// avsluta med ett  felmeddelande. 
bool read_arguments(int argc, char* argv[], int& iterations, int& print_outs,
                    float& time_units, float& volts)
{
  // argc: Antalet ord på kommandoraden (inkl programmets namn)
  if (argc != 5)
  {
    cerr << "FEL: Fel antal argument på kommandoraden!" << endl;
    return false;
  }

  // Konvertera till vector med C++-strängar (säkrare)
  // Inbyggd array och C-strängar ger INTE djupa kopior
  vector<string> arg(argv, argv+argc);

  // Försök konvertera från strängar till hel- och flyttal
  try
  {
    iterations = stoi(arg[1]);
    print_outs = stoi(arg[2]);
    time_units = stof(arg[3]);
    volts = stof(arg[4]);
  }
  catch (exception& e)
  {
    cerr <<  endl <<  "Fel vid konvertering av kommandoradsargument ("
         << e.what() << ")" << endl;
    return false;
  }
  
  return true;
}

// Loopa igenom vektorn 1 tidssteg och simulera varje komponent x steg
void simulate(vector<Component*>& net, int const iterations,
              int const print_outs, float const time_units) 
{
  // när vi ska skriva ut?
  int print = iterations / print_outs; 


  // Skriv ut tabellhuvud
  std::vector<Component*>::iterator comp; 
  for (unsigned i = 0; i < net.size(); ++i) 
  {
    cout << setw(11) << net[i]->getName() << setw(2) << "";
  } 
  cout << endl;
  for (unsigned i = 0; i < net.size(); ++i) 
  {
    cout << setw(5) << "Volt" << setw(6) << "Curr" << setw(2) << "";
  }

  // ** Simulera tid, x antal tidssteg ** //
  for (int i = 1; i <= iterations; ++i) // undvika att dela med 0
  {
    // Simulera rörelse för varje tidssteg
    for (comp = net.begin(); comp != net.end(); ++comp)
    {
      (*comp)->moveCharge(time_units);
    }
    
    // Skriv ut resultat var x:e gång
    if (i %  print == 0) 
    {
      cout << endl;
      
      // Mät spänning och ström och skriv ut
      for (comp = net.begin(); comp != net.end(); ++comp) 
      {
        cout << fixed << setprecision(2) << setw(5)
             << (*comp)->getVolt() << setw(6)
             << (*comp)->getCurr() << setw(2) << "";
      } 
    }
  }
}

////////////////////////////////
int main(int argc, char* argv[])
{
  // Dessa värden tilldelas från kommandoraden
  int iterations, print_outs;
  float time_units, volts;
  
  // Testa att läsa in och konvertera kommandoraden
  if (!read_arguments(argc, argv, iterations, print_outs, time_units, volts))
  {
    return 0;
  }

  // EXEMPEL 1 
  Connection p, n, r, l;
  vector<Component*> net;

  net.push_back(new Battery("Bat", volts, p, n)); 
  net.push_back(new Resistor("R1", 150.0, p, l));
  net.push_back(new Resistor("R2", 50.0, p, r));
  net.push_back(new Resistor("R3", 100.0, r, l));
  net.push_back(new Resistor("R4", 300.0, n, l));
  net.push_back(new Resistor("R5", 250.0, r, n));

  cout << endl << "EXEMPEL 2" << endl; 

  simulate(net, iterations, print_outs, time_units);

  // Rensa
  for (comp = net.begin(); comp != net.end(); ++comp)
  {
    delete *comp;
  }
  net.clear();

  // EXEMPEL 1 
  // Återställ kopplingspunkter
  p.setCharge(0);  n.setCharge(0);
  r.setCharge(0);  l.setCharge(0);

  net.push_back(new Battery("Bat", volts, p, n)); 
  net.push_back(new Resistor("R1", 150.0, p, l));
  net.push_back(new Resistor("R2", 50.0, p, r));
  net.push_back(new Capacitator("C3", 1.0, r, l));
  net.push_back(new Resistor("R4", 300.0, n, l));
  net.push_back(new Capacitator("C5", 0.75, r, n));

  cout << endl << "EXEMPEL 3" << endl;
  
  simulate(net, iterations, print_outs, time_units);

  // Rensa
  for(comp = net.begin(); comp != net.end(); ++comp)
  {
    delete *comp;   
  }
  net.clear();


  cout << endl; 

  return 0;
}


