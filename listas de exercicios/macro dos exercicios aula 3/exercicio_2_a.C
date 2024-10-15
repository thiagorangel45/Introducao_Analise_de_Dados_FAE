void exercicio_2_a() {

    TCanvas *c1 = new TCanvas("c1", "Canvas Title", 800, 600);
    TGraph *gr = new TGraph();    

    std::ifstream file("/Users/thiagorangel/UERJ/Introducao_Analise_de_Dados_FAE/data/graphdata.txt"); 

    double x, y;
    while (1) {
        file >> x >> y;
        gr->SetPoint(gr->GetN(), x, y); 
        if (file.eof()){break;}
    }

    gr->SetMarkerStyle(21);  
    gr->SetMarkerSize(1.5);  
    gr->SetMarkerColor(kBlack);  

    gr->Draw("APL"); 
    c1->SaveAs("graph_2.png");
}