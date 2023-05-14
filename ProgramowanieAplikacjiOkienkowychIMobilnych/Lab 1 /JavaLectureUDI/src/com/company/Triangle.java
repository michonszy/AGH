package com.company;
public class Triangle extends Figure implements Printable{
    double h;
    double a; //podstawa
    double b; //jeden bok
    double c; //drugi bok
    //P=(a*h)/2

    public Triangle(double h, double a, double b, double c) {
        this.h = h;
        this.a = a;
        this.b = b;
        this.c = c;

    }

    public double geth() {
        return h;
    }

    public void seth(double h) {
        this.h = h;
    }

    public double geta() {
        return a;
    }

    public void seta(double a) {
        this.a = a;
    }
    @Override
    public double calculateArea() {
        return (a*h)/2;
    }

    @Override
    public double calculatePerimeter() {
        return a + b +c;
    }
    public void getInfo(){
        Printable.print(
                "Pole to: "+calculateArea()+"\n"+
                "Obwod to: "+calculatePerimeter()+"\n");
    }
}
