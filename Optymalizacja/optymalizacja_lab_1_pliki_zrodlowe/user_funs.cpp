#include"user_funs.h"
#include"ode_solver.h"
#include <math.h>

const double PI = 3.14;

matrix ff(matrix x, matrix ud1, matrix ud2){
    matrix y;
    y = -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * M_PI,2)) + 0.002 * pow(0.1 * x(),2);
    return y;
}

matrix df(double t, matrix y, matrix ud1, matrix ud2){
    double a = 0.98, b = 0.63, g = 9.81, PA = 0.75, TA = 90.0, PB = 1.0, DB = 0.00365665, Fin = 0.01, Tin = 10.0;

    matrix dY(3, 1);
    double FAout = a * b * m2d(ud2) * sqrt(2 * g * y(0) / PA);
    double FBout = a * b * DB * sqrt(2 * g * y(1) / PB);
    dY(0) = -FAout;
    dY(1) = FAout + Fin - FBout;
    dY(2) = ( Fin / y(1) ) * (Tin - y(2)) + ( FAout / y(1) ) * (TA - y(2));

    return dY;
}

matrix fR(matrix x, matrix ud1, matrix ud2){
    double y;
    matrix Y0 = matrix(3, new double[3]{ 5,1,10 });
    matrix* Y = solve_ode(df, 0, 1, 1000, Y0, ud1, x);
    int n = get_len(Y[0]);
    double max = Y[1](0, 2);
    for (int i = 0; i < n; i++)
        if (max < Y[1](i, 2)) max = Y[1](i, 2);
    y = abs(max - 50);
    return y;
}

matrix ff2(matrix x, matrix ud1, matrix ud2){
    matrix y;
    y = pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * PI * x(0)) - cos(2.5 * PI * x(1)) + 2;
    return y;
}

matrix df2(double t, matrix y, matrix ud1, matrix ud2) {
    double mr = 1, mc = 9, l = 0.5, b = 0.5;
    double I = mr * l * l / 3.0 + mc * l * l;
    matrix dY(2,1);
    dY(0) = y(1);
    dY(1) = (ud2(0) * (ud1(0) - y(0)) + ud2(1)*(ud1(1) - y(1)) - b * y(1) ) / I;
    return dY;
}

matrix fT2(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    matrix y0(2,1), y_ref(2, new double[2]{PI,0});
    matrix* Y = solve_ode(df2, 0, 0.1, 100, y0, y_ref, x);
    y = 0;
    int n = get_len(Y[0]);
    for (int i = 0;i<n;i++) {
        y = y + 10 * pow(y_ref(0)-Y[1](i,0), 2)
            + pow(y_ref(1) - Y[1](i,1), 2)
            + pow(x(0) * (y_ref(0) - Y[1](i,0)) + x(1) * (y_ref(1) - Y[1](i,1)), 2);
    }
    y = y * 0.1;
    return y;
}

matrix fT3A(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    double arg = PI * sqrt(pow(x(0) / PI, 2) + pow(x(1) / PI, 2));
    y = sin(arg) / arg;
    if (-x(0) + 1 > 0) y = y + ud2 * pow(-x(0) + 1, 2);
    if (-x(1) + 1 > 0) y = y + ud2 * pow(-x(1) + 1, 2);
    if (norm(x) - ud1 > 0) y = y + ud2 * pow(norm(x) - ud1, 2);
    return y;
}

matrix fT3B(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    double arg = PI * sqrt(pow(x(0) / PI, 2) + pow(x(1) / PI, 2));
    y = sin(arg) / arg;
    if (-x(0) + 1 > 0) y = 10e10;
    else y = y - ud2 / (-x(0) - 1);
    if (-x(1) + 1 > 0) y = 10e10;
    else y = y - ud2 / (-x(1) - 1);
    if (norm(x) - ud1 > 0) y = 10e10;
    else y = y - ud2 / (norm(x) - ud1);
    return y;
}

matrix df3(double t, matrix x, matrix ud1, matrix ud2) {
    cout << t << ";" << x(0) << ";" << x(2) << endl;
    double c = 0.47, r = 0.12, m = 0.6, v0y = 0, g = 9.81;
    double s = PI * r * r;
    double dx = 0.5 * c * v0y * s * abs(x(1)) * x(1);
    double dy = 0.5 * c * v0y * s * abs(x(3)) * x(3);
    double fmx = PI * v0y * x(3) * ud2() * pow(r, 3);
    double fmy = PI * v0y * x(1) * ud2() * pow(r, 3);
    matrix dY(4, 1);
    dY(0) = x(1);
    dY(1) = (-dx - fmx) / m;
    dY(2) = x(3);
    dY(3) = (-g - dy - fmy) / m;
    return dY;
}

matrix fr3(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    matrix y0(4, new double[4]{0, x(0), 100, 0});
    matrix* yB = solve_ode(df3, 0, 0.01, 7, y0, ud1, x(1));
    int n = get_len(yB[0]);
    int i50 = 0;
    int i0 = 0;
    for (int i = 0; i<n; i++) {
        if (abs(yB[1](i, 2) - 50) < abs(yB[1](i50, 2 ) - 50)) i50 = i;
        if (abs(yB[1](i, 2)) < abs(yB[1](i0, 2 ))) i0 = i;
    }
    y = -yB[1](i0, 0);
    if (abs(x(0)) - 10 > 0) y = y + ud2 * pow(abs(x(0)) - 10, 2);
    if (abs(x(1)) - 25 > 0) y = y + ud2 * pow(abs(x(1)) - 25, 2);
    if (abs(yB[1](i50, 0) - 5) - 1 > 0) y = y + ud2 * pow((yB[1](i50, 0) - 5) - 1, 2);
    return y;
}

matrix ff4T(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    y = pow(x(0) + 2 * x(1) - 7, 2) + pow(2 * x(0) + x(1) - 5, 2);
    return y;
}

matrix gf4T(matrix x, matrix ud1, matrix ud2) {
    matrix g(2, 1);
    g(0) = 10 * x(0) + 8 * x(1) - 34;
    g(1) = 8 * x(0) + 10 * x(1) - 38;
    return g;
}

matrix Hf4T(matrix x, matrix ud1, matrix ud2) {
    matrix H(2, 2);
    H(0, 0) = H(1, 1) = 10;
    H(0, 1) = H(1, 0) = 8;
    return H;
}

matrix ff4R(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    int m = 100;
    int n = get_len(x);
    static matrix X(n, m), Y(1, m);
    static bool read = true;
    if (read) {
        ifstream S("XData.txt");
        S >> X;
        S.close();
        S.open("YData.txt");
        S >> Y;
        S.close();
        read = false;
    }
    double h;
    y = 0;
    for (int i = 0; i < m; i++) {
        h = (trans(x) * X[i])();
        h = 1.0 / (1.0 + exp(-h));
        y = y - Y(0, i) * log(h) - (1 - Y(0, i)) * log(1 - h);
    }
    y = y / m;
    return y;
}

matrix gf4R(matrix x, matrix ud1, matrix ud2) {
    int m = 100;
    int n = get_len(x);
    matrix g(n, 1);
    static matrix X(n, m), Y(1, m);
    static bool read = true;
    if (read) {
        ifstream S("XData.txt");
        S >> X;
        S.close();
        S.open("YData.txt");
        S >> Y;
        S.close();
        read = false;
    }
    double h;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            h = (trans(x) * X[j])();
            h = 1.0 / (1.0 + exp(-h));
            g(i) = g(i) + X(i, j) * (h - Y(0, j));
        }
        g(i) = g(i) / m;
    }
    return g;
}
