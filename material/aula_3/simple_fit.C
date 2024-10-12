void simple_fit()
{
    TCanvas *c1 = new TCanvas();
    TRandom3 *rand = new TRandom3();
    TH1F *hist = new TH1F("hist", "histogram", 100, -5, 5);
    TF1 *fit = new TF1("fit", "gaus", -10, 10);

    for (int i = 0; i < 10000; i++)
    {
        double_t randomNumber = rand->Gaus(0, 1);
        hist->Fill(randomNumber);
    }
    
    hist->Draw();
    hist->Fit("fit");
    gStyle->SetOptFit(1111);
    c1->Draw();
}