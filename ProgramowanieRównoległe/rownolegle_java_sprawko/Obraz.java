package com.company;
import  java.util.Random;

public class Obraz {

    private int size_n;
    private int size_m;
    private char[][] tab;
    private int[] histogram;
    private final Object lock = new Object();

    public Obraz(int n, int m) {

        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];

        final Random random = new Random();

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
                System.out.print(tab[i][j]+" ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        histogram = new int[94];
        clear_histogram();
    }

    public void clear_histogram(){

        for(int i=0;i<94;i++) histogram[i]=0;

    }

    public void calculate_histogram(){

        for(int i=0;i<size_n;i++) {
            for(int j=0;j<size_m;j++) {

                for(int k=0;k<94;k++) {
                    if(tab[i][j] == (char)(k+33)) histogram[k]++;
                }

            }
        }
    }

    public void calculate_histogram(int index) {
        for(int i=0;i<size_n;i++) {
            for(int j=0;j<size_m;j++) {

                if(tab[i][j] == (char)(index+33)) histogram[index]++;

            }
        }
    }

    public void print_histogram(){

        for(int i=0;i<94;i++) {
            System.out.print((char)(i+33)+" "+histogram[i]+"\n");
        }
    }

    public void print_histogram(int index) {
        System.out.print("Wątek " + index + ": "+ (char)(index+33)+" "+histogram[index]+"\n");
    }

    public void print_histogram2(int index, int num) {
        synchronized (lock) {
            System.out.print("Wątek " + index + ": "+ (char)(num+33)+" "+histogram[num] + ": ");


            for(int i = 0; i < histogram[num]; i++) {
                System.out.print((char)(num+33));
            }
            System.out.print("\n");
        }


    }
}
