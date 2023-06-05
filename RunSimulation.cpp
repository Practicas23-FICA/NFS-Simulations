#include "Math/Point3D.h"
#include "Math/Vector3D.h"
#include "TRandom.h"
#include "TMath.h"

#include "SimGeometry.h"
#include "SimCrossSection.h"

using XYZPoint = ROOT::Math::XYZPoint;
using XYZVector = ROOT::Math::XYZVector;

void RunSimulation()
{
    //Configure simulation
    int niter {10};

    //Read geometry
    auto* geo {new SimGeometry()};
    geo->ReadGeometry("./Geometries/", "geo0");

    //Read cross sections
    SimCrossSection xs {};
    xs.ReadScatteringCrossSection("./XSData/JEFF3_1_neutron_elastic_hydrogen.dat");
    xs.ReadAngularCrossSection("./XSData/JEFF3_1_neutron_elastic_hydrogen_angular.dat");
    xs.ComputeXSAtEnergy(15.);//MeV
    
    //geo->Draw();
    gRandom->SetSeed();

    for(int i = 0; i < niter; i++)
    {
        XYZPoint vertex {0, 0, 0};
        auto theta {gRandom->Uniform(- TMath::PiOver2(), TMath::PiOver2())};
        XYZVector direction {TMath::Cos(theta), TMath::Sin(theta), 0};
        xs.SampleXS();
        int silIndex {}; int silType {}; bool isMirror {};
        double dist {}; XYZPoint newPoint {};
        geo->PropagateTrackToSiliconArray(vertex, direction, 0, isMirror, dist, silType, silIndex, newPoint, false);
    }
    xs.DrawXS();
}
