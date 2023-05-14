package com.company;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.util.List;

public class PopUpek extends JFrame {
    private JPanel mPanel;
    private JTextArea textArea6;
    private JButton addButton;
    private JTextArea textArea1;
    private JTextArea textArea2;
    private JTextArea textArea4;
    private JTextArea textArea5;
    private JComboBox comboBox1;

    public PopUpek(String title){
        super(title);

        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(mPanel);
        this.pack();
    }

    public JPanel getmPanel() {
        return mPanel;
    }

    public JTextArea getTextArea6() {
        return textArea6;
    }

    public JButton getAddButton() {
        return addButton;
    }

    public JTextArea getTextArea1() {
        return textArea1;
    }

    public JTextArea getTextArea2() {
        return textArea2;
    }

    public JTextArea getTextArea4() {
        return textArea4;
    }

    public JTextArea getTextArea5() {
        return textArea5;
    }

    public JComboBox getComboBox1() {
        return comboBox1;
    }

    public void setmPanel(JPanel mPanel) {
        this.mPanel = mPanel;
    }

    public void setTextArea6(Integer text) {
        textArea6.setText(Integer.toString(text));
    }

    public void setAddButton(JButton addButton) {
        this.addButton = addButton;
    }

    public void setTextArea1(String text) {
        textArea1.setText(text);
    }

    public void setTextArea2(String text) {
        textArea2.setText(text);
    }

    public void setTextArea4(Integer text) {
        textArea4.setText(Integer.toString(text));
    }

    public void setTextArea5(Double text) {
        textArea5.setText(Double.toString(text));
    }

    public void setComboBox1(String comboBoxString) {
        if(comboBoxString == "odrabiajacy"){
            this.comboBox1.setSelectedItem(StudentCondition.odrabiajacy);
        }else if(comboBoxString == "chory"){
            this.comboBox1.setSelectedItem(StudentCondition.chory);
        }else if(comboBoxString == "nieobecny"){
            this.comboBox1.setSelectedItem(StudentCondition.nieobecny);
        }else if(comboBoxString == "obecny"){
            this.comboBox1.setSelectedItem(StudentCondition.obecny);
        }


    }

    private void createUIComponents() {

        String [] items = {};
        //comboBox1 = new JComboBox(stan);
        comboBox1 = new JComboBox<>();
        comboBox1.setModel(new DefaultComboBoxModel<>(StudentCondition.values()));

        addButton = new JButton();
        addButton.addActionListener(e ->
        {

           String imie = textArea1.getText();
           String nazwisko = textArea2.getText();
           //String stan = (String) comboBox1.getSelectedItem();
           String rokUrodzenia = textArea4.getText();
           String iloscPunktow = textArea5.getText();
           String pesel = textArea6.getText();


        });
    }
}
