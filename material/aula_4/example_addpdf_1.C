void example_addpdf_1()
{
    TFile *file = new TFile("/opendata/example_data.root", "READ");
    TTree *tree = (TTree*)file->Get("nt");
    TCanvas *c1 = new TCanvas();

    RooRealVar x("mass", "mass", 0, 2);
    RooDataSet dataUnbinned("dataUnbinned", "Unbinned Data", RooArgSet(x), RooFit::Import(*tree));
    RooRealVar mean("mean", "mean", 1.0, 0.9, 1.1);
    RooRealVar sigma("sigma", "sigma", 0.1, 0.01, 0.2);
    RooGaussian gaus("gaus", "gauss", x, mean, sigma);

    RooRealVar expParm("expParm", "expParm", -1.0, -5.0, 0.0);
    RooExponential exp("exp", "exponential", x, expParm);

    RooRealVar frac("frac", "fraction of gaussian", 0.5, 0.0, 1.0);
    RooAddPdf model("model", "gauss+exp", RooArgList(gaus, exp), RooArgList(frac));
    model.fitTo(dataUnbinned);

    RooPlot *frame = x.frame();

    dataUnbinned.plotOn(frame, RooFit::MarkerColor(kBlue), RooFit::Name("Unbinned"));
    model.plotOn(frame, RooFit::MarkerColor(kRed), RooFit::Name("Model Fit"));
    model.plotOn(frame, RooFit::Components("gaus"), RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen),RooFit::Name("Gaussian"));
    model.plotOn(frame, RooFit::Components("exp"), RooFit::LineStyle(kDotted), RooFit::LineColor(kMagenta),RooFit::Name("Exponential"));
    frame->Print();
    frame->Draw();

    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->AddEntry(frame->FindObject("Unbinned"), "Data", "p");
    leg->AddEntry(frame->FindObject("Model Fit"), "Model (Gaussian + exponential)", "l");
    leg->AddEntry(frame->FindObject("gaus"), "Gaussian component", "l");

    leg->SetBorderSize(1);
    leg->Draw();
    c1->Update();
    c1->SaveAs("Importar_dados_fit_model.png");
    file->Close();

}