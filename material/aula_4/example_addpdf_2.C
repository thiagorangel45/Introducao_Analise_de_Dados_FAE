#include "TCanvas.h"
#include <iostream>

using namespace RooFit;

void example_addpdf_2()
{
    RooRealVar x("x", "x", 0.0, 1.0);
    RooRealVar mu("mu", "mean", 0.5, 0, 1);
    RooRealVar sigma("sigma", "sigma", 0.1, 0, 0.3);
    RooGaussian gaus("gaus", "gaus", x, mu, sigma);

    RooRealVar slope("slope", "slope", -0.3, -10., 10.);
    RooPolynomial linear("linear", "linear", x, RooArgSet(slope));

    RooRealVar fraction("fraction", "fraction", 0.5, 0., 1.);
    RooAddPdf model("model", "model", RooArgList(gaus, linear), RooArgList(fraction));

    RooDataSet *data = model.generate(x, 10000);
    RooFitResult *fit_result = model.fitTo(*data, RooFit::Save());
    fit_result->Print("v");

    TCanvas *c1 = new TCanvas();
    RooPlot *frame = x.frame();
    data->plotOn(frame);
    model.plotOn(frame);
    model.plotOn(frame, Components(linear), LineStyle(7), LineColor(kRed));
    frame->Draw();
    c1->Draw();
    c1->SaveAs("exemplo_somaPDF.png");
}