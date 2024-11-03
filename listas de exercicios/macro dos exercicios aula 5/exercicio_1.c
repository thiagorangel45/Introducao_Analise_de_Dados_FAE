#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

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

    // Elétrons
    TTreeReader reader(&chain);
    TTreeReaderArray<float> Electron_pt(reader, "Electron_pt");
    TTreeReaderArray<float> Electron_eta(reader, "Electron_eta");
    TTreeReaderArray<float> Electron_phi(reader, "Electron_phi");

    // Múons 
    TTreeReaderArray<float> Muon_pt(reader, "Muon_pt");
    TTreeReaderArray<float> Muon_eta(reader, "Muon_eta");
    TTreeReaderArray<float> Muon_phi(reader, "Muon_phi");

    // Taus
    TTreeReaderArray<float> Tau_pt(reader, "Tau_pt");
    TTreeReaderArray<float> Tau_eta(reader, "Tau_eta");
    TTreeReaderArray<float> Tau_phi(reader, "Tau_phi");

    // Jatos
    TTreeReaderArray<float> Jet_pt(reader, "Jet_pt");
    TTreeReaderArray<float> Jet_eta(reader, "Jet_eta");
    TTreeReaderArray<float> Jet_phi(reader, "Jet_phi");

    // Criando histogramas
    TH1F* hElectronPt = new TH1F("hElectronPt", "Distribuicao de p_{T} dos Eletrons; p_{T} (GeV/c); Eventos", 50, 0, 200);
    TH1F* hElectronEta = new TH1F("hElectronEta", "Distribuicao de #eta dos Eletrons; #eta; Eventos", 50, -3, 3);
    TH1F* hElectronPhi = new TH1F("hElectronPhi", "Distribuicao de #phi dos Eletrons; #phi; Eventos", 50, -TMath::Pi(), TMath::Pi());
    
    TH1F* hMuonPt = new TH1F("hMuonPt", "Distribuicao de p_{T} dos Muons; p_{T} (GeV/c); Eventos", 50, 0, 200);
    TH1F* hMuonEta = new TH1F("hMuonEta", "Distribuicao de #eta dos Muons; #eta; Eventos", 50, -3, 3);
    TH1F* hMuonPhi = new TH1F("hMuonPhi", "Distribuicao de #phi dos Muons; #phi; Eventos", 50, -TMath::Pi(), TMath::Pi());
    
    TH1F* hTauPt = new TH1F("hTauPt", "Distribuicao de p_{T} dos Taus; p_{T} (GeV/c); Eventos", 50, 0, 200);
    TH1F* hTauEta = new TH1F("hTauEta", "Distribuicao de #eta dos Taus; #eta; Eventos", 50, -3, 3);
    TH1F* hTauPhi = new TH1F("hTauPhi", "Distribuicao de #phi dos Taus; #phi; Eventos", 50, -TMath::Pi(), TMath::Pi());
    
    TH1F* hJetPt = new TH1F("hJetPt", "Distribuicao de p_{T} dos Jatos; p_{T} (GeV/c); Eventos", 50, 0, 200);
    TH1F* hJetEta = new TH1F("hJetEta", "Distribuicao de #eta dos Jatos; #eta; Eventos", 50, -3, 3);
    TH1F* hJetPhi = new TH1F("hJetPhi", "Distribuicao de #phi dos Jatos; #phi; Eventos", 50, -TMath::Pi(), TMath::Pi());
    
    TH1F* hInvariantMassMuon = new TH1F("hInvariantMassMuon", "Massa Invariante dos Dois Muons de Maior p_{T}; m_{ll} (GeV/c^{2}); Eventos", 50, 0, 200);
    TH1F* hInvariantMassTau = new TH1F("hInvariantMassTau", "Massa Invariante dos Dois Taus de Maior p_{T}; m_{ll} (GeV/c^{2}); Eventos", 50, 0, 200);
    TH1F* hInvariantMassElectron = new TH1F("hInvariantMassElectron", "Massa Invariante dos Dois Eletrons de Maior p_{T}; m_{ll} (GeV/c^{2}); Eventos", 50, 0, 200);

    int eventos_analisados = 0;

    while (reader.Next()) {
        eventos_analisados++;
        if (eventos_analisados % 10000 == 0) {
            std::cout << "Eventos analisados: " << eventos_analisados << std::endl;
        }

        // Preenchendo histogramas de elétrons
        for (int i = 0; i < Electron_pt.GetSize(); ++i) {
            hElectronPt->Fill(Electron_pt[i]);
            hElectronEta->Fill(Electron_eta[i]);
            hElectronPhi->Fill(Electron_phi[i]);
        }

        // Preenchendo histogramas de múons
        for (int i = 0; i < Muon_pt.GetSize(); ++i) {
            hMuonPt->Fill(Muon_pt[i]);
            hMuonEta->Fill(Muon_eta[i]);
            hMuonPhi->Fill(Muon_phi[i]);
        }

        // Preenchendo histogramas de taus
        for (int i = 0; i < Tau_pt.GetSize(); ++i) {
            hTauPt->Fill(Tau_pt[i]);
            hTauEta->Fill(Tau_eta[i]);
            hTauPhi->Fill(Tau_phi[i]);
        }

        // Preenchendo histogramas de jatos
        for (int i = 0; i < Jet_pt.GetSize(); ++i) {
            hJetPt->Fill(Jet_pt[i]);
            hJetEta->Fill(Jet_eta[i]);
            hJetPhi->Fill(Jet_phi[i]);
        }

        // Analisando massa invariante de elétrons
        if (Electron_pt.GetSize() >= 2) {
            std::vector<TLorentzVector> electrons;
            for (int i = 0; i < Electron_pt.GetSize(); ++i) {
                TLorentzVector electron;
                electron.SetPtEtaPhiM(Electron_pt[i], Electron_eta[i], Electron_phi[i], 0.000511); // Massa do elétron
                electrons.push_back(electron);
            }
            std::sort(electrons.begin(), electrons.end(), [](const TLorentzVector& a, const TLorentzVector& b) {
                return a.Pt() > b.Pt();
            });
            if (electrons.size() >= 2) {
                TLorentzVector invMassElectron = electrons[0] + electrons[1];
                hInvariantMassElectron->Fill(invMassElectron.M());
            }
        }

        // Analisando massa invariante de muons
        if (Muon_pt.GetSize() >= 2) {
            std::vector<TLorentzVector> muons;
            for (int i = 0; i < Muon_pt.GetSize(); ++i) {
                TLorentzVector muon;
                muon.SetPtEtaPhiM(Muon_pt[i], Muon_eta[i], Muon_phi[i], 0.105658); // Massa do múon
                muons.push_back(muon);
            }
            std::sort(muons.begin(), muons.end(), [](const TLorentzVector& a, const TLorentzVector& b) {
                return a.Pt() > b.Pt();
            });
            if (muons.size() >= 2) {
                TLorentzVector invMassMuon = muons[0] + muons[1];
                hInvariantMassMuon->Fill(invMassMuon.M());
            }
        }

        // Analisando massa invariante de taus
        if (Tau_pt.GetSize() >= 2) {
            std::vector<TLorentzVector> taus;
            for (int i = 0; i < Tau_pt.GetSize(); ++i) {
                TLorentzVector tau;
                tau.SetPtEtaPhiM(Tau_pt[i], Tau_eta[i], Tau_phi[i], 1.77682); // Massa do tau
                taus.push_back(tau);
            }
            std::sort(taus.begin(), taus.end(), [](const TLorentzVector& a, const TLorentzVector& b) {
                return a.Pt() > b.Pt();
            });
            if (taus.size() >= 2) {
                TLorentzVector invMassTau = taus[0] + taus[1];
                hInvariantMassTau->Fill(invMassTau.M());
            }
        }
    }

    // Criando canvas e plotando histogramas
    TCanvas *c1 = new TCanvas("c1", "Distribuições elétrons", 800, 600);
    c1->Divide(2, 2);
    c1->cd(1); hElectronPt->Draw();
    c1->cd(2); hElectronEta->Draw();
    c1->cd(3); hElectronPhi->Draw();
    c1->cd(4); hInvariantMassElectron->Draw();
    c1->SaveAs("distribuicoes_electron.png");
    delete c1;

    TCanvas *c2 = new TCanvas("c2", "Distribuições múons", 800, 600);
    c2->Divide(2, 2);
    c2->cd(1); hMuonPt->Draw();
    c2->cd(2); hMuonEta->Draw();
    c2->cd(3); hMuonPhi->Draw();
    c2->cd(4); hInvariantMassMuon->Draw();
    c2->SaveAs("distribuicoes_muons.png");
    delete c2;

    TCanvas *c3 = new TCanvas("c3", "Distribuições Taús", 800, 600);
    c3->Divide(2, 2);
    c3->cd(1); hTauPt->Draw();
    c3->cd(2); hTauEta->Draw();
    c3->cd(3); hTauPhi->Draw();
    c3->cd(4); hInvariantMassTau->Draw();
    c3->SaveAs("distribuicoes_tau.png");
    delete c3;

    TCanvas *c4 = new TCanvas("c4", "Distribuições Jatos", 800, 600);
    c4->Divide(2, 2);
    c4->cd(1); hJetPt->Draw();
    c4->cd(2); hJetEta->Draw();
    c4->cd(3); hJetPhi->Draw();
    c4->SaveAs("distribuicoes_jatos.png");
    delete c4;
    
    // Deletando histogramas após a plotagem
    delete hElectronPt;
    delete hElectronEta;
    delete hElectronPhi;
    delete hMuonPt;
    delete hMuonEta;
    delete hMuonPhi;
    delete hTauPt;
    delete hTauEta;
    delete hTauPhi;
    delete hJetPt;
    delete hJetEta;
    delete hJetPhi;
    delete hInvariantMassMuon;
    delete hInvariantMassTau;
    delete hInvariantMassElectron;
}
