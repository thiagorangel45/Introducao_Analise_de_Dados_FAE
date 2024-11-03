void example_2()
{
    TFile *file = new TFile("DataSkim4.root");
    TTree *oniaTree = (TTree*)file->Get("oniaTree");

    TCanvas *c1 = new TCanvas();
    TH1F *hptz = new TH1F("hptz", "Distribuição Pt para M > 70", 500, 0, 100);
    TH1F *hptj = new TH1F("hptj", "Distribuição Pt para 3.0 < M < 3.2", 100, 0, 100);

    oniaTree->Draw("dimuon_p4.Pt()>>+hptz", "dimuon_p4.M() > 70");
    oniaTree->Draw("dimuon_p4.Pt()>>+hptj", "dimuon_p4.M() > 3.0 && dimuon_p4.M() < 3.2");

    hptz->SetLineColor(kRed);
    hptj->SetLineColor(kBlue);
    hptz->Draw("SAME");
    hptj->Draw("SAME");
    c1->SaveAs("distribuicoes_cinematicas.png");
}
