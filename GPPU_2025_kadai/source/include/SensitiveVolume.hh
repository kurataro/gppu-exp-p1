//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SensitiveVolume.hh
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef SensitiveVolume_h
#define SensitiveVolume_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;
namespace GPPU
{

//------------------------------------------------------------------------------
  class SensitiveVolume : public G4VSensitiveDetector
//------------------------------------------------------------------------------
{
  public:
      SensitiveVolume(G4String name);
     ~SensitiveVolume();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
private:
    G4double fSumEdepGe = 0.;

};

}
#endif
