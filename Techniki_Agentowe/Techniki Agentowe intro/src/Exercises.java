import java.util.Random;
import java.util.Scanner;
import java.util.HashMap;
import java.util.Map;
public class Exercises {

    public static void main(String[] args) {

    }
    public void zad1(){
        for (int i = 0; i <= 100; i++) {
            if (i % 3 == 0 && i % 5 == 0) {
                System.out.println("xyxy");
            } else if (i % 3 == 0) {
                System.out.println("xxx");
            } else if (i % 5 == 0) {
                System.out.println("yyy");
            } else {
                System.out.println(i);
            }
        }
    }
    public void zad2(){
        Random random = new Random();
        int number = random.nextInt(101);
        int guess = 0;
        int count = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Zgadywanie liczby 0-100");
        while (guess != number) {
            System.out.print("Podaj liczbę: ");
            guess = scanner.nextInt();
            count++;
            if (guess < number) {
                System.out.println("Za mało.");
            } else if (guess > number) {
                System.out.println("Za dużo.");
            } else {
                System.out.println(guess + " to poprawna odpowiedź, zgadłeś ją w ilości prób" + count);
            }
        }

        scanner.close();
    }
    public void zad3(){
        int[] numbers = { 1,6,5,4,3,2,7,12,8};
        int max = 0;
        int secondMax = 0;

        // wyświetlamy tablicę
        System.out.print("Tablica: ");
        for (int number : numbers) {
            System.out.print(number + " ");
            if (number > max) {
                secondMax = max;
                max = number;
            } else if (number > secondMax && number != max) {
                secondMax = number;
            }
        }

        // wyświetlamy największą i drugą co do wielkości wartość
        System.out.println("\nNajwiększa wartość: " + max);
        System.out.println("Druga co do wielkości wartość: " + secondMax);
    }
    public static String reverseString(String s) {
        StringBuilder reversed = new StringBuilder();
        for (int i = s.length() - 1; i >= 0; i--) {
            reversed.append(s.charAt(i));
        }
        return reversed.toString();
    }

    public static boolean isPalindrome(String s) {
        String reversed = reverseString(s);
        return s.equals(reversed);
    }

    public void zad4(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Podaj wyraz lub ciąg liczb: ");
        String input = scanner.nextLine();
        String reversedInput = reverseString(input);

        System.out.println("Odwrócony wyraz/ciąg: " + reversedInput);

        if (isPalindrome(input)) {
            System.out.println("Podany wyraz/ciąg jest palindromem");
        } else {
            System.out.println("Podany wyraz/ciąg nie jest palindromem");
        }
    }
    public void zad5(){
        String s = "Siema to siema ja to ja ,że wiadomo";
        // zakładam że jedyne co oddzielać będzie zdania to spacje
        String[] words = s.split(" ");
        Map<String, Integer> wordCount = new HashMap<>();
        for (String word : words) {
            if (!wordCount.containsKey(word)) {
                wordCount.put(word, 1);
            } else {
                int count = wordCount.get(word);
                wordCount.put(word, count + 1);
            }
        }

        for (Map.Entry<String, Integer> entry : wordCount.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
    }

    public static boolean isPrime(int number) {
        if (number < 2) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(number); i++) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }
    public void zad6(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Podaj liczbę: ");
        int number = scanner.nextInt();

        boolean isPrime = isPrime(number);

        if (isPrime) {
            System.out.println(number + " jest liczbą pierwszą.");
        } else {
            System.out.println(number + " nie jest liczbą pierwszą.");
        }
    }
    public void zad7() {
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8 - i; j++) {
                System.out.print(" ");
            }
            for (int k = 1; k <= 2 * i - 1; k++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }
    public static double kmToLandmiles(double kilometers) {
        return kilometers / 1.609;
    }

    public static double kmToSeaMiles(double kilometers) {
        return kilometers / 1.852;
    }
    public void zad8(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Podaj odległość w km: ");
        double distance = scanner.nextDouble();

        double landMiles = kmToLandmiles(distance);
        double seaMiles = kmToSeaMiles(distance);

        System.out.println(distance + " kilometrów to " + landMiles + " mil lądowych i " + seaMiles + " mil morskich.");

    }
}
