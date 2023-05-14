//SZYMON MICHOŃ
#include <iostream>
using namespace std;
double f1(double xn, double yn) {
	return xn * xn + yn;
}
double f2(double xn, double yn) {
	return xn + yn;
}
double frk2(double xn, double yn,double hn) {
	double k1 = f1(xn, yn);
	double k2 = f1(xn + hn, yn + hn * k1);
	return (k1 + k2) / 2;
}

void metodaEulera(double x0, double y0, double x, double n, double(*funkcja)(double, double)) {
	double h = (x - x0) / n;
	//cout << "Obliczenia do Eulera" << endl;
	for (int i = 0; i < n; i++) {
		y0 = y0 + h * funkcja(x0, y0);
		x0 = x0 + h;
		//cout << "x: " << x0 << " y: " << y0 << endl;
	}
	cout << "WYNIK: " << y0 << endl;
}
void metodaRK2(double x0, double y0, double x, double n, double(*funkcja)(double, double)) {
	double h = (x - x0) / n;
	for (int i = 0; i < n; i++) {
		double k1 = funkcja(x0, y0);
		double k2 = funkcja(x0 + h, y0+ h * k1);
		//cout << "k1: " << k1 << " k2: " << k2 << endl;
		double wynik = (1.0/2.0)*(k1 + k2);
		y0 = y0 + h * wynik;
		x0 = x0 + h;
		//cout << "x: " << x0 << " y: " << y0 << endl;
	}
	cout << "WYNIK RK2: " << y0 << endl;
}
void metodaRK4(double x0, double y0, double x, double n, double(*funkcja)(double, double)) {
	double h = (x - x0) / n;
	for (int i = 0; i < n; i++) {
		double k1 = funkcja(x0, y0);
		double k2 = funkcja(x0 + 0.5 * h, y0 + 0.5 * h * k1);
		double k3 = funkcja(x0 + 0.5 * h, y0 + 0.5 * h * k2);
		double k4 = funkcja(x0 + h, y0 + h * k3);
		double wynik = (1.0/6.0) * (k1 + (2.0 * k2) + (2.0 * k3) + k4);
		//cout << wynik << endl;
		y0 = y0 + h * wynik;
		x0 = x0 + h;
		//cout << "x: " << x0 << " y: " << y0 << endl;
	}
	cout << "WYNIK RK4: " << y0 << endl;
}
int main()
{
	metodaEulera(0, 0.1, 0.3, 3, f1);
	metodaEulera(0, 0.1, 1, 10, f1);
	metodaEulera(0, 0.1, 1, 10, f2);

	cout << endl << "Metoda RK2" << endl;
	metodaRK2(0, 0.1, 0.3, 3, f1);
	metodaRK2(0, 0.1, 1, 10, f1);
	metodaRK2(0, 0.1, 1, 10, f2);

	cout << endl << "Metoda RK4" << endl;
	metodaRK4(0, 0.1, 0.3, 3, f1);
	metodaRK4(0, 0.1, 1, 10, f1);
	metodaRK4(0, 0.1, 1, 10, f2);
}