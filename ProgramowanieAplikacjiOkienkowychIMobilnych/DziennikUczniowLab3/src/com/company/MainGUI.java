package com.company;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MainGUI extends JFrame{
    private JPanel mainPanel;
    private JButton addGroupButton;
    private JButton addStudentButton;
    private JButton removeGroupButton;
    private JButton removeStudentButton;

    private JTable studentTable;
    private JScrollPane scrollClassesPanel;
    private JScrollPane scrollStudentPanel;
    private JTable classesTable;
    private JButton sortStudentsByNameButton;
    private JButton sortStudentsByPointsButton;
    private JButton edytujWybranegoStudentaButton;
    private JButton edytujKlaseButton;
    //private JTable studentsTable;



    public MainGUI(String title) {
        super(title);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setContentPane(mainPanel);
        this.pack();

    }


private void klikniento(){
    System.out.println("Pressseddc");
}

public void dodajStudentaClicked(List<Student> studenci,DefaultTableModel tableModelStudenci,String imie, String nazwisko, StudentCondition stanStudenta, int rokUrodzenia, double iloscPunktow,int pesel) {

    studenci.add(new Student(imie, nazwisko, stanStudenta, rokUrodzenia, iloscPunktow, pesel) );
    int indeks = studenci.size()-1;
    tableModelStudenci.insertRow(indeks,new Object[]{studenci.get(indeks).imie,
            studenci.get(indeks).nazwisko,
            studenci.get(indeks).stanStudenta,
            studenci.get(indeks).rokUrodzenia,
            studenci.get(indeks).iloscPunktow,
            studenci.get(indeks).pesel,
    });
}
private void usunStudentaClicked(){

}
private void dodajGrupeClicked(){

}
private void usunGrupeClicked(){

}
private void jTable1MouseClicked(java.awt.event.MouseEvent evt) {
        JTable source = (JTable)evt.getSource();
        int row = source.rowAtPoint( evt.getPoint() );
        int column = source.columnAtPoint( evt.getPoint() );
        String s=source.getModel().getValueAt(row, column)+"";

        JOptionPane.showMessageDialog(null, s);
    System.out.println(s);
    }
    private void createUIComponents() {
        // TODO: place custom component creation code here
//grupy stworzone na potrzeby początkowych wartości
    List<Student> studenci = new ArrayList<Student>();
    ClassContainer kontener = new ClassContainer();
        studenci.add(new Student("Zandrzej","Zandrzejewski",StudentCondition.chory,1992,20,920345678));
        studenci.add(new Student("Michal","Michalewski",StudentCondition.odrabiajacy,1995,50,950345678));

        List<Student> studenci2 = new ArrayList<Student>();
        studenci2.add(new Student("Zandrzej","Zandrzejewski",StudentCondition.chory,1765,40,98678435));
        studenci2.add(new Student("Michal","Michalewski",StudentCondition.nieobecny,1856,23,92764389));
        studenci2.add(new Student("Michal","Michalewski",StudentCondition.odrabiajacy,2001,500,986872376));
        studenci2.add(new Student("Michal","Michalewski",StudentCondition.obecny,2020,76,139089746));

        List<Student> studencipusci = new ArrayList<Student>();

        DefaultTableModel tableModelStudenci;
        tableModelStudenci = new DefaultTableModel();
        studentTable = new JTable(tableModelStudenci);
        tableModelStudenci.addColumn("Imie");
        tableModelStudenci.addColumn("Nazwisko");
        tableModelStudenci.addColumn("Kondycja studenta");
        tableModelStudenci.addColumn("Rok urodzenia");
        tableModelStudenci.addColumn("Ilosc Punktów");
        tableModelStudenci.addColumn("Pesel");

        DefaultTableModel tableModelKlasy;
        tableModelKlasy = new DefaultTableModel();
        classesTable = new JTable(tableModelKlasy);
        tableModelKlasy.addColumn("Nazwa grupy");
        tableModelKlasy.addColumn("Zajętość");



        kontener.addClass("1B",studenci,10);
        kontener.addClass("2C",studenci2,13);
        kontener.addClass("3C",studencipusci,5);

        int indeks = 0;
            for (Map.Entry<String, Klass> entry : kontener.mapaKlas.entrySet()) {
                tableModelKlasy.insertRow(indeks, new Object[]{entry.getKey(), entry.getValue().howManyStudents() * 100 / entry.getValue().maksymalnaIloscStudentow + " %"});
                indeks++;
            }
           /* tableModelKlasy.insertRow(i,new Object[]{kontener.mapaKlas.get(i).getNazwagrupy(),
            kontener.mapaKlas.get("2C").howManyStudents()*100/kontener.mapaKlas.get("2C").maksymalnaIloscStudentow+" %"});
        }*/

        for(int i=0; i<studenci.size();i++){
            tableModelStudenci.insertRow(i,new Object[]{studenci.get(i).imie,
                    studenci.get(i).nazwisko,
                    studenci.get(i).stanStudenta,
                    studenci.get(i).rokUrodzenia,
                    studenci.get(i).iloscPunktow,
                    studenci.get(i).pesel,
            });
        }

        addStudentButton = new JButton();
        addStudentButton.addActionListener(e ->
        {
            PopUpek pp = new PopUpek("Siema");
            pp.getAddButton().addActionListener(x ->
            {
                try{
                    String imie = pp.getTextArea1().getText();
                    String nazwisko = pp.getTextArea2().getText();
                    //String stan = (String) comboBox1.getSelectedItem();
                    Object obj= pp.getComboBox1().getSelectedItem();
                    String stan = obj.toString();

                    String rokUrodzenia = pp.getTextArea4().getText();
                    String iloscPunktow = pp.getTextArea5().getText();
                    String pesel = pp.getTextArea6().getText();
                    if(stan == "odrabiajacy"){
                        dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.odrabiajacy,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));

                    }else if(stan == "chory"){
                        dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.chory,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));


                    }else if(stan == "nieobecny"){
                        dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.nieobecny,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));

                    }else if(stan == "obecny"){
                        dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.obecny,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));

                    }else{
                        throw new RuntimeException();
                    }
                }
                catch (Exception exception) {
                    JOptionPane.showMessageDialog(this,"Błędne dane!!");
                }
            });
            pp.setVisible(true);
        });
        edytujKlaseButton = new JButton();
        edytujKlaseButton.addActionListener(e ->
        {
            PopUpAddClass pp = new PopUpAddClass("Siema");
            String nazwa = classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString();
            Integer maxIlosc = kontener.mapaKlas.get(classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString()).getMaksymalnaIloscStudentow();
            try{

                pp.setTextArea1(nazwa);
                pp.setTextArea2(Integer.toString(maxIlosc));

                pp.setVisible(true);
                pp.getButton1().addActionListener(x ->{
                    kontener.mapaKlas.remove(classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString());
                    tableModelKlasy.removeRow(classesTable.getSelectedRow());
                    tableModelStudenci.setRowCount(0);
                    try{
                        String nazwa2 = pp.getTextArea1().getText();
                        String maxilosc = pp.getTextArea2().getText();

                        kontener.addClass(nazwa2,studencipusci,Integer.parseInt(maxilosc));
                        int indec = kontener.mapaKlas.size()-1;
                        int indeks2 = 0;
                        tableModelKlasy.setRowCount(0);
                        for (Map.Entry<String, Klass> entry : kontener.mapaKlas.entrySet()) {
                            tableModelKlasy.insertRow(indeks2, new Object[]{entry.getKey(), entry.getValue().howManyStudents() * 100 / entry.getValue().maksymalnaIloscStudentow + " %"});
                            indeks2++;
                        }
                    }
                    catch (Exception exception){
                        JOptionPane.showMessageDialog(this,"Błędne dane!!");
                    }

                });


            }
            catch(Exception exception){
                JOptionPane.showMessageDialog(this,"Nie zaznaczyłeś klasy!");
            }

        });
        edytujWybranegoStudentaButton = new JButton();
        edytujWybranegoStudentaButton.addActionListener(e ->
        {
            PopUpek pp = new PopUpek("Siema");
            try{
                studentTable.getSelectedRow();
                System.out.println(studentTable.getValueAt(studentTable.getSelectedRow(), 0).toString());
                int zmienna =0;
                for(int i=0;i<studenci.size();i++){
                    if(studentTable.getValueAt(studentTable.getSelectedRow(), 0).toString() == studenci.get(i).getImie()){
                        zmienna = i;
                    }
                }
                pp.setTextArea1(studenci.get(zmienna).getImie());
                pp.setTextArea2(studenci.get(zmienna).getNazwisko());
                pp.setTextArea4(studenci.get(zmienna).getRokUrodzenia());
                pp.setTextArea5(studenci.get(zmienna).getIloscPunktow());
                pp.setTextArea6(studenci.get(zmienna).getPesel());
                pp.setComboBox1(studenci.get(zmienna).getStanStudentaStringowo());
                pp.getAddButton().addActionListener(x ->

                {
                    try{
                        String imie = pp.getTextArea1().getText();
                        String nazwisko = pp.getTextArea2().getText();
                        //String stan = (String) comboBox1.getSelectedItem();
                        Object obj= pp.getComboBox1().getSelectedItem();
                        String stan = obj.toString();

                        String rokUrodzenia = pp.getTextArea4().getText();
                        String iloscPunktow = pp.getTextArea5().getText();
                        String pesel = pp.getTextArea6().getText();

                        kontener.mapaKlas.get(classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString()).listaStudentow.remove(studentTable.getSelectedRow());
                        tableModelStudenci.removeRow(studentTable.getSelectedRow());

                        if(stan == "odrabiajacy"){
                            dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.odrabiajacy,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));

                        }else if(stan == "chory"){
                            dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.chory,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));


                        }else if(stan == "nieobecny"){
                            dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.nieobecny,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));

                        }else if(stan == "obecny"){
                            dodajStudentaClicked(studenci,tableModelStudenci,imie,nazwisko,StudentCondition.obecny,Integer.parseInt(rokUrodzenia),Double.parseDouble(iloscPunktow),Integer.parseInt(pesel));

                        }else{
                            throw new RuntimeException();
                        }
                    }
                    catch (Exception exception) {
                        JOptionPane.showMessageDialog(this,"Błędne dane!!");
                    }
                });
                pp.setVisible(true);
            }
            catch(Exception exception){
                JOptionPane.showMessageDialog(this,"Nie wybrano nic do edycji!!");
            }



        });

