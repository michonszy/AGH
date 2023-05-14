package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	// write your code here
        System.out.print("Figury do wybrania \n" +
                "[1] Trójkąt \n" +
                "[2] Kwadrat \n" +
                "[3] Koło \n" +
                "[4] Graniastosłup \n" +
                "Podaj wybór: ");
        Scanner scanner = new Scanner(System.in);
        int myString = scanner.nextInt();

        if (myString == 1) {
            System.out.print("Podaj wysokosc: ");
            double h = scanner.nextDouble();
            System.out.print("Podaj dlugosc podstawy: ");
            double a = scanner.nextDouble();
            System.out.print("Podaj dlugosc b: ");
            double b = scanner.nextDouble();
            System.out.print("Podaj dlugosc c: ");
            double c = scanner.nextDouble();
            if (h < 0 || a<0 || b<0 || c<0){
                System.out.println("Nie można podawać ujemnych wartości!");
            }else{
                Triangle trojkat = new Triangle(h,a,b,c);
                trojkat.getInfo();
            }

        } else if (myString == 2) {
            System.out.print("Podaj dlugosc: ");
            double a = scanner.nextDouble();

            Square kwadrat = new Square(a);
            kwadrat.getInfo();
        }
        else if (myString == 3){
            System.out.print("Podaj promien: ");
            double r = scanner.nextDouble();
            Circle kolo = new Circle(r);
            kolo.getInfo();
        } else if (myString == 4) {
            System.out.println("Podaj dlugosci lub 0 nie wystepuje, dla kwadrata c,a,b to będa oczywiście te same długości");
            //tutaj jeszcze wybor podstawy
            System.out.print("Podaj dlugosc c podstawy: ");
            double c = scanner.nextDouble();
            System.out.print("Podaj dlugosc a podstawy: ");
            double a = scanner.nextDouble();
            System.out.print("Podaj dlugosc b podstawy: ");
            double b = scanner.nextDouble();
            System.out.print("Podaj wysokosc h graniastolupa: ");
            double h = scanner.nextDouble();
            System.out.print("Jeżeli podstawą ma być trójkąt to podaj jego wysokość, jak nie podaj zero: ");
            double wysT = scanner.nextDouble();
            Prism graniastoslup = new Prism(h,a,b,c,wysT);
            graniastoslup.getInfo();
        } else{
                System.out.println("Brak takiej opcji! Kończę działanie programu");
        }
        //System.out.println("Wybrano: "+ myString);
    }
}
