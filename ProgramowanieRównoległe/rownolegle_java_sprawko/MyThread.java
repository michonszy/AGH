package com.company;

public class MyThread extends Thread{

    private Obraz obraz;
    private int index;

    @Override
    public void run() {
        obraz.calculate_histogram(index);
        obraz.print_histogram(index);
    }

    public MyThread(int index, Obraz obraz) {
        this.obraz = obraz;
        this.index = index;
    }
}
