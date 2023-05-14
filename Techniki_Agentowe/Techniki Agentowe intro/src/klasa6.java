import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.core.behaviours.OneShotBehaviour;
import java.util.Scanner;

public class klasa6 extends Agent {

    private Behaviour behaviour = new OneShotBehaviour() {
        @Override
        public void action() {
            System.out.println("zachowanie startuje");
            Scanner scanner = new Scanner(System.in);
            System.out.println("Podaj liczbę całkowitą:");
            int number = scanner.nextInt();
            if (number < 0) {
                myAgent.removeBehaviour(this);
            }
        }

        @Override
        public int onEnd() {
            System.out.println("zachowanie zakończone");
            return super.onEnd();
        }
    };

    @Override
    protected void setup() {
        System.out.println("startuję");
        addBehaviour(behaviour);
    }

    @Override
    protected void takeDown() {
        System.out.println("zaraz się usunę");
    }
}
