//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SensitiveVolume.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SensitiveVolume.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "EventAction.hh"

namespace GPPU
{
//------------------------------------------------------------------------------
  SensitiveVolume::SensitiveVolume(G4String name)
    : G4VSensitiveDetector(name)
{}
//------------------------------------------------------------------------------
  SensitiveVolume::~SensitiveVolume()
{}
//------------------------------------------------------------------------------
  void SensitiveVolume::Initialize(G4HCofThisEvent*)
{
     fSumEdepGe = 0.;
}
//------------------------------------------------------------------------------
  void SensitiveVolume::EndOfEvent(G4HCofThisEvent*)
{
  auto runManager = G4RunManager::GetRunManager();
  // auto eventAction = dynamic_cast<EventAction*>(runManager->GetUserEventAction());
  auto eventAction = (EventAction*)(runManager->GetUserEventAction());

  if (eventAction) {
    eventAction->AddEdepGe(fSumEdepGe);
  }

}

//------------------------------------------------------------------------------
  G4bool SensitiveVolume::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  fSumEdepGe += aStep->GetTotalEnergyDeposit();
  return true;
}

}
