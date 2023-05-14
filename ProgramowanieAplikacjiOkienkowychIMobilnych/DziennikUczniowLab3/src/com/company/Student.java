package com.company;

import javax.swing.*;

public class Student implements Comparable{
    String imie;
    String nazwisko;
    StudentCondition stanStudenta;
    int rokUrodzenia;
    double iloscPunktow;
    int pesel;

    public Student(String imie, String nazwisko, StudentCondition stanStudenta, int rokUrodzenia, double iloscPunktow,int pesel) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.stanStudenta = stanStudenta;
        this.rokUrodzenia = rokUrodzenia;
        this.iloscPunktow = iloscPunktow;
        this.pesel = pesel;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public StudentCondition getStanStudenta() {
        return stanStudenta;
    }
    public String getStanStudentaStringowo() {
        return StudentCondition.values().toString();
    }
    public int getRokUrodzenia() {
        return rokUrodzenia;
    }

    public int getPesel() {
        return pesel;
    }

    public String getImie() {
        return imie;
    }

    public double getIloscPunktow() {
        return iloscPunktow;
    }

    @Override
    public String toString() {
        return "Student{" +
                "imie='" + imie + '\'' +
                ", nazwisko='" + nazwisko + '\'' +
                ", stanStudenta=" + stanStudenta +
                ", rokUrodzenia=" + rokUrodzenia +
                ", iloscPunktow=" + iloscPunktow +
                ", pesel=" + pesel +
                '}';
    }
}
