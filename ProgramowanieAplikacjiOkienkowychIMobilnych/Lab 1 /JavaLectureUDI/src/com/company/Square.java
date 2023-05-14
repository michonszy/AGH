package com.company;
public class Square extends Figure implements Printable{
    double a;
    //P=a*a
    public Square(double a) {
        this.a = a;
    }

    public double geta() {
        return a;
    }

    public void seta(double a) {
        this.a = a;
    }
    @Override
    public double calculateArea() {
        return a*a;
    }

    @Override
    public double calculatePerimeter() {
        return a+a+a+a;
    }
    public void getInfo(){
        Printable.print(
                "Pole to: "+calculateArea()+"\n"+
                        "Obwod to: "+calculatePerimeter()+"\n");
    }
}
