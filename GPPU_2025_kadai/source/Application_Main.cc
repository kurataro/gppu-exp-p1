//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Space Users: 2015.08.24 @Hiroshima
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "ActionInitialization.hh"
#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "PhysicsList.hh"

using namespace GPPU;

//-------------------------------------------------------------------------------
  int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
   // ============= [ Setting up the application environment ] ================
   G4String dirMacro = "/home/gppuuser09/work/utils/Macros/";
   G4String nameMainMacro = "GlobalSetup.mac";      // Initialization  macros
   // =========================================================================
 // Construct the default run manager
  //
  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new Geometry() );

// Set up mandatory user initialization: Physics-List
   runManager->SetUserInitialization( new PhysicsList );

// Set up user initialization: User Actions
   if (argc == 3) {
     G4String outname = argv[2];
     runManager->SetUserInitialization( new ActionInitialization(outname) );
   } else{
     runManager->SetUserInitialization( new ActionInitialization() );
   }

// Initialize G4 kernel
   runManager->Initialize();

// Create visualization environment
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();

// Start interactive session
   G4UImanager*   uiManager = G4UImanager::GetUIpointer();
   G4UIExecutive* ui = nullptr;
   if(argc==1){
       ui =  new G4UIExecutive(argc, argv);
       uiManager->ApplyCommand("/control/macroPath " + dirMacro);
       uiManager->ApplyCommand("/control/execute " + nameMainMacro);
       ui->SessionStart();
       delete ui;
   } else {
       uiManager->ApplyCommand("/control/execute " + G4String(argv[1]));
   }

// Job termination
   delete visManager;
   delete runManager;

   return 0;
}
