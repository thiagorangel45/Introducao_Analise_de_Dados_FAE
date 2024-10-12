void simple_histogram2D()
{
    TCanvas *c1 = new TCanvas();
    TH2F *hist2d = new TH2F("hist2d", "histogram title", 100, 0, 10, 100, 0, 10);

    for (int i = 0; i < 10000; i++)
    {
        double_t x = gRandom->Uniform(0, 10);
        double_t y = gRandom->Uniform(0, 10);

        hist2d->Fill(x, y);
    }
    
    hist2d->Draw();
    c1->Draw();
}