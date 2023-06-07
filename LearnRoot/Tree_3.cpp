#include "TFile.h"
#include "TTree.h"

void Tree_3()
{
auto* fout = new TFile("./Tree.root","recreate");
auto* tree= new TTree("Test","Trying TTree class");
double x{};
tree-> Branch ("x",&x);
double y{};
tree-> Branch ("y",&y);
tree-> Print();
}