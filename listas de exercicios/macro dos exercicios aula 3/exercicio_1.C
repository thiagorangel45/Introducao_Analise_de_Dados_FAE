void exercicio_1(){

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->SetTicks(1,1);
    TF1 *f1 = new TF1("f1", "([0]*sin([1]*x))/x", 0, 10); 
    TF1 *f2 = new TF1("f2", "([0]*sin([1]*x))/x", 0, 10);

    f1->SetTitle("");
    f1->SetParameters(1, 2);
    f1->SetLineColor(kBlue);

    f2->SetTitle("");
    f2->SetParameters(2,3);
    f2->SetLineColor(kRed);

    double valor_em_1 = f1->Eval(1);
    std::cout << "Valor da funcao em x=1: " << valor_em_1 << std::endl;

    double derivada_em_1 = f1->Derivative(1);
    std::cout << "Derivada da funcao em x=1: " << derivada_em_1 << std::endl;

    double valor_integral = f1->Integral(0, 3);
    std::cout << "Integral da funcao entre 0 e 3: " << valor_integral << std::endl;

    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->AddEntry(f1, "f1: (1*sin(2*x))/x", "l");
    leg->AddEntry(f2, "f2: (2*sin(3*x))/x", "l");

    f2->Draw();
    f1->Draw("SAME");
    leg->Draw();
    c1->SaveAs("exercicio_1.png");
}
