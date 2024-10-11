void exercicio_2() {
    TCanvas *c1 = new TCanvas(); 
    TGraph *gr = new TGraph();    

    std::ifstream file("/Users/thiagorangel/UERJ/Introducao_Analise_de_Dados_FAE/data/graphdata.txt"); // Abre o arquivo

    double x, y;

    while (1) { 
        file >> x >> y; 

        if (file.eof()) {break;}

        gr->SetPoint(gr->GetN(), x, y); 
    }

    gr->SetMarkerSize(10);
    gr->SetMarkerStyle(1);
    gr->Draw("AP"); 
    c1->Draw();
    c1->SaveAs("graph_1.png");

    gr->SetMarkerSize(10);
    gr->SetMarkerStyle(1);
    gr->Draw("AL"); 
    c1->Draw();
    c1->SaveAs("graph_2.png");
}
