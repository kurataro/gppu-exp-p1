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

#include "RunAction.hh"

#include "Geometry.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4AnalysisManager.hh"

#include "HistConf.hh"

namespace GPPU
{

RunAction::RunAction(G4String filename)
{
// Create analysis manager

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(false);
  // analysisManager->SetDefaultFileType("csv");
  //analysisManager->SetDefaultFileType("root");
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetVerboseLevel(1);

  analysisManager->SetFileName(filename);
  // Book histograms, ntuple
  // Create Histogram
  analysisManager->CreateH1("h_EdepTotal_Ge", "Total Energy Deposit in Ge Crystal [MeV]", HistConf::NBinEdepGe, HistConf::MinEdepGe, HistConf::MaxEdepGe, "MeV");
  analysisManager->CreateH1("h_Vtx_X", "X Position of Primary Vertex [mm]", HistConf::NBinVtx, HistConf::MinVtx, HistConf::MaxVtx, "mm");
  analysisManager->CreateH1("h_Vtx_Y", "Y Position of Primary Vertex [mm]", HistConf::NBinVtx, HistConf::MinVtx, HistConf::MaxVtx, "mm");
  analysisManager->CreateH1("h_Vtx_Z", "Z Position of Primary Vertex [mm]", HistConf::NBinVtx, HistConf::MinVtx, HistConf::MaxVtx, "mm");
  analysisManager->CreateH1("h_Dir_X", "X Vector of Primary Particle Direction", HistConf::NBinDir, HistConf::MinDir, HistConf::MaxDir, "none");
  analysisManager->CreateH1("h_Dir_Y", "Y Vector of Primary Particle Direction", HistConf::NBinDir, HistConf::MinDir, HistConf::MaxDir, "none");
  analysisManager->CreateH1("h_Dir_Z", "Z Vector of Primary Particle Direction", HistConf::NBinDir, HistConf::MinDir, HistConf::MaxDir, "none");
  analysisManager->CreateH1("h_Phi", "Phi Distribution of Primary Particle Direction [rad]", HistConf::NBinPhi, HistConf::MinPhi, HistConf::MaxPhi, "rad");

  // Creating ntuple
  analysisManager->CreateNtuple("Edep","Energy Deposit in Ge");
  analysisManager->CreateNtupleIColumn("evnum");
  analysisManager->CreateNtupleDColumn("Edep_total");
  analysisManager->CreateNtupleDColumn("Vtx_X");
  analysisManager->CreateNtupleDColumn("Vtx_Y");
  analysisManager->CreateNtupleDColumn("Vtx_Z");
  analysisManager->CreateNtupleDColumn("Dir_X");
  analysisManager->CreateNtupleDColumn("Dir_Y");
  analysisManager->CreateNtupleDColumn("Dir_Z");
  analysisManager->CreateNtupleDColumn("Phi");
  analysisManager->FinishNtuple();
}

// RunAction::RunAction()
// {
// // Create analysis manager

//   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//   analysisManager->SetNtupleMerging(false);
//   analysisManager->SetDefaultFileType("csv");
//   //analysisManager->SetDefaultFileType("root");
//   G4cout << "Using " << analysisManager->GetType() << G4endl;

//   analysisManager->SetVerboseLevel(1);
//   G4String fileName = "outGPPU";
//   analysisManager->SetFileName(fileName);

//   // Book histograms, ntuple
//   //

//   // Creating ntuple
//   /*
//   analysisManager->CreateNtuple("Edep","Energy Deposit in Ge");

//   analysisManager->FinishNtuple();
//   */
// }


RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  // Get analysis manager and open an output file
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Reset();

  analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run*)
{
  //save histograms & ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile(false);

}

}  // namespace GPPU
