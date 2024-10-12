#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooFit.h"


void gaussian_plot()
{
    RooRealVar x("x", "x", 0, -10, 10);
    RooRealVar mean("mean", "mean of gaussian", 0, -10, 10);
    RooRealVar width("width", "width of gaussian", 3, 0.1, 10);
    RooGaussian gaus("gaus", "Gaussian", x, mean, width);

    RooPlot *frame = x.frame();
    gaus.plotOn(frame);

    TCanvas *c1 = new TCanvas();
    frame->Draw();
    c1->Draw();
    c1->SaveAs("gaussian.png");

}