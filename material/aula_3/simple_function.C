double_t minhaFuncao(double_t *x, double_t *par){return TMath::Sin(x[0])*TMath::Cos(x[0]);}

void simple_function()
{
    TCanvas *c1 = new TCanvas();
    TF1 *f1 = new TF1("f1", minhaFuncao, 0.0, 10.0, 0);
    TGraph *gr = new TGraph(f1);

    gr->SetTitle("exemplo de TF1");
    gr->GetXaxis()->SetTitle("eixo x");
    gr->GetYaxis()->SetTitle("eixo y");

    gr->Draw("AL");
    c1->Draw();
}