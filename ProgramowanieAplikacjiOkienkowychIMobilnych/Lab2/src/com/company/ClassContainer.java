package com.company;

import java.util.*;

public class ClassContainer {
    //List<Class> listaKlas = new ArrayList<Class>();
    //String nazwa;

    Map<String,Klass> mapaKlas = new HashMap<>();

    public void addClass(String nazwagrupy,List<Student> lista, int max){
        Klass c = new Klass(nazwagrupy, lista, max);
        mapaKlas.put(nazwagrupy, c);
    }
    public void removeClass(String nazwa){
        mapaKlas.remove(nazwa);
    }
    public void findEmpty(){
        for(Map.Entry<String, Klass> entry : mapaKlas.entrySet()) {
            Klass klasa = entry.getValue();
            if (klasa.howManyStudents() * 100 / klasa.getMaksymalnaIloscStudentow() == 0) {
                System.out.println("Znaleziono pustą klasę bez studentów, jest to: "+klasa.getNazwagrupy());
            }
        }
    }


    public void Summary() {
        //System.out.println(nazwa);
        //System.out.println(mapaKlas);
        for(Map.Entry<String, Klass> entry : mapaKlas.entrySet()) {
            Klass klasa = entry.getValue();
            System.out.println("Zajętość grupy " +klasa.getNazwagrupy()+": "+ klasa.howManyStudents()*100/klasa.getMaksymalnaIloscStudentow()+" %");
            //System.out.println(entry.getKey() + " %" + (c.getStudents().size()*100)/c.getMaxStudents());
        }
        //System.out.println(mapaKlas);
    }
}
