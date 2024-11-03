#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <RooRealVar.h>
#include <RooDataHist.h>
#include <RooFit.h>
#include <RooCrystalBall.h>
#include <RooPlot.h>
#include <RooAddPdf.h>
#include <RooPolynomial.h>
#include <TLegend.h>
#include <TLatex.h> // Adicionado para usar TLatex
#include <iostream>
#include <vector>
#include <algorithm>

void exercicio_1() {
    std::vector<std::string> diretorios = {
        "/opendata/eos/opendata/cms/Run2016G/DoubleEG/NANOAOD/UL2016_MiniAODv2_NanoAODv9-v1/100000/*.root",
        "/opendata/eos/opendata/cms/Run2016G/DoubleEG/NANOAOD/UL2016_MiniAODv2_NanoAODv9-v1/1010000/*.root",
        "/opendata/eos/opendata/cms/Run2016G/DoubleEG/NANOAOD/UL2016_MiniAODv2_NanoAODv9-v1/250000/*.root"
    };

    TChain chain("Events");
    for (const auto& path : diretorios) {
        chain.Add(path.c_str());
    }

    TTreeReader reader(&chain);
    TTreeReaderArray<float> Electron_pt(reader, "Electron_pt");
    TTreeReaderArray<float> Electron_eta(reader, "Electron_eta");
    TTreeReaderArray<float> Electron_phi(reader, "Electron_phi");

    TH1F* hInvariantMassElectron = new TH1F("hInvariantMassElectron", "Massa Invariante dos Dois Eletrons de Maior p_{T}; m_{ll} (GeV/c^{2}); Eventos", 100, 80, 100);
    TCanvas *c2 = new TCanvas("c2", "Ajuste com Crystal Ball e Background Linear", 800, 600);

    int eventos_analisados = 0;
    while (reader.Next()) {
        eventos_analisados++;
        if (eventos_analisados % 10000 == 0) {
            std::cout << "Eventos analisados: " << eventos_analisados << std::endl;
        }

        if (Electron_pt.GetSize() >= 2) {
            std::vector<TLorentzVector> electrons;
            for (int i = 0; i < Electron_pt.GetSize(); ++i) {
                if (Electron_pt[i] > 20.0 && fabs(Electron_eta[i]) < 2.4) {
                    TLorentzVector electron;
                    electron.SetPtEtaPhiM(Electron_pt[i], Electron_eta[i], Electron_phi[i], 0.000511);
                    electrons.push_back(electron);
                }
            }
            std::sort(electrons.begin(), electrons.end(), [](const TLorentzVector& a, const TLorentzVector& b) {
                return a.Pt() > b.Pt();
            });

            if (electrons.size() >= 2) {
                TLorentzVector invMassElectron = electrons[0] + electrons[1];
                hInvariantMassElectron->Fill(invMassElectron.M());
            }
        }
    }

    // RooFit:
    RooRealVar mass("mass", "m_{e^{+}e^{-}} (GeV/c^{2})", 80, 100);
    RooDataHist dataHist("dataHist", "Dataset a partir do histograma", mass, RooFit::Import(*hInvariantMassElectron));

    RooRealVar mean("mean", "Média", 90.5, 80, 100);
    RooRealVar sigma("sigma", "Desvio padrão", 1.5, 0.5, 10);
    RooRealVar alpha("alpha", "Alpha", 1.5, 0, 5);
    RooRealVar n("n", "n", 1, 0.1, 10);
    RooCrystalBall crystalBall("crystalBall", "Função de Crystal Ball", mass, mean, sigma, alpha, n);

    RooRealVar a0("a0", "Coeficiente linear", 0, -10, 10);
    RooPolynomial background("background", "Fundo Linear", mass, RooArgList(a0));

    RooRealVar nsig("nsig", "Número de eventos de sinal", 500, 0, 10000);
    RooRealVar nbkg("nbkg", "Número de eventos de background", 200, 0, 5000);
    RooAddPdf model("model", "Modelo Combinado", RooArgList(crystalBall, background), RooArgList(nsig, nbkg));

    model.fitTo(dataHist);

    double meanVal = mean.getVal();
    double meanErr = mean.getError();
    double sigmaVal = sigma.getVal();
    double sigmaErr = sigma.getError();

    RooPlot* frame = mass.frame();
    dataHist.plotOn(frame);
    model.plotOn(frame, RooFit::LineColor(kBlue)); 
    model.plotOn(frame, RooFit::Components("background"), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
    model.plotOn(frame, RooFit::Components("crystalBall"), RooFit::LineColor(kGreen));
    frame->SetTitle("");
    frame->Draw();
    
    TLegend* legend = new TLegend(0.7, 0.6, 0.9, 0.9); 
    legend->SetTextSize(0.03); 
    legend->AddEntry(frame->getObject(0), "Dados", "P"); 
    legend->AddEntry(frame->getObject(1), "Modelo Total", "L"); 
    legend->AddEntry(frame->getObject(2), "Fundo Linear", "L"); 
    legend->AddEntry(frame->getObject(3), "Crystal Ball", "L");
    
    // Adicionando as informações da média e sigma com TLatex
    TLatex* latex = new TLatex();
    latex->SetNDC(); // Define coordenadas normalizadas do canvas
    latex->SetTextSize(0.035); // Define o tamanho do texto
    latex->DrawLatex(0.12, 0.78, Form("Media = %.3f #pm %.3f GeV/c^{2}", meanVal, meanErr));
    latex->DrawLatex(0.12, 0.73, Form("Sigma = %.3f #pm %.3f GeV/c^{2}", sigmaVal, sigmaErr));
    
    legend->Draw("SAME");
    
    c2->Update(); // Força a atualização do canvas
    c2->SaveAs("ajuste_crystal_ball_background.png");
    c2->SaveAs("ajuste_crystal_ball_background.root");

    // Cleanup
    delete latex; // Limpeza do objeto TLatex
    delete c2;
    delete hInvariantMassElectron;
}
