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

#include "Geometry.hh"

#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "SensitiveVolume.hh"

namespace GPPU
{


G4VPhysicalVolume* Geometry::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* matAir = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* matVacuum = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* matAl = nist->FindOrBuildMaterial("G4_Al");
    G4Material* matCu = nist->FindOrBuildMaterial("G4_Cu");
    G4Material* matGe = nist->FindOrBuildMaterial("G4_Ge");
    G4Material* matPb = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* matKapton = nist->FindOrBuildMaterial("G4_KAPTON");

    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    static G4int i_pv = 0; // copy ID for Physical Volume

    //
    // World
    //
    G4double half_world_size = 50.0*cm;

    auto solidWorld =
	new G4Box("World",  // its name
		  half_world_size, half_world_size,half_world_size);  // its size

    auto logiWorld = new G4LogicalVolume(solidWorld,  // its solid
					  matAir,  // its material
					  "World");  // its name

    logiWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    auto physWorld = new G4PVPlacement(nullptr,  // no rotation
				       G4ThreeVector(),  // at (0,0,0)
				       logiWorld,  // its logical volume
				       "World",  // its name
				       nullptr,  // its mother  volume
				       false,  // no boolean operation
				       i_pv++,  // copy number
				       checkOverlaps);  // overlaps checking

    // Lead Shielding
    G4double half_lead_xy = 35.0*cm;
    G4double half_lead_z = 45.0*cm;

    auto solidLeadShielding = new G4Box("solidLeadShielding",
					half_lead_xy,
					half_lead_xy,
					half_lead_z);

    auto logiLeadShielding =
	new G4LogicalVolume(solidLeadShielding,
			    matPb,
			    "logiLeadShielding");
    logiLeadShielding->SetVisAttributes(G4Colour(0.3,0.3,0.3));

    new G4PVPlacement(nullptr, G4ThreeVector(), logiLeadShielding, "physLeadShielding", logiWorld, false, i_pv++, checkOverlaps);


    // Cupper Shielding

    G4double half_cupper_xy = 15.0*cm;
    G4double half_cupper_z = 25.0*cm;

    auto solidCupperShielding = new G4Box("solidCupperShielding",
					half_cupper_xy,
					half_cupper_xy,
					half_cupper_z);

    auto logiCupperShielding =
	new G4LogicalVolume(solidCupperShielding,
			    matCu,
			    "logiCupperShielding");
    logiCupperShielding->SetVisAttributes(G4Colour(1.0,1.0,0.8));

    new G4PVPlacement(nullptr, G4ThreeVector(), logiCupperShielding, "physCupperShielding", logiLeadShielding, false, i_pv++, checkOverlaps);

    // Measurement Area

    G4double half_measurementarea_xy = 10.0*cm;
    G4double half_measurementarea_z = 20.0*cm;

    auto solidMeasurementArea = new G4Box("solidMeasurementArea",
					half_measurementarea_xy,
					half_measurementarea_xy,
					half_measurementarea_z);

    auto logiMeasurementArea =
	new G4LogicalVolume(solidMeasurementArea,
			    matCu,
			    "logiMeasurementArea");
    logiMeasurementArea->SetVisAttributes(G4Colour(0.0,1.0,1.0));
    //logiMeasurementarea->SetVisAttributes(G4VisAttributes::GetInvisible());

    new G4PVPlacement(nullptr, G4ThreeVector(), logiMeasurementArea, "physMeasurementArea", logiCupperShielding, false, i_pv++, checkOverlaps);


    // ------- Ge Detector -------
    // Al case
    G4double radius_alcase = 80.0*mm / 2.0;
    G4double half_z_alcase = 100.0*mm / 2.0;
    G4double thickness_alcase = 0.8*mm;

    auto solidAlCase = new G4Tubs("solidAlCase", 0, radius_alcase, half_z_alcase, 0, CLHEP::twopi);
    auto logiAlCase = new G4LogicalVolume(solidAlCase, matAl, "logiAlCase");
    logiAlCase->SetVisAttributes(G4Colour(0.4,0.4,0.4));

