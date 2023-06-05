/* This macro builds a SimGeometry object
and stores the ACTAR TPC and the Silicon Info in a .root file
*/

#include "SimGeometry.h"

#include <map>
#include <string>
#include <utility>

void BuildGeometry()
{
    //1--> Define protoACTAR chamber sizes
    double driftX { 12.8 / 2};//cm
    double driftY {  6.4 / 2};
    double driftZ { 17.0 / 2};
    DriftInfo protoactar(driftX, driftY, driftZ);
    //2--> Silicon unit sizes
    double silicon1X { 5.0E-2 / 2};//cm, thickness
    double silicon1Y { 5.0    / 2};
    double silicon1Z { 5.0    / 2};
    SilUnit silUnit(0, silicon1X, silicon1Y, silicon1Z);
    //3--> Build left assembly!
    std::map<int, std::pair<double, double>> leftPlacements {
        {1, std::make_pair(+2 * silicon1Y, +silicon1Z)},
        {2, std::make_pair(+0 * silicon1Y, +silicon1Z)},
        {3, std::make_pair(-2 * silicon1Y, +silicon1Z)},
        {4, std::make_pair(-2 * silicon1Y, -silicon1Z)},
        {5, std::make_pair(+0 * silicon1Y, -silicon1Z)},
        {6, std::make_pair(+2 * silicon1Y, -silicon1Z)},
    };
    SilAssembly leftAss(0, silUnit, false, true);
    leftAss.SetOffsets(-1, 7. + driftY);//supposed to be the real value of offset
    leftAss.SetAssemblyPlacements(leftPlacements);
    leftAss.SetMirror(true);

    //BUILD GEOMETRY!
    SimGeometry geo {};
    geo.SetDrift(protoactar);
    geo.AddAssemblyData(leftAss);
    geo.ConstructPlus();
    geo.PrintGeometryPlus();

    //SAVE GEO
    geo.WriteGeometry("./", "geo0");

    geo.Draw();
}
