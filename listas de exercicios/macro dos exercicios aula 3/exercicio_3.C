void exercicio_3() {

    TCanvas *c1 = new TCanvas(); 
    TGraphErrors *gr = new TGraphErrors(); 

    std::ifstream file("/Users/thiagorangel/UERJ/Introducao_Analise_de_Dados_FAE/data/graphdata_error.txt"); // Abre o arquivo

    double x, y, ex, ey;
    while (1) {
        file >> x >> y >> ex >> ey; 

        if (file.eof()) {break;}

        gr->SetPoint(gr->GetN(), x, y);
        gr->SetPointError(gr->GetN() - 1, ex, ey);
    }

    gr->SetMarkerSize(1);
    gr->SetMarkerStyle(21);
    gr->Draw("AP");
    c1->SaveAs("graph_error_1.png");

    gr->SetMarkerSize(1);
    gr->SetMarkerStyle(21);
    gr->Draw("AL"); 
    c1->Draw();
    c1->SaveAs("graph_error_2.png");

    file.close();
}
