//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PhysicsList.cc
//  [Note] Based on "G4 Basic Example: B3"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4SystemOfUnits.hh"

namespace GPPU
{
    
//------------------------------------------------------------------------------
  PhysicsList::PhysicsList()
  : G4VModularPhysicsList()
//------------------------------------------------------------------------------
{
// Default physics
   RegisterPhysics(new G4DecayPhysics());

// Radioactive decay
   RegisterPhysics(new G4RadioactiveDecayPhysics());

// EM physics
   RegisterPhysics(new G4EmStandardPhysics());
   //RegisterPhysics(new G4EmLivermorePhysics());

}

//------------------------------------------------------------------------------
  PhysicsList::~PhysicsList()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void PhysicsList::SetCuts()
//------------------------------------------------------------------------------
{
    SetCutValue(0.01*mm,"gamma");
    SetCutValue(0.01*mm,"e-");
    SetCutValue(0.01*mm,"e+");

}

}
