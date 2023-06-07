#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
void Func_2()
{
auto* f = new TF1("f", "TMath::Sin(x)/x",-5,5);
auto* g = new TGraph();
for(double x=-5;x<=5;x+=0.1)
{
auto idx = g ->GetN();
auto y = f -> Eval(x);
 g->SetPoint(idx,x,y) ;
}


f->SetTitle("sin(x)/x;x;y");
auto* c = new TCanvas("c","sin(x)/x");
c->Divide(2,1);
c->cd(1);
f->Draw();
c->cd(2);
g->SetMarkerStyle(24);
g->SetLineWidth(2);
g->Draw("apl");
}