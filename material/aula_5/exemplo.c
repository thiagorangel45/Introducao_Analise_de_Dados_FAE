void exemplo()
{
    TCanvas *c1 = new TCanvas();
    TH1F *hist = new TH1F("hist", "", 100, 1, 100);

    TFile *file = new TFile("/opendata/eos/opendata/cms/Run2016G/DoubleEG/NANOAOD/UL2016_MiniAODv2_NanoAODv9-v1/100000/11DA657F-5262-BD4A-AD1E-8E53BE62A601.root", "READ");
    TTree *tree = (TTree*)file->Get("Events");
    tree->Draw("Muon_pt>>hist");
    
    hist->GetXaxis()->SetTitle("Muon_pt");
    hist->GetYaxis()->SetTitle("N_{entries}");
    c1->SetLogy();
    
    c1->Draw();
    c1->SaveAs("teste.png");
}