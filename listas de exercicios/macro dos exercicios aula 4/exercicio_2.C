#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooDataSet.h"
#include "RooExtendPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "RooFitResult.h"

void exercicio_2() {

    RooRealVar x("x", "x", 5, 10);
    RooRealVar lambda("lambda", "lambda", 1, 0.1, 2);
    RooExponential exp("exp", "Exponential PDF", x, lambda);
    
    RooDataSet* data = exp.generate(x, 10000);
    RooFitResult* fitResult = exp.fitTo(*data, RooFit::Save());

    RooPlot* xframe = x.frame(RooFit::Title(""));
    data->plotOn(xframe);  
    exp.plotOn(xframe);  
    TCanvas* c = new TCanvas("c", "Ajuste Exponencial", 800, 600);
    xframe->Draw();  

    fitResult->Print();
    c->SaveAs("exponential_fit.png");
}
