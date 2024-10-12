#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooFit.h"

void importar_dados()
{
    TFile *file = new TFile("/opendata/example_data.root", "READ");
    TTree *tree = (TTree*)file->Get("nt");
    TCanvas *c1 = new TCanvas();

    RooRealVar x("mass", "mass", 0.0, 2.0);
    RooDataSet dataUnbinned("dataUnbinned", "Unbinned Data", RooArgSet(x), RooFit::Import(*tree));
    std::cout << "dados importados" << std::endl;
    dataUnbinned.Print("v");

    RooPlot *frame = x.frame();
    dataUnbinned.plotOn(frame, RooFit::MarkerColor(kBlue), RooFit::Name("Unbinned"));
    frame->Draw();
    c1->Draw();
    c1->SaveAs("ImportarDadosUnbinned.png");
    file->Close();
}