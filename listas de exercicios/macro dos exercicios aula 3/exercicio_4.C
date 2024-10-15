void exercicio_4() {

    TCanvas *c1 = new TCanvas("c1", "Histograma de Momento", 800, 600);
    TFile *file = new TFile("/Users/thiagorangel/UERJ/Introducao_Analise_de_Dados_FAE/data/tree.root");
    TTree *tree = (TTree*)file->Get("tree1");
    
    TH1F *hist = new TH1F("hist", "Distribuição do Momento Total", 100, 0, 200);

    float px, py, pz, ebeam;
    tree->SetBranchAddress("ebeam", &ebeam);
    tree->SetBranchAddress("px", &px); 
    tree->SetBranchAddress("py", &py);
    tree->SetBranchAddress("pz", &pz);

    float sumEbeam = 0;
    Int_t nEntries = tree->GetEntries();

    for (Int_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        sumEbeam += ebeam;
    }
    
    float meanEbeam = sumEbeam / nEntries;  

    TCut *cutEbeam = new TCut(Form("ebeam < %f || ebeam > %f", meanEbeam - 0.2, meanEbeam + 0.2));
    tree->Draw("sqrt(px*px + py*py + pz*pz)", *cutEbeam);
    c1->SaveAs("histograma_momento.png");
}
