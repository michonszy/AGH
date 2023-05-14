package com.company;
public class Circle extends Figure implements Printable{
    double r;
    //P=3.14*r*r
    public Circle(double r) {
        this.r = r;
    }

    public double getr() {
        return r;
    }

    public void setr(double r) {
        this.r = r;
    }


    @Override
    public double calculateArea() {
        return 3.14*r*r;
    }

    @Override
    public double calculatePerimeter() {
        return 2*3.14*r;
    }
    public void getInfo(){
        Printable.print(
                "Pole to: "+calculateArea()+"\n"+
                        "Obwod to: "+calculatePerimeter()+"\n");
    }
}
