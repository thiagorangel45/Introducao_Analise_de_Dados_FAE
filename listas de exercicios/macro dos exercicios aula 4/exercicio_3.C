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

    RooRealVar mean("mean", "mean", 3.1, 2.8, 3.2); 
    RooRealVar sigma("sigma", "sigma", 0.3, 0.0001, 1.); 
    RooRealVar alfa("alfa", "alfa", 1.5, -5., 5.); 
    RooRealVar n("n", "n", 1.5, 0.5, 5.);
    RooCBShape CB("CB", "CB", mass, mean, sigma, alfa, n);

    RooRealVar a1("a1", "a1", -0.7, -2., 2.);
    RooRealVar a2("a2", "a2", 0.3, -2., 2.);
    RooRealVar a3("a3", "a3", -0.03, -2., 2.);
    RooPolynomial background("background", "The background PDF", mass, RooArgList(a1, a2, a3));

    RooRealVar frac("frac", "frac", 0.5, 0.0, 1.0);
    RooAddPdf model("model", "Modelo Sinal + Fundo", RooArgList(CB, background), RooArgList(frac));

    RooFitResult *fitResult = model.fitTo(*data, RooFit::Save());

    RooPlot *frame = mass.frame();
    data->plotOn(frame); 
    model.plotOn(frame);
    model.paramOn(frame); 

    double chi2 = frame->chiSquare();
    int ndf = data->numEntries() - fitResult->floatParsFinal().getSize();  // Calculando ndf

    std::cout << "chi2 / ndf = " << chi2 << " / " << ndf << std::endl;

    TLegend *leg = new TLegend(0.4, 0.7, 0.6, 0.9);
    leg->AddEntry(frame->findObject("data"), "Dados", "PL");  
    leg->AddEntry(frame->findObject("model"), "Modelo Ajustado", "l");
    leg->AddEntry((TObject*)0, Form("mean = %.3f", mean.getVal()), "");
    leg->AddEntry((TObject*)0, Form("sigma = %.3f", sigma.getVal()), "");
    leg->AddEntry((TObject*)0, Form("chi2/ndf = %.3f", chi2), "");

    TCanvas *c = new TCanvas("c", "Ajuste JPsi", 800, 600);
    frame->SetTitle("");
    frame->Draw();
    leg->Draw();  // Desenhando a legenda
    c->SaveAs("fit_result.pdf");
    file->Close();
}
