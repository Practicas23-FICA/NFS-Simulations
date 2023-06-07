#include "TH1D.h"//T = Clase de ROOT; H1 = histograma 1-dimensional;D = tipo do contido, D = double (decimal de máxima precisión)
#include "TRandom.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
void Histo_1()
{
    //gRandom->Gaus();
    auto* h {new TH1D("h", "Histograma; X ", 100, -10, 10)};
    for(int i=0;i<=(int)1e6;i++){
       auto x=gRandom-> Gaus(0,1);
       h->Fill(x);
    }
    auto * c{new TCanvas("c","Histograma")};
    c->cd();
    h->SetLineColor(kBlue);
    h->SetLineWidth(2);
    h->Draw();
    h->Fit("gaus");
    auto* func = h->GetFunction("gaus");
    auto mean = func->GetParameter("Mean");
    auto sigma = func->GetParameter("Sigma");
    std::cout<< "Media = "<< mean<<"\n";
    std::cout<<"Sigma = "<< sigma << "\n";
    auto* file = new TFile("./Histograma.root","recreate");
    file->cd();
    h->Write();
    file->Close();
    delete file;
}