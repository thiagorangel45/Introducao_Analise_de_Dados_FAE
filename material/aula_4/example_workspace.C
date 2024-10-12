void example_workspace()
{
    RooRealVar mass("mass", "mass", 5.20, 5.30);
    RooRealVar mean("mean", "mean", 5.28, 5.20, 5.30);
    RooRealVar sigma("sigma", "sigma", 0.005, 0.001, 0.05);
    RooGaussian model("model", "model", mass, mean, sigma);

    RooWorkspace w("w");
    w.import(model);

    RooDataSet *data = w.pdf("model")->generate(*w.var("mass"), 1000);
    w.pdf("model")->fitTo(*data);

    RooPlot *frame = w.var("mass")->frame();
    TCanvas *c1 = new TCanvas();
    data->plotOn(frame);
    w.pdf("model")->plotOn(frame);
    frame->Draw();
    c1->Draw();
    c1->SaveAs("w.png");
    w.writeToFile("wspacepp.root");
}