void example_1()
{
    TFile *file = new TFile("DataSkim4.root");
    TTree *oniaTree = (TTree*)file->Get("oniaTree");
    
    TCanvas *c1 = new TCanvas();
    oniaTree->Draw("dimuon_p4.M()");
    c1->Draw();
    c1->SaveAs("dimuon_p4.png");

    TCanvas *c2 = new TCanvas();
    oniaTree->Draw("dimuon_p4.Eta()");
    c2->Draw();
    c2->SaveAs("dimuon_eta.png");
}