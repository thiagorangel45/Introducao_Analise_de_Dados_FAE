void simple_histogram()
{
    TH1F *hist = new TH1F("hist", "histogram", 100, 0, 10);
    TCanvas *c1 = new TCanvas();

    for (int i = 0; i < 10000; i++)
    {
        double random_number = gRandom->Uniform(0, 10);
        hist->Fill(random_number);
    }
    
    hist->Draw();
    c1->Draw("histograma.png");

}