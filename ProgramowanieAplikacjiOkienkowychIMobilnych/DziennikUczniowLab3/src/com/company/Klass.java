package com.company;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Klass {
    String nazwagrupy;
    List<Student> listaStudentow = new ArrayList<Student>();
    int maksymalnaIloscStudentow;

    public List<Student> getListaStudentow() {
        return listaStudentow;
    }

    public Klass(String nazwagrupy, List<Student> listaStudentow, int maksymalnaIloscStudentow) {
        this.nazwagrupy = nazwagrupy;
        this.listaStudentow = listaStudentow;
        this.maksymalnaIloscStudentow = maksymalnaIloscStudentow;
    }

    public void addStudent(String imie, String nazwisko, StudentCondition stanStudenta, int rokUrodzenia, double iloscPunktow,int pesel) {
        listaStudentow.add(new Student(imie, nazwisko, stanStudenta, rokUrodzenia, iloscPunktow, pesel));
    }
    public void addPoints(Student student, double liczbaPkt){
        for(Student x : listaStudentow){
            if(x == student){
                x.iloscPunktow = x.iloscPunktow + liczbaPkt;
            }
        }
    }
    public void getStudent(Student student){
        for(Student x : listaStudentow){
            if(x == student){
                if(x.iloscPunktow == 0){
                    System.out.println("Student ma 0 punktów, usuwam");
                    listaStudentow.remove(x);
                }else{
                    System.out.println("Student ma więcej niż 0 punktów więc nie usuwam go");
                }
            }
        }
    }
    public void changeCondition(Student student, StudentCondition condition){
        for(Student x : listaStudentow){
            if(x == student){
                x.stanStudenta = condition;
            }
        }
    }
    public void removePoints(Student student, double liczbaPkt){
        for(Student x : listaStudentow){
            if(x == student){
                x.iloscPunktow = x.iloscPunktow - liczbaPkt;
            }
        }
    }
    public void search(String nazwisko){
        for(Student x : listaStudentow){
            if(x.nazwisko == nazwisko ){
                System.out.println(x);
            }
        }
    }
    public void searchPartial(String nazwisko){
        for(Student x : listaStudentow){
            if(x.nazwisko.contains(nazwisko) ){
                System.out.println(x);
            }
        }
    }
    public int countByCondition(StudentCondition condition){
        int licznik = 0;
        for(Student x : listaStudentow){
            if(x.stanStudenta == condition ){
                licznik++;
            }
        }
        return licznik;
    }
    public void Summary(){
        for(Student x : listaStudentow){
            System.out.println(x);
        }
    }
    public void sortByName(){
        listaStudentow.sort(Comparator.comparing(Student::getImie));
    }
    public void sortByPoints(){
        listaStudentow.sort(Comparator.comparing(Student::getIloscPunktow).reversed());
    }
    public int howManyStudents(){
        int licznik = 0;
        for(Student x : listaStudentow){
                licznik++;
        }
        return licznik;
    }

    public int getMaksymalnaIloscStudentow() {
        return maksymalnaIloscStudentow;
    }

    public String getNazwagrupy() {
        return nazwagrupy;
    }

    public void max(){
        Student s1 = Collections.max(listaStudentow, new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return Double.compare(o1.iloscPunktow, o2.iloscPunktow);
            }
        });
    }




}
