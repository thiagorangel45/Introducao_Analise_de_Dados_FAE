void exercicio_3() {

    TCanvas *c1 = new TCanvas("c1", "Canvas", 800, 600);
    TH1F *hist = new TH1F("hist", "", 50, 0, 10);
    TRandom3 *rand = new TRandom3();

    for (int i = 0; i < 10000; ++i) {
        double value = rand->Gaus(5, 2); 
        hist->Fill(value);
    }

    hist->Draw();
    hist->SetStats(0);
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); 
    legend->SetHeader("Estatistica", "C"); 

    legend->AddEntry((TObject*)0, Form("Entries: %d", (int)hist->GetEntries()), "");
    legend->AddEntry((TObject*)0, Form("Mean: %.2f", hist->GetMean()), "");
    legend->AddEntry((TObject*)0, Form("RMS: %.2f", hist->GetRMS()), "");
    legend->AddEntry((TObject*)0, Form("Integral: %.2f", hist->Integral()), "");
    legend->AddEntry((TObject*)0, Form("Underflows: %d", (int)hist->GetBinContent(0)), "");
    legend->AddEntry((TObject*)0, Form("Overflows: %d", (int)hist->GetBinContent(hist->GetNbinsX() + 1)), "");
    legend->AddEntry((TObject*)0, Form("Skewness: %.2f", hist->GetSkewness()), "");
    legend->AddEntry((TObject*)0, Form("Kurtosis: %.2f", hist->GetKurtosis()), "");
    legend->Draw();

    c1->SaveAs("histogram_estatistica.png");
}
