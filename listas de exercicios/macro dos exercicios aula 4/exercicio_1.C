#include "RooRealVar.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TRandom3.h"

void exercicio_1() {

    RooRealVar x("x", "x", -10, 10);
    RooRealVar mean("mean", "mean", 0, -10, 10);  
    RooRealVar sigma("sigma", "sigma", 1, 0.1, 5);  
    RooRealVar alpha("alpha", "alpha", 1.5, 0.1, 10);  
    RooRealVar n("n", "n", 2, 0.1, 10);  
    RooCBShape crystalball("crystalball", "Crystal Ball PDF", x, mean, sigma, alpha, n);

    RooDataSet* data = crystalball.generate(x, 10000);  
    RooFitResult* fitResult = crystalball.fitTo(*data, RooFit::Save());
    RooPlot* xframe = x.frame(RooFit::Title("Ajuste da pdf Crystal Ball aos Dados"));
    data->plotOn(xframe);  
    crystalball.plotOn(xframe);  

    fitResult->Print();  

    TCanvas* c1 = new TCanvas("c1", "Ajuste da pdf Crystal Ball", 800, 600);
    xframe->Draw();  
    c1->SaveAs("crystalball_fit.png");
}
