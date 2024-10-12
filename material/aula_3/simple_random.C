void simple_random()
{
    TRandom *rand = new TRandom();
    TH1F *hist = new TH1F("hist", "histogram", 100, 0, 10);
    TCanvas *c1 = new TCanvas();

    for (int i = 0; i < 10000; i++)
    {
        double_t randomNumber = rand->Uniform(0, 10);
        hist->Fill(randomNumber);
    }
    
    hist->Draw();
    c1->Draw();
}