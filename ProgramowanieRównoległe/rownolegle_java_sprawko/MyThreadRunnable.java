package com.company;

public class MyThreadRunnable implements Runnable{

    private int portion;
    private Obraz obraz;
    private int index;
    @Override
    public void run() {
        System.out.println("Wątek: " + index + ", Start:" + index*portion + ", Koniec:" + (index + 1) * portion);
        for(int i = index * portion; i < (index + 1) * portion; i++) {

            obraz.calculate_histogram(i);
            obraz.print_histogram2(index, i);
        }
    }

    MyThreadRunnable(int index ,int portion, Obraz obraz) {

        this.portion = portion;
        this.obraz = obraz;
        this.index = index;
    }
}
