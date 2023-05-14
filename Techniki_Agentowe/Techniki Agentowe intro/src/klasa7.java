import jade.core.Agent;
import jade.core.behaviours.Behaviour;

public class klasa7 extends Agent {

    private Behaviour generyczne = new Behaviour() {

        private int krok = 1;

        public void action() {
            switch(krok) {
                case 1:
                    System.out.println("pierwszy krok");
                    addBehaviour(pierwsze);
                    krok++;
                    break;
                case 2:
                    System.out.println("drugi krok");
                    addBehaviour(drugie);
                    krok++;
                    break;
                case 3:
                    System.out.println("trzeci krok");
                    removeBehaviour(this);
                    break;
            }
        }

        public boolean done() {
            return (krok == 4);
        }
    };

    private Behaviour pierwsze = new Behaviour() {
        public void action() {
            System.out.println("pierwsze");
        }

        public boolean done() {
            return true;
        }
    };

    private Behaviour drugie = new Behaviour() {
        public void action() {
            System.out.println("drugie");
        }

        public boolean done() {
            return true;
        }
    };

    protected void setup() {
        System.out.println("startuję");
        addBehaviour(generyczne);
    }

    protected void takeDown() {
        System.out.println("zaraz się usunę");
    }

}