    G4double pos_X_LogiAlCase = 0.0*mm;
    G4double pos_Y_LogiAlCase = 0.0*mm;
    G4double pos_Z_LogiAlCase = (0.0 - half_z_alcase)*mm;
    auto threeVect_LogiAlCase = G4ThreeVector{ pos_X_LogiAlCase, pos_Y_LogiAlCase, pos_Z_LogiAlCase };
    new G4PVPlacement(nullptr, threeVect_LogiAlCase, logiAlCase, "physAlCase", logiMeasurementArea, false, i_pv++, checkOverlaps);


    // Vacuum Space
    G4double radius_vacuumcase = (radius_alcase - thickness_alcase)*mm;
    G4double half_z_vacuumcase =  half_z_alcase - thickness_alcase;

    auto solidVacuumCase = new G4Tubs("solidVacuumCase", 0, radius_vacuumcase, half_z_vacuumcase, 0, CLHEP::twopi);
    auto logiVacuumCase  = new G4LogicalVolume(solidVacuumCase, matVacuum, "logiVacuumCase");
    logiVacuumCase->SetVisAttributes(G4VisAttributes::GetInvisible());
    // logiAlCase->SetVisAttributes(G4Colour(1.0,0.0,0.0));

    G4double pos_X_LogiVacuumCase = 0.0*mm;
    G4double pos_Y_LogiVacuumCase = 0.0*mm;
    G4double pos_Z_LogiVacuumCase = 0.0*mm;
    auto threeVect_LogiVacuumCase = G4ThreeVector{ pos_X_LogiVacuumCase, pos_Y_LogiVacuumCase, pos_Z_LogiVacuumCase };
    new G4PVPlacement(nullptr, threeVect_LogiVacuumCase, logiVacuumCase, "physVacuumCase", logiAlCase, false, i_pv++, checkOverlaps);

    // Kapton window
    G4double radius_kapton = 75.0*mm / 2.0;
    G4double half_z_kapton = 0.1*mm / 2.0;

    auto solidKapton = new G4Tubs("solidKapton", 0, radius_kapton, half_z_kapton, 0, CLHEP::twopi);
    auto logiKapton = new G4LogicalVolume(solidKapton, matKapton, "logiKapton");
    logiKapton->SetVisAttributes(G4Colour(1.0,1.0,0.0));

    G4double pos_X_LogiKapton = 0.0*mm;
    G4double pos_Y_LogiKapton = 0.0*mm;
    G4double pos_Z_LogiKapton = (half_z_alcase - 5.0*mm + half_z_kapton)*mm;
    auto threeVect_LogiKapton = G4ThreeVector{ pos_X_LogiKapton, pos_Y_LogiKapton, pos_Z_LogiKapton };
    new G4PVPlacement(nullptr, threeVect_LogiKapton, logiKapton, "physKapton", logiVacuumCase, false, i_pv++, checkOverlaps);

    // Cu case
    G4double radius_cucase = 75.0*mm / 2.0;
    G4double half_z_cucase = 80.0*mm / 2.0;
    G4double thickness_cucase = 0.8*mm;

    auto solidCuCase = new G4Tubs("solidCuCase", 0, radius_cucase, half_z_cucase, 0, CLHEP::twopi);
    auto logiCuCase = new G4LogicalVolume(solidCuCase, matCu, "logiCuCase");
    logiCuCase->SetVisAttributes(G4Colour(1.0,1.0,0.8));

    G4double pos_X_LogiCuCase = 0.0*mm;
    G4double pos_Y_LogiCuCase = 0.0*mm;
    G4double pos_Z_LogiCuCase = (half_z_alcase - 5.0 - half_z_cucase)*mm;
    auto threeVect_LogiCuCase = G4ThreeVector{ pos_X_LogiCuCase, pos_Y_LogiCuCase, pos_Z_LogiCuCase };
    new G4PVPlacement(nullptr, threeVect_LogiCuCase, logiCuCase, "physCuCase", logiVacuumCase, false, i_pv++, checkOverlaps);

