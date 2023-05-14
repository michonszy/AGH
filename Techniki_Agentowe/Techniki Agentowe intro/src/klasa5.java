import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import java.util.Scanner;

public class klasa5 extends Agent {

    protected void setup() {
        System.out.println("startuję");

        // dodaj zachowanie
        addBehaviour(new Behaviour() {
            public void action() {
                Scanner scanner = new Scanner(System.in);
                System.out.println("Podaj liczbę całkowitą:");
                int liczba = scanner.nextInt();
                if (liczba < 0) {
                    myAgent.removeBehaviour(this);
                }
            }

            public boolean done() {
                return false;
            }
        });
    }

    protected void takeDown() {
        System.out.println("zaraz się usunę");

    }
}
