#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooDataSet.h"
#include "RooExtendPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "RooFitResult.h"
#include "TLegend.h"

void exercicio_2() {
    RooRealVar x("x", "x", 5, 10);
    RooRealVar lambda("lambda", "lambda", 1, 0.1, 2);
    RooExponential exp("exp", "Exponential PDF", x, lambda);
    
    RooDataSet* data = exp.generate(x, 1500);
    RooFitResult* fitResult = exp.fitTo(*data, RooFit::Save());

    RooPlot* xframe = x.frame(RooFit::Title(""));
    data->plotOn(xframe);  
    exp.plotOn(xframe);  

    int totalEvents = data->numEntries();

    TLegend *leg = new TLegend(0.6, 0.7, 0.88, 0.9);  
    leg->AddEntry(xframe->findObject("data"), "Dados", "PL");  
    leg->AddEntry(xframe->findObject("exp"), "Ajuste Exponencial", "l");
    leg->AddEntry((TObject*)0, Form("#lambda = %.3f", lambda.getVal()), "");  
    leg->AddEntry((TObject*)0, Form("Total de Eventos: %d", totalEvents), "");  // Adicionando total de eventos à legenda

    TCanvas* c1 = new TCanvas("c1", "Ajuste Exponencial", 800, 600);
    xframe->SetTitle("");
    xframe->Draw();  
    leg->Draw();  

    c1->SaveAs("exponential_fit.png");
}