    // Vacuum space
    G4double radius_vacuumspace = (75.0 - thickness_cucase*2) / 2.0*mm;
    G4double half_z_vacuumspace = (80.0 - thickness_cucase) / 2.0*mm;

    auto solidVacuumSpace = new G4Tubs("solidVacuumSpace", 0, radius_vacuumspace, half_z_vacuumspace, 0, CLHEP::twopi);
    auto logiVacuumSpace = new G4LogicalVolume(solidVacuumSpace, matVacuum, "logiVacuumSpace");
    logiVacuumSpace->SetVisAttributes(G4VisAttributes::GetInvisible());
    // logiVacuumSpace->SetVisAttributes(G4Colour(1.0,0.0,0.0));

    G4double pos_X_LogiVacuumSpace = 0.0*mm;
    G4double pos_Y_LogiVacuumSpace = 0.0*mm;
    G4double pos_Z_LogiVacuumSpace = thickness_cucase / 2.0*mm;
    auto threeVect_LogiVacuumSpace = G4ThreeVector{ pos_X_LogiVacuumSpace, pos_Y_LogiVacuumSpace, pos_Z_LogiVacuumSpace };
    new G4PVPlacement(nullptr, threeVect_LogiVacuumSpace, logiVacuumSpace, "physVacuumSpace", logiCuCase, false, i_pv++, checkOverlaps);

    // Ge crystal
    G4double radius_gecrystal = 70.0*mm / 2.0;
    G4double half_z_gecrystal = 60.0*mm / 2.0;

    auto solidGeCrystal = new G4Tubs("solidGeCrystal", 0, radius_gecrystal, half_z_gecrystal, 0, CLHEP::twopi);
    auto logiGeCrystal = new G4LogicalVolume(solidGeCrystal, matGe, "logiGeCrystal");
    logiGeCrystal->SetVisAttributes(G4Color(1.0,0.0,1.0));

    G4double pos_X_LogiGeCrystal = 0.0*mm;
    G4double pos_Y_LogiGeCrystal = 0.0*mm;
    G4double pos_Z_LogiGeCrystal = (half_z_vacuumspace - half_z_gecrystal)*mm;
    auto threeVect_LogiGeCrystal = G4ThreeVector{ pos_X_LogiGeCrystal, pos_Y_LogiGeCrystal, pos_Z_LogiGeCrystal };
    new G4PVPlacement(nullptr, threeVect_LogiGeCrystal, logiGeCrystal, "physGeCrystal", logiVacuumSpace, false, i_pv++, checkOverlaps);

    // VacuumCore
    G4double radius_vacuumcore = 8.0*mm / 2.0;
    G4double half_z_vacuumcore = 45.0*mm / 2.0;

    auto solidVacuumCore = new G4Tubs("solidVacuumCore", 0, radius_vacuumcore, half_z_vacuumcore, 0, CLHEP::twopi);
    auto logiVacuumCore = new G4LogicalVolume(solidVacuumCore, matVacuum, "logiVacuumCore");

    G4double pos_X_LogiVacuumCore = 0.0*mm;
    G4double pos_Y_LogiVacuumCore = 0.0*mm;
    G4double pos_Z_LogiVacuumCore = (0.0 - half_z_gecrystal + half_z_vacuumcore)*mm;
    auto threeVect_LogiVacuumCore = G4ThreeVector{ pos_X_LogiVacuumCore, pos_Y_LogiVacuumCore, pos_Z_LogiVacuumCore };
    new G4PVPlacement(nullptr, threeVect_LogiVacuumCore, logiVacuumCore, "physVacuumCore", logiGeCrystal, false, i_pv++, checkOverlaps);

    //
    // Sensitive Detector
    //
    auto sdManager = G4SDManager::GetSDMpointer();
    SensitiveVolume* sd = new SensitiveVolume("GeCrystal");
    sdManager->AddNewDetector(sd);
    logiGeCrystal->SetSensitiveDetector(sd);

    return physWorld;
}

}  // namespace GPPU
