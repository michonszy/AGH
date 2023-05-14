package com.company;

import javax.swing.*;

public class PopUpAddClass extends JFrame{
    private JPanel panelAdd;
    private JTextArea textArea1;
    private JTextArea textArea2;
    private JButton button1;
    public PopUpAddClass(String title){
        super(title);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(panelAdd);
        this.pack();
    }

    public void setPanelAdd(JPanel panelAdd) {
        this.panelAdd = panelAdd;
    }

    public void setTextArea1(String text) {
        this.textArea1.setText(text);
    }

    public void setTextArea2(String text) {
        this.textArea2.setText(text);
    }

    public void setButton1(JButton button1) {
        this.button1 = button1;
    }

    public JPanel getPanelAdd() {
        return panelAdd;
    }

    public JTextArea getTextArea1() {
        return textArea1;
    }

    public JTextArea getTextArea2() {
        return textArea2;
    }

    public JButton getButton1() {
        return button1;
    }
}