//nasluchiwanie ktory element w tabeli klas został naciśnięty
        classesTable.getSelectionModel().addListSelectionListener(new ListSelectionListener(){
            public void valueChanged(ListSelectionEvent event) {
                try{
                    String nazwa = classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString();
                    System.out.println(nazwa);
                    tableModelStudenci.setRowCount(0);
                    for(int i=0; i<kontener.mapaKlas.get(nazwa).listaStudentow.size();i++){
                        tableModelStudenci.insertRow(i,new Object[]{kontener.mapaKlas.get(nazwa).listaStudentow.get(i).imie,
                                kontener.mapaKlas.get(nazwa).listaStudentow.get(i).nazwisko,
                                kontener.mapaKlas.get(nazwa).listaStudentow.get(i).stanStudenta,
                                kontener.mapaKlas.get(nazwa).listaStudentow.get(i).rokUrodzenia,
                                kontener.mapaKlas.get(nazwa).listaStudentow.get(i).iloscPunktow,
                                kontener.mapaKlas.get(nazwa).listaStudentow.get(i).pesel,
                        });
                    }
                }
                catch(Exception exception){
                    System.out.println("Nie uda sie");
                }

            }
        });


    addGroupButton = new JButton();
    addGroupButton.addActionListener(e ->
    {
        PopUpAddClass popDodaniaKlasy = new PopUpAddClass("Dodawanie klasy");
        popDodaniaKlasy.setVisible(true);

        popDodaniaKlasy.getButton1().addActionListener(x ->
        {
            try{
                String nazwa = popDodaniaKlasy.getTextArea1().getText();
                String maxilosc = popDodaniaKlasy.getTextArea2().getText();

                kontener.addClass(nazwa,studencipusci,Integer.parseInt(maxilosc));
                int indec = kontener.mapaKlas.size()-1;

                tableModelKlasy.insertRow(indec,new Object[]{nazwa,kontener.mapaKlas.get(nazwa).howManyStudents() * 100 / kontener.mapaKlas.get(nazwa).maksymalnaIloscStudentow + " %"});
            }
            catch (Exception exception){
                JOptionPane.showMessageDialog(this,"Błędne dane!!");
            }
        });

    });
    removeGroupButton = new JButton();
    removeGroupButton.addActionListener(e ->
    {
        kontener.mapaKlas.remove(classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString());
        tableModelKlasy.removeRow(classesTable.getSelectedRow());
    });
        removeStudentButton = new JButton();
        removeStudentButton.addActionListener(e ->
        {
            studenci.remove(studentTable.getSelectedRow());
            tableModelStudenci.removeRow(studentTable.getSelectedRow());

        });

    sortStudentsByNameButton = new JButton();
    sortStudentsByNameButton.addActionListener(x -> {
        TableRowSorter<TableModel> sorter = new TableRowSorter<TableModel>(studentTable.getModel());
        studentTable.setRowSorter(sorter);
        List<RowSorter.SortKey> sortKeys = new ArrayList<>(25);
        sortKeys.add(new RowSorter.SortKey(0, SortOrder.ASCENDING));
        //sortKeys.add(new RowSorter.SortKey(0, SortOrder.ASCENDING));
        sorter.setSortKeys(sortKeys);

    });
        sortStudentsByPointsButton = new JButton();
        sortStudentsByPointsButton.addActionListener(x -> {
            kontener.mapaKlas.get(classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString()).sortByPoints();

            String nazwa = classesTable.getValueAt(classesTable.getSelectedRow(), 0).toString();
            System.out.println(nazwa);
            tableModelStudenci.setRowCount(0);
            for(int i=0; i<kontener.mapaKlas.get(nazwa).listaStudentow.size();i++) {
                tableModelStudenci.insertRow(i, new Object[]{kontener.mapaKlas.get(nazwa).listaStudentow.get(i).imie,
                        kontener.mapaKlas.get(nazwa).listaStudentow.get(i).nazwisko,
                        kontener.mapaKlas.get(nazwa).listaStudentow.get(i).stanStudenta,
                        kontener.mapaKlas.get(nazwa).listaStudentow.get(i).rokUrodzenia,
                        kontener.mapaKlas.get(nazwa).listaStudentow.get(i).iloscPunktow,
                        kontener.mapaKlas.get(nazwa).listaStudentow.get(i).pesel,
                });
            }
            /*TableRowSorter<TableModel> sorter = new TableRowSorter<TableModel>(studentTable.getModel());
            studentTable.setRowSorter(sorter);
            List<RowSorter.SortKey> sortKeys = new ArrayList<>(25);
            sortKeys.add(new RowSorter.SortKey(4, SortOrder.ASCENDING));
            //sortKeys.add(new RowSorter.SortKey(0, SortOrder.ASCENDING));
            sorter.setSortKeys(sortKeys);*/
        });

        addStudentButton.setVisible(true);
        studentTable.setVisible(true);

    }
}
