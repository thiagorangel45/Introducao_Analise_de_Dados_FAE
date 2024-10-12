#include <iostream>
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "RooRealVar.h"
#include "RooCrystalBall.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooFit.h"

void exercicio_3() {


    TCanvas *c1 = new TCanvas("c1", "Ajuste J/ψ", 800, 600);
    TFile *file = new TFile("/Users/thiagorangel/UERJ/Introducao_Analise_de_Dados_FAE/data/DataSet_lowstat.root");
    TTree *tree = (TTree*)file->Get("data");

    // Definindo a variável da massa
    RooRealVar x("mass", "Massa (GeV/c^{2})", 2.5, 3.5);
    RooDataSet dataUnbinned("dataUnbinned", "Unbinned data", RooArgSet(x), RooFit::Import(*tree));
    std::cout << "Dados importados: " << std::endl;
    dataUnbinned.Print("v");

    // Definindo a função Crystal Ball
    RooRealVar mean("mean", "Média do sinal", 3.096916, 3.0, 3.2);
    RooRealVar sigma("sigma", "Largura do sinal", 0.1, 0.01, 0.5);
    RooRealVar alpha("alpha", "Alpha da Crystal Ball", 1.0, 0, 5);  
    RooRealVar n("n", "n da Crystal Ball", 2.0, 0, 5);              
    RooCrystalBall CB("CB", "Sinal JPsi", x, mean, sigma, alpha, n);

    // Definindo o background exponencial
    RooRealVar lambda("lambda", "Constante de decaimento", -1.0, -10.0, 0.0); 
    RooExponential exp("exp", "Background exponencial", x, lambda);

    // Combinando os modelos de sinal e background
    RooRealVar frac("frac", "Frações do sinal", 0.5, 0.0, 1.0);
    RooAddPdf model("model", "Modelo Sinal + Background", RooArgList(CB, exp), RooArgList(frac));

    // Ajustando o modelo aos dados
    model.fitTo(dataUnbinned);

    // Plotando os resultados
    RooPlot* frame = x.frame();
    dataUnbinned.plotOn(frame, RooFit::MarkerColor(kBlue), RooFit::Name("Dados"));
    model.plotOn(frame, RooFit::LineColor(kRed), RooFit::Name("Ajuste do Modelo"));
    model.plotOn(frame, RooFit::Components("CB"), RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen), RooFit::Name("Crystal Ball"));
    model.plotOn(frame, RooFit::Components("exp"), RooFit::LineStyle(kDotted), RooFit::LineColor(kMagenta), RooFit::Name("Exponencial"));

    // Adicionando a legenda
    TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);  
    legend->AddEntry(frame->findObject("Dados"), "Dados", "p");
    legend->AddEntry(frame->findObject("Ajuste do Modelo"), "Modelo (Crystal Ball + Exponencial)", "l");
    legend->AddEntry(frame->findObject("CB"), "Crystal Ball", "l");
    legend->AddEntry(frame->findObject("exp"), "Exponencial", "l");
    legend->SetBorderSize(1); 
    legend->Draw();

    c1->Update();
    c1->SaveAs("ImportarDadosFitModel.png");
    file->Close();

    
}
