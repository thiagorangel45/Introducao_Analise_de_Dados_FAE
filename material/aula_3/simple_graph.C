void simple_graph()
{
    const Int_t Npoint = 10;
    double_t x[Npoint] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    double_t y[Npoint] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};


    TCanvas *c1 = new TCanvas();
    TGraph *gr = new TGraph(Npoint, x, y);

    gr->SetMarkerStyle(20);
    gr->SetMarkerColor(kBlue);
    gr->SetTitle("Exemplo de TGraph");
    gr->GetXaxis()->SetTitle("Eixo x");
    gr->GetYaxis()->SetTitle("Eixo y");

    gr->Draw("AP");
    c1->Draw();

}