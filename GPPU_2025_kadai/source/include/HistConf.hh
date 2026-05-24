#ifndef HistConf_h
#define HistConf_h 1

#include "G4SystemOfUnits.hh"

namespace GPPU
{
namespace HistConf
{

constexpr G4double MinEdepGe = 0.*MeV;
constexpr G4double MaxEdepGe = 3.*MeV;
constexpr G4double BinWidthEdepGe = 0.5*keV;
constexpr G4int    NBinEdepGe = static_cast<G4int>(std::round((MaxEdepGe - MinEdepGe) / BinWidthEdepGe));

constexpr G4double MinVtx = -100.*cm;
constexpr G4double MaxVtx =  100.*cm;
constexpr G4double BinWidthVtx = 1.*mm;
constexpr G4int    NBinVtx = static_cast<G4int>(std::round((MaxVtx - MinVtx) / BinWidthVtx));

constexpr G4double MinDir = -1.;
constexpr G4double MaxDir =  1.;
constexpr G4double BinWidthDir = 0.01;
constexpr G4int    NBinDir = static_cast<G4int>(std::round((MaxDir - MinDir) / BinWidthDir));

constexpr G4double MinPhi = -CLHEP::pi;
constexpr G4double MaxPhi =  CLHEP::pi;
constexpr G4double BinWidthPhi = 1*deg;
constexpr G4int    NBinPhi = static_cast<G4int>(std::round((MaxPhi - MinPhi) / BinWidthPhi));

// constexpr G4double MinVtx_X = -100.*cm;
// constexpr G4double MaxVtx_X =  100.*cm;
// constexpr G4double BinWidthVtx_X = 1.*mm;
// constexpr G4int    NBinVtx_X = static_cast<G4int>((MaxVtx_X - MinVtx_X) / BinWidthVtx_X);

// constexpr G4double MinVtx_Y = -100.*cm;
// constexpr G4double MaxVtx_Y =  100.*cm;
// constexpr G4double BinWidthVtx_Y = 1.*mm;
// constexpr G4int    NBinVtx_Y = static_cast<G4int>((MaxVtx_Y - MinVtx_Y) / BinWidthVtx_Y);

// constexpr G4double MinVtx_Z = -100.*cm;
// constexpr G4double MaxVtx_Z =  100.*cm;
// constexpr G4double BinWidthVtx_Z = 1.*mm;
// constexpr G4int    NBinVtx_Z = static_cast<G4int>((MaxVtx_Z - MinVtx_Z) / BinWidthVtx_Z);

// constexpr G4double MinDir_X = -1.;
// constexpr G4double MaxDir_X =  1.;
// constexpr G4double BinWidthDir_X = 0.1;
// constexpr G4int    NBinDir_X = static_cast<G4int>((MaxDir_X - MinDir_X) / BinWidthDir_X);

// constexpr G4double MinDir_Y = -1.;
// constexpr G4double MaxDir_Y =  1.;
// constexpr G4double BinWidthDir_Y = 0.1;
// constexpr G4int    NBinDir_Y = static_cast<G4int>((MaxDir_Y - MinDir_Y) / BinWidthDir_Y);

// constexpr G4double MinDir_Z = -1.;
// constexpr G4double MaxDir_Z =  1.;
// constexpr G4double BinWidthDir_Z = 0.1;
// constexpr G4int    NBinDir_Z = static_cast<G4int>((MaxDir_Z - MinDir_Z) / BinWidthDir_Z);

} // namespace HistConf

} // namespace GPPU

#endif
