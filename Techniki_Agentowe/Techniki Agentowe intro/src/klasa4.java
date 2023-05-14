import jade.core.Agent;
import jade.core.behaviours.Behaviour;

public class klasa4 extends Agent {

    protected void setup() {
        System.out.println("startuję");

        // dodaj zachowanie generyczne
        addBehaviour(new Behaviour() {
            private int step = 0;

            public void action() {
                switch (step) {
                    case 1:
                        System.out.println("pierwszy krok");
                        step++;
                        break;
                    case 2:
                        System.out.println("drugi krok");
                        step++;
                        break;
                    case 3:
                        System.out.println("trzeci krok");
                        step++;
                        break;
                }
            }

            public boolean done() {
                return (step > 3);
            }
        });
    }

    protected void takeDown() {
        System.out.println("zaraz się usunę");
    }
}
