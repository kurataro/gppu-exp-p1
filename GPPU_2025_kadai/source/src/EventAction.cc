//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "RunAction.hh"
#include "G4AnalysisManager.hh"

#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"

namespace GPPU
{


EventAction::EventAction()
  : fTotalEdepGe(0.) {}


void EventAction::BeginOfEventAction(const G4Event*)
{
  fTotalEdepGe = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    auto primaryVtx = event->GetPrimaryVertex();
    auto primaryPart = primaryVtx->GetPrimary();

    auto vtx = primaryVtx->GetPosition();
    auto dir = primaryPart->GetMomentumDirection();

    // ----- Fill Histogram -----
    analysisManager->FillH1(analysisManager->GetH1Id("h_EdepTotal_Ge"), fTotalEdepGe);
    // Vertex
    analysisManager->FillH1(analysisManager->GetH1Id("h_Vtx_X"), vtx.x());
    analysisManager->FillH1(analysisManager->GetH1Id("h_Vtx_Y"), vtx.y());
    analysisManager->FillH1(analysisManager->GetH1Id("h_Vtx_Z"), vtx.z());
    // Direction
    analysisManager->FillH1(analysisManager->GetH1Id("h_Dir_X"), dir.x());
    analysisManager->FillH1(analysisManager->GetH1Id("h_Dir_Y"), dir.y());
    analysisManager->FillH1(analysisManager->GetH1Id("h_Dir_Z"), dir.z());
    analysisManager->FillH1(analysisManager->GetH1Id("h_Phi"), dir.phi());


    // ----- Fill NTuple -----
    analysisManager->FillNtupleIColumn(0, event->GetEventID());
    analysisManager->FillNtupleDColumn(1, fTotalEdepGe);
    // Vertex
    analysisManager->FillNtupleDColumn(2, vtx.x());
    analysisManager->FillNtupleDColumn(3, vtx.y());
    analysisManager->FillNtupleDColumn(4, vtx.z());
    // Direction
    analysisManager->FillNtupleDColumn(5, dir.x());
    analysisManager->FillNtupleDColumn(6, dir.y());
    analysisManager->FillNtupleDColumn(7, dir.z());
    analysisManager->FillNtupleDColumn(8, dir.phi());

    analysisManager->AddNtupleRow();
}


}  // namespace GPPU
