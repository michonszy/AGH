/*********************************************
Kod stanowi uzupe�nienie materia��w do �wicze�
w ramach przedmiotu metody optymalizacji.
Kod udost�pniony na licencji CC BY-SA 3.0
Autor: dr in�. �ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia G�rniczo-Hutnicza
*********************************************/

#include"opt_alg.h"
#include"user_funs.h"

void lab1();

void lab2();

void lab3();

void lab4();

void lab5();

using namespace std;

int main() {
    try {
        // lab1();
        // lab2();
        //lab3();
        lab4();
    }
    catch (string EX_INFO) {
        cerr << "ERROR:\n";
        cerr << EX_INFO << endl << endl;
    }
    system("pause");
    return 0;
}

void lab1() {
    cout << "Metoda ekspansji" << endl;
    double x0;
    double d, alpha;
    int Nmax;
    double *p;

    x0 = 100;
    d = 1, alpha = 1.1;
    Nmax = 1000;
    p = expansion(ff, x0, d, alpha, Nmax, NULL, NULL);
    cout << "wynik: [" << p[0] << " ; " << p[1] << "]" << endl;

    x0 = 100;
    d = 1, alpha = 1.5;
    Nmax = 1000;
    p = expansion(ff, x0, d, alpha, Nmax, NULL, NULL);
    cout << "wynik: [" << p[0] << " ; " << p[1] << "]" << endl;

    x0 = -100;
    d = 1, alpha = 1.5;
    Nmax = 1000;
    p = expansion(ff, x0, d, alpha, Nmax, NULL, NULL);
    cout << "wynik: [" << p[0] << " ; " << p[1] << "]" << endl;

    solution::clear_calls();

    x0 = -100;
    d = 1, alpha = 2.5;
    Nmax = 1000;
    p = expansion(ff, x0, d, alpha, Nmax, NULL, NULL);
    cout << "wynik: [" << p[0] << " ; " << p[1] << "]" << endl;

    solution::clear_calls();

    x0 = -10;
    d = 1, alpha = 2.5;
    Nmax = 1000;
    p = expansion(ff, x0, d, alpha, Nmax, NULL, NULL);
    cout << "wynik: [" << p[0] << " ; " << p[1] << "]" << endl;

    solution::clear_calls();

    x0 = 10;
    d = 1, alpha = 2.5;
    Nmax = 1000;
    p = expansion(ff, x0, d, alpha, Nmax, NULL, NULL);
    cout << "wynik: [" << p[0] << " ; " << p[1] << "]" << endl;

    solution::clear_calls();

    cout << "Metoda Fibonacziego" << endl;
    double epsilon = 1e-10;
    double gamma = 1e-200;
    Nmax = 1000;

    cout << fib(fR, 1e-4, 1e-2, epsilon) << endl;

    solution::clear_calls();

    epsilon = 1e-7;
    cout << fib(fR, 1e-4, 1e-2, epsilon) << endl;

    solution::clear_calls();

}

void lab2() {
    solution::clear_calls();

    double s = 0.5, alphaHJ = 0.5, epsilon = 1e-3;
    int Nmax = 1000;
    solution opt;
    matrix x0;

//    x0 = 2.0 * rand_mat(2, 1) - 1.0;
//    cout << "x0: " << x0 << endl << endl;
//    opt = HJ(ff2, x0, s, alphaHJ, epsilon, Nmax);
//    cout << opt << endl << endl;
//    solution::clear_calls();

    //Ramie robota
    s = 2;
    x0 = 10.0 * rand_mat(2, 1);
    cout << x0 << endl << endl;
    opt = HJ(fT2, x0, s, alphaHJ, epsilon, Nmax);
    cout << opt << endl << endl;
    solution::clear_calls();

}

void lab3() {
    //Funkcja testowa
    matrix x0, a(4);
    double c_ex = 1, c_in = 10, dc_ex = 2, dc_in = 0.5, epsilon = 1e-3;
    int Nmax = 10000;
    solution opt, opt1;
    /*do x0 = 5 * rand_mat(2, 1) + 1;
    while (norm(x0) > a);*/



    cout << x0 << endl;
    //// Problem testowy zewnetrzny
//    opt = pen(fT3A, x0, c_ex, dc_ex, epsilon, Nmax, a);

    //// Problem testowy wewnetrzny
//    opt = pen(fT3B, x0, c_ex, dc_ex, epsilon, Nmax, a);

    //// Problem rzeczywisty
    x0 = matrix(2, new double[2]{2.45783, 2.87194});
    opt = pen(fr3, x0, c_in, dc_in, epsilon, Nmax, a);

    cout << opt << endl;
}

void lab4() {
    double epsilon = 1e-3, h = 0.05;
    //cout << h << endl << endl;
    int Nmax = 5000;
    matrix ud1, ud2;
    matrix x0 = 20 * rand_mat(2, 1) - 10;
    cout << x0 << endl << endl;
    solution opt;
    //// Problem testowy
    /*opt = SD(ff4T, gf4T, x0, h, epsilon, Nmax, ud1, ud2);
    cout << opt << endl << endl;
    solution::clear_calls();
    opt = CG(ff4T, gf4T, x0, h, epsilon, Nmax);
    cout << opt << endl << endl;
    solution::clear_calls();
    opt = Newton(ff4T, gf4T, Hf4T, x0, h, epsilon, Nmax);
    cout << opt << endl << endl;
    solution::clear_calls();*/
    //// Problem rzeczywisty
    epsilon = 0.001; h = 0.0001;
    Nmax = 20000;
    x0 = matrix(3, 1, 0.0);
    opt = CG(ff4R, gf4R, x0, h, epsilon, Nmax);
    cout << opt.x(0) << ";" << opt.x(1) << ";" << opt.x(2) << ";" << opt.y << ";" << opt.g_calls << endl;
}

void lab5() {

}

