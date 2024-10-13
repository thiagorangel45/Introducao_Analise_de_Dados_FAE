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

    RooRealVar mass("mass", "Massa [GeV/c^{2}]", 2.5, 3.5);  

    // Definindo a Crystal Ball
    RooRealVar mean("mean", "Média", 3.096916, 3.0, 3.2); 
    RooRealVar sigma("sigma", "Desvio Padrão", 0.01, 0.001, 0.1);
    RooRealVar alpha("alpha", "Alpha", 1.0, 0.1, 5.0);
    RooRealVar n("n", "n", 1.0, 0.1, 5.0);
    RooCBShape CB("CB", "Sinal JPsi", mass, mean, sigma, alpha, n);

    RooRealVar lambda("lambda", "lambda", 1, 0, 10);
    RooExponential exp("exp", "background", mass, lambda);

    RooRealVar nsig("nsig", "Número de Sinal", 200, 0, 1000);
    RooRealVar nbkg("nbkg", "Número de Fundo", 300, 0, 1000);
    RooAddPdf model("model", "Modelo Sinal + Fundo", RooArgList(CB, exp), RooArgList(nsig, nbkg));

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
