package com.company;
public class Prism extends Figure{
    double h;
    double Pp;
    double a,b,c;
    double wysT;

    public Prism(double h, double a, double b, double c,double wysT) {
        this.h = h;
        this.a = a;
        this.b = b;
        this.c = c;
        this.wysT = wysT;
    }

    @Override
    public double calculateArea() {
        //Pc = 2 Pp + Pb
        double Pp=0;
        double Pb=0;
        if(wysT != 0){
            Pp = a*wysT/2;
            Pb = (a*h)+(b*h)+(c*h);
        }else{
            Pp=a*b;
            Pb = 4*(a*h);
        }
        return (2*Pp)+Pb; //to jest narazie źle
    }

    @Override
    public double calculatePerimeter() {
        //V=Pp*h
        double Pp=0;

        if(wysT != 0){
            Pp = a*wysT/2;

        }else{
            Pp=a*b;
        }
        return Pp*h;
    }
    public void getInfo(){
        Printable.print(
                "Pole to: "+calculateArea()+"\n"+
                        "Obwod to: "+calculatePerimeter()+"\n");
    }
}
