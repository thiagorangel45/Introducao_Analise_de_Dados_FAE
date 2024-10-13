#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooPolynomial.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooFit.h" 

void exercicio_3() {

    TFile *file = TFile::Open("DataSet_lowstat.root");
    RooDataSet *data = (RooDataSet*)file->Get("data");

    RooRealVar mass("mass", "Massa [GeV/c^{2}]", 2, 6);  

    // Definindo a Crystal Ball
    RooRealVar mean("mean", "mean", 3.1, 2.8, 3.2); 
    RooRealVar sigma("sigma", "sigma", 0.3, 0.0001, 1.); 
    RooRealVar alfa("alfa", "alfa", 1.5, -5., 5.); 
    RooRealVar n("n", "n", 1.5, 0.5, 5.);
    RooCBShape CB( "CB","CB", mass , mean , sigma , alfa , n);


    RooRealVar a1("a1", "a1", -0.7, -2., 2.);
    RooRealVar a2("a2", "a2", 0.3, -2., 2.);
    RooRealVar a3("a3", "a3", -0.03, -2., 2.);
    RooPolynomial background("background","The background PDF", mass, RooArgList(a1,a2,a3));

    RooRealVar frac("frac", "frac", 0.5, 0.0, 1.0);
    RooAddPdf model("model", "Modelo Sinal + Fundo", RooArgList(CB, background), RooArgList(frac));

    RooFitResult *fitResult = model.fitTo(*data);

    RooPlot *frame = mass.frame();
    data->plotOn(frame); 
    model.plotOn(frame);
    model.paramOn(frame); 

    double chi2 = frame->chiSquare();
    std::cout << "chi2 / ndf = " << chi2 << std::endl;

    TCanvas *c = new TCanvas("c", "Ajuste JPsi", 800, 600);
    frame->Draw();
    c->SaveAs("fit_result.pdf");
    file->Close();
}