#include"opt_alg.h"
matrix f(double x, matrix(*ff)(matrix, matrix, matrix), matrix ud1 = NULL, matrix ud2 = NULL) {
    solution X(x);
    matrix fg = X.fit_fun(ff, ud1, ud2);
    return fg;
}

static int* F_A = new int[5000]{};

double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        double* p = new double[2]{ 0, 0 };
        //Tu wpisz kod funkcji
        double i = 0;
        double x1 = x0 + d;
        if (f(x1, ff) == f(x0, ff)) {
            p[0] = x0;
            p[1] = x1;
            return p;
        }
        if (f(x1, ff) > f(x0, ff)) {
            d = -d;
            x1 = x0 + d;
            if (f(x1, ff) >= f(x0, ff)) {
                p[0] = x1;
                p[1] = x0 - d;
                return p;
            }
        }

        double xim1 = x0;
        double xi = x0;
        double xip1 = x0;

        do {
            if (i > Nmax) {
                throw ("Too many iterations");
            }
            i = i + 1;
            xim1 = xi; //poprzedni to bedzie obecny
            xi = xip1; // obecny to bedzie poprzedni powiekszony
            xip1 = x0 + pow(alpha, i) * d; //zmiane robimy jedynie w kroku naprzod
        } while (f(xi, ff) >= f(xip1, ff));

        if (d > 0) {
            p[0] = xim1;
            p[1] = xip1;
            return p;
        }

        p[0] = xip1;
        p[1] = xim1;
        return p;
    }
    catch (string ex_info)
    {
        throw ("double* expansion(...):\n" + ex_info);
    }
}

int fibo(int n) {
    if (F_A[n] != 0 ) return F_A[n];
    if (n == 0) return 0;
    if (n == 1 ) {
        F_A[n] = 1;
        return F_A[n];
    }
    F_A[n] = fibo(n-1) + fibo(n-2);
    return F_A[n];
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{

    try
    {
        solution Xopt;
        int k = 3;

        while (true) {
            int temp = fibo(k);
            if (temp * 1.0 > (b - a ) / epsilon) {
                break;
            }
            k++;
        }

        solution AI(a), BI(b), C, D;
        C.x = BI.x - 1.0 * F_A[k-1] / F_A[k] * (BI.x - AI.x);
        D.x = AI.x + BI.x - C.x;

        for (int i = 0;i<=k-3;i++) {
            if (C.fit_fun(ff, ud1, ud2) < D.fit_fun(ff, ud1, ud2)) {
                BI = D;
            } else {
                AI = C;
            }

            /**
             *
             * Maciej Lisowski
             * Below you have to divide the [k-i-1]th Fibonacci number
             * by [k-i] th number
             * Instructions provided are wrong.
             *
             */

            C.x = BI.x - 1.0 * F_A[k-i-1] / F_A[k-i] * (BI.x - AI.x);
            D.x = AI.x + BI.x - C.x;
        }

        C.fit_fun(ff, ud1, ud2);
        D.fit_fun(ff, ud1, ud2);

        Xopt = C;
        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution fib(...):\n" + ex_info);
    }

}

solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        //Tu wpisz kod funkcji

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution lag(...):\n" + ex_info);
    }
}

solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution xopt(x0), xoptPrev, x;
        xopt.fit_fun(ff, ud1, ud2);
        do {

            x = HJ_trial(ff, xopt, s);

            if (x.y < xopt.y) {
                do {
                    xoptPrev = xopt;
                    xopt = x;
                    x.x = 2.0 * xopt.x - xoptPrev.x;
                    x.fit_fun(ff, ud1, ud2);
                    x = HJ_trial(ff, x, s);
                    if (solution::f_calls > Nmax) throw ("Too many iterations");
                } while (x.fit_fun(ff, ud1, ud2) < xopt.fit_fun(ff, ud1, ud2));
            } else {
                s *= alpha;
            }

            if (solution::f_calls > Nmax) throw ("Too many iterations");

        } while (s >= epsilon);

        return xopt;
    }
    catch (string ex_info)
    {
        throw ("solution HJ(...):\n" + ex_info);
    }
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
    try
    {
        int n = get_dim(XB);
        matrix e = ident_mat(n);
        solution x;
        for (int i = 0; i < n; i++) {
            x.x = XB.x + s * e[i];
            x.fit_fun(ff, ud1, ud2);
            if (x.y < XB.y) {
                XB = x;
            } else {
                x.x = XB.x - s * e[i];
                x.fit_fun(ff, ud1, ud2);
                if (x.y < XB.y) {
                    XB = x;
                }
            }
        }
        return XB;
    }
    catch (string ex_info)
    {
        throw ("solution HJ_trial(...):\n" + ex_info);
    }
}

solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        //Tu wpisz kod funkcji

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution Rosen(...):\n" + ex_info);
    }
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try {
        solution Xopt;
        double alpha = 1, beta = 0.5, gamma = 2, delta = 0.5, s = 0.5;
        solution X(x0), X1;
        while (true)
        {
            X1 = sym_NM(ff, X.x, s, alpha, beta, gamma, delta, epsilon, Nmax, ud1, c);
            if (norm(X.x - X1.x) < epsilon)
            {
                Xopt = X1;
                Xopt.flag = 0;
                break;
            }
            if (solution::f_calls > Nmax)
            {
                Xopt = X1;
                Xopt.flag = 1;
                break;
            }
            c *= dc;
            X = X1;
        }
        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution pen(...):\n" + ex_info);
    }
}

solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        int n = get_len(x0);
        matrix D = ident_mat(n);
        int N = n + 1;
        solution* S = new solution[N];
        S[0].x = x0;
        S[0].fit_fun(ff, ud1, ud2);
        for (int i = 1; i < N; i++) {
            S[i].x = S[0].x + s * D[i - 1];
            S[i].fit_fun(ff, ud1, ud2);
        }
        solution PO, PE, PZ;
        matrix pc;
        int iMin, iMax;
        while (true) {
            iMin = iMax = 0;
            for (int i = 1; i < N; i++) {
                if (S[iMin].y > S[i].y) iMin = i;
                if (S[iMax].y < S[i].y) iMax = i;
            }
            pc = matrix(n, 1);
            for (int i = 0; i < N; i++) {
                if (i != iMax) pc = pc + S[i].x;
            }
            pc = pc / (N - 1.0);
            PO.x = pc + alpha * (pc - S[iMax].x);
            PO.fit_fun(ff, ud1, ud2);
            if (PO.y < S[iMin].y) {
                PE.x = pc + gamma * (PO.x - pc);
                PE.fit_fun(ff, ud1, ud2);
                if (PE.y < PO.y) S[iMax] = PE;
                else S[iMax] = PO;
            } else {
                if (S[iMin].y <= PO.y && PO.y < S[iMax].y) S[iMax] = PO;
                else {
                    PZ.x = pc + beta * (S[iMax].x - pc);
                    PZ.fit_fun(ff, ud1, ud2);
                    if (PZ.y >= S[iMax].y) {
                        for (int i = 0; i < N; i++) {
                            if (i != iMin) {
                                S[i].x = delta * (S[i].x + S[iMin].x);
                                S[i].fit_fun(ff, ud1, ud2);
                            }
                        }
                    } else {
                        S[iMax] = PZ;
                    }
                }
            }
            if (solution::f_calls > Nmax) {
                cout<<"Error occured"<<endl;
                Xopt.flag = -1;
                Xopt = S[iMin];
                return Xopt;
            }
            double max = 0;
            for (int itmp = 0; itmp < N; itmp++) if (S[itmp].x() > max) max = S[itmp].x();
            if (norm(S[iMin].x - max) < epsilon) break;
        }
        return Xopt = S[iMin];
    }
    catch (string ex_info)
    {
        throw ("solution sym_NM(...):\n" + ex_info);
    }
}

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        Xopt.ud = trans(x0);
        int n = get_len(x0);
        solution X0, X1;
        X0.x = x0;
        matrix d(n, 1);
        solution h;
        while (true) {
            d = -X0.grad(gf, ud1, ud2);
            X1.x = X0.x + h0 * d;
            // cout << X1.x(0) << ";" << X1.x(1) << endl;

            Xopt.ud.add_row(trans(X1.x));

            if (norm(X0.x - X1.x) < epsilon) {
                Xopt = X1;
                Xopt.fit_fun(ff, ud1, ud2);
                Xopt.flag = 0;
                break;
            }
            if (solution::f_calls > Nmax || solution::g_calls > Nmax) {
                Xopt = X1;
                Xopt.fit_fun(ff, ud1, ud2);
                Xopt.flag = 1;
                break;
            }
            X0 = X1;
        }

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution SD(...):\n" + ex_info);
    }
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        Xopt.ud = trans(x0);
        int n = get_len(x0);
        solution X0, X1;
        X0.x = x0;
        matrix d(n, 1), P(n, 2);
        solution h;
        double* ab, beta;
        d = -X0.grad(gf, ud1, ud2);
        while (true) {
            X1.x = X0.x + h0 * d;
            Xopt.ud.add_row(trans(X1.x));
            cout << X1.x(0) << ";" << X1.x(1) << endl;

            if(norm(X0.x - X1.x) < epsilon) {
                Xopt = X1;
                Xopt.fit_fun(ff, ud1, ud2);
                Xopt.flag = 0;
                break;
            }
            //cout << norm(X0.x - X1.x) << " " << epsilon << endl;
            if (solution::f_calls > Nmax || solution::g_calls > Nmax) {
                Xopt = X1;
                Xopt.fit_fun(ff, ud1, ud2);
                Xopt.flag = 1;
                break;
            }
            beta = pow(norm(X1.grad(gf, ud1, ud2)), 2) / pow(norm(X0.g), 2);
            d = -X1.g + beta * d;
            X0 = X1;
        }

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution CG(...):\n" + ex_info);
    }
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
                matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        Xopt.ud = trans(x0);
        int n = get_len(x0);
        solution X0, X1;
        X0.x = x0;
        matrix d(n, 1);

        while (true) {
            d = -inv(X0.hess(Hf, ud1, ud2)) * X0.grad(gf, ud1, ud2);
            X1.x = X0.x + h0 * d;
            cout << X1.x(0) << ";" << X1.x(1) << endl;
            Xopt.ud.add_row(trans((X1.x)));
            if (norm(X0.x - X1.x) < epsilon) {
                Xopt = X1;
                Xopt.fit_fun(ff, ud1, ud2);
                Xopt.flag = 0;
                break;
            }
            // cout << norm(X0.x - X1.x) << " " << epsilon << endl;
            if (solution::f_calls > Nmax || solution::g_calls > Nmax || solution::H_calls > Nmax) {
                Xopt = X1;
                Xopt.fit_fun(ff, ud1, ud2);
                Xopt.flag = 1;
                break;
            }
            X0 = X1;
        }

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution Newton(...):\n" + ex_info);
    }
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        //Tu wpisz kod funkcji

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution golden(...):\n" + ex_info);
    }
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix limits, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
    try
    {
        solution Xopt;
        //Tu wpisz kod funkcji

        return Xopt;
    }
    catch (string ex_info)
    {
        throw ("solution EA(...):\n" + ex_info);
    }
}

/*
 * double a0 = a;
        double b0 = b;
        double c0 = b0 - phi(k-1) / phi(k)*(b0-a0);
        double d0 = a0+b0-c0;
        double ci=c0;
        double di=d0;
        double ai=a0;
        double bi=b0;
        double aip1=a0;
        double bip1=b0;
        double cip1=c0;
        double dip1=d0;
        for(int i=0; i<k-3;i++){
            if(f(ci,ff) < f(di,ff)){
                aip1 = ai;
                bip1 = di;
            }else{
                bip1 = bi;
                aip1 = ci;
            }
            cip1 = bip1 - phi(k-i-2) / phi(k-i-1)*(bip1 - aip1);
            dip1 = aip1 + bip1 - cip1;
        }
        Xopt = cip1;
 * */
