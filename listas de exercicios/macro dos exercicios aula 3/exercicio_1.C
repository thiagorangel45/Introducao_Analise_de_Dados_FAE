void exercicio_1(){

    TCanvas *c1 = new TCanvas();
    TF1 *f1 = new TF1("funcao", "([0]*sin([1]*x))/x", 0, 10);
    f1->SetTitle("");
    f1->SetParameters(1, 2);

    // Calculo de f(1)
    double valor_em_1 = f1->Eval(1);
    std::cout << "Valor da funcao em x=1: " << valor_em_1 << std::endl;

    // Calculo da derivada em x=1
    double derivada_em_1 = f1->Derivative(1);
    std::cout << "Derivada da funcao em x=1: " << derivada_em_1 << std::endl;

    // Calculo da integral entre 0 e 3
    double valor_integral = f1->Integral(0, 3);
    std::cout << "Integral da funcao entre 0 e 3: " << valor_integral << std::endl;

    f1->Draw();
    c1->Draw();
    c1->SaveAs("exercicio_1.png");
}