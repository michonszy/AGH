package com.company;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
	// write your code here
        JFrame frame = new MainGUI("System zarządzania studentami");
        frame.setVisible(true);



        //KOD Z POPRZEDNIEGO PROJEKTU
        List<Student> studenci = new ArrayList<Student>();
        studenci.add(new Student("Zandrzej","Zandrzejewski",StudentCondition.chory,1992,20,920345678));
        studenci.add(new Student("Michal","Michalewski",StudentCondition.odrabiajacy,1995,50,950345678));

        List<Student> studenci2 = new ArrayList<Student>();
        studenci2.add(new Student("Zandrzej","Zandrzejewski",StudentCondition.chory,1765,40,98678435));
        studenci2.add(new Student("Michal","Michalewski",StudentCondition.nieobecny,1856,23,92764389));
        studenci2.add(new Student("Michal","Michalewski",StudentCondition.odrabiajacy,2001,500,986872376));
        studenci2.add(new Student("Michal","Michalewski",StudentCondition.obecny,2020,76,139089746));


        List<Student> studencipusci = new ArrayList<Student>();

        Klass klasa1 = new Klass("KlasaA",studenci,10);


        System.out.println("> Wypisuje studentów: ");
        klasa1.Summary();
        System.out.println("> Sortuje po ilości punktów");
        klasa1.sortByPoints();
        System.out.println("> Posortowani, pokazuje po zmianie");
        klasa1.Summary();
        System.out.println("> Próbuję usunąć studenta 1");
        klasa1.getStudent(studenci.get(1));

        System.out.println("> Zmieniam kondycje studenta 0");
        klasa1.changeCondition(studenci.get(0),StudentCondition.nieobecny);
        System.out.println("> Zmienione, pokazuje po zmianie");
        klasa1.Summary();

        ClassContainer kontener = new ClassContainer();
        kontener.addClass("1B",studenci,10);
        kontener.addClass("2C",studenci2,5);
        kontener.addClass("3C",studencipusci,5);

        System.out.println("> Wyświetlam podsumowanie kontenera klas");
        kontener.Summary();

        System.out.println("> Szukam pustej klasy");
        kontener.findEmpty();

        System.out.println("> Usuwam jedna klase");
        kontener.removeClass("1B");

        System.out.println("> Wyświetlam podsumowanie kontenera klas");
        kontener.Summary();
    }
}
