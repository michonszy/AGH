package com.company;
import java.util.Scanner;

public class Histogram_test {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);

        //obraz_1.calculate_histogram();
        //obraz_1.print_histogram();





        //wariant 1
        /*
        int num_threads = 94;

        MyThread[] ThreadArray = new MyThread[num_threads];

        for (int i = 0; i < num_threads; i++) {
            (ThreadArray[i] = new MyThread(i, obraz_1)).start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
        	ThreadArray[i].join();
           } catch (InterruptedException e) {}
        }
        */

        //wariant 2

        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();

        int portion = (int)Math.ceil(94/num_threads);

        Thread threadArray[] = new Thread[num_threads];

        for(int i = 0; i < num_threads; i++) {
            threadArray[i] = new Thread(new MyThreadRunnable(i, portion, obraz_1));
            threadArray[i].start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                threadArray[i].join();
            } catch (InterruptedException e) {}
        }
    }
}
