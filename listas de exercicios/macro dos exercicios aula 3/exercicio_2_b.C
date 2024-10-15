void exercicio_2_b() {

    TCanvas *c1 = new TCanvas("c1", "Canvas Title", 800, 600);
    TGraphErrors *gr_err = new TGraphErrors();

    std::ifstream file("/Users/thiagorangel/UERJ/Introducao_Analise_de_Dados_FAE/data/graphdata_error.txt");

    double x, y, ex, ey;

    while (1) {
        file >> x >> y >> ex >> ey;
        gr_err->SetPoint(gr_err->GetN(), x, y);  
        gr_err->SetPointError(gr_err->GetN()-1, ex, ey);  
        if (file.eof()){break;}
        
    }

    gr_err->SetMarkerStyle(21);  
    gr_err->SetMarkerSize(1.5);  
    gr_err->SetMarkerColor(kBlack);  

    gr_err->Draw("APL");  
    c1->SaveAs("graph_2_errors.png");
}
