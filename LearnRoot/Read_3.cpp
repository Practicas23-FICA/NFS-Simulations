#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <stdexcept>

void Read_3()
{
auto* f = new TFile("Histograma.root");
auto* h = f-> Get<TH1D>("h1");
if (!h){
    throw std::runtime_error("h non existe");
}
h->Draw();
}